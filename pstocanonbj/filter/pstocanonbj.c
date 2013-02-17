#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <cups/cups.h>
#include <cups/ppd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define BUF_SIZE 256
#define COMMAND_PATH \
	"/usr/bin/gs -r%d -g%dx%d -q -dNOPROMPT -dSAFER"\
	" -sDEVICE=ppmraw -sOutputFile=- - |"\
	" /usr/bin/%s%s --imageres %d --papersize %s"\
	" --paperload %s --media %s --bbox %d,%d,%d,%d"
#define CMD_BUF_SIZE 4096

int
main (int argc, char *argv[])
{
	int num_options;
	cups_option_t *options;
	ppd_file_t *ppd;
	ppd_choice_t *p_choice;
	ppd_size_t *p_size;
	int ret = 0;
	int resolution;
	int i;
	char paper[BUF_SIZE];
	char inputslot[BUF_SIZE];
	char mediatype[BUF_SIZE];
	char prefix[BUF_SIZE];
	char product[BUF_SIZE];
	char command[CMD_BUF_SIZE];
	double dd;
	pid_t child_pid;
	int child_stat;
	int fds[2];

	if (argc < 6 || argc > 7) {
		fprintf(stderr, "ERROR: Incorrect arguments: %d\n", argc);
		return 1;
	}

	if (argc == 7) {
		if ((close(0) != 0) || (open(argv[6], O_RDONLY) != 0)) {
			fprintf(stderr, "ERROR: cannot open file: %s\n", argv[6]);
			return 1;
		}
	}

	if ((ppd = ppdOpenFile(getenv("PPD"))) == NULL) {
		fprintf(stderr, "ERROR: cannot open ppd: %s\n", getenv("PPD"));
		return 1;
	}

	options = NULL;
	num_options = cupsParseOptions(argv[5], 0, &options);

	ppdMarkDefaults(ppd);
	cupsMarkOptions(ppd, num_options, options);

	/* get resolution */
	p_choice = ppdFindMarkedChoice(ppd, "Resolution");
	resolution = atoi(p_choice->choice);
	/* get paper size */
	p_choice = ppdFindMarkedChoice(ppd, "PageSize");
	strncpy(paper, p_choice->choice, BUF_SIZE);
	/* These are dirty hacks. */
	/* Canon driver does not accept "paper size" spelled in upper case. */
	/* They, however, force us to use large 'X' in paper sizes such as 4X6 or 8X10.  */
	/* So we cannot simply convert upper cases into lower cases. */
	/* What a stupid strategy they did!! */
	if (paper[0] == 'A')
		paper[0] = 'a';
	if (paper[0] == 'B')
		paper[0] = 'b';
	paper[BUF_SIZE - 1] = 0;
	p_size = ppdPageSize(ppd, p_choice->choice);
	
	fprintf(stderr, "DEBUG: paper: %s, resolution %d\n", paper, resolution);

	/* get seet feeder option */
	p_choice = ppdFindMarkedChoice(ppd, "InputSlot");
	strncpy(inputslot, p_choice->choice, BUF_SIZE);
	inputslot[BUF_SIZE - 1] = 0;
	
	fprintf(stderr, "DEBUG: seetfeeder: %s \n", inputslot);

	/* get media type option */
	p_choice = ppdFindMarkedChoice(ppd, "MediaType");
	strncpy(mediatype, p_choice->choice, BUF_SIZE);
	mediatype[BUF_SIZE - 1] = 0;

	fprintf(stderr, "DEBUG: mediatype: %s \n", mediatype);
	
	/* get product name */
	strncpy(product, ppd->shortnickname, BUF_SIZE);
	product[BUF_SIZE - 1] = 0;
	for (i = 0; i < BUF_SIZE; i++)
		product[i] = tolower(product[i]);

	fprintf(stderr, "DEBUG: model: %s\n", product);

	/* The prefix of bjfiter was changed from "bjfilter" into "cif". */
	/* Another dirty hack again.... :-< */
	if (strncmp(product, "pixus", 5) == 0 || strncmp(product, "pixma", 5) == 0)
		strncpy(prefix, "bjfilter", BUF_SIZE);
	else
		strncpy(prefix, "cif", BUF_SIZE);
	prefix[BUF_SIZE - 1] = 0;
	
	/* filter */
	dd = 1.0 - 36.0 / (double)resolution;
	snprintf(command, CMD_BUF_SIZE, COMMAND_PATH,
			resolution,
			(int)(p_size->width * (double)resolution / 72.0),
			(int)(p_size->length * (double)resolution / 72.0),
			prefix, product, resolution, paper, inputslot, mediatype,
			(int)p_size->left,
			(int)(p_size->bottom - dd),
			(int)(p_size->right + dd),
			(int)(p_size->top + dd));
	command[CMD_BUF_SIZE - 1] = 0;
	fprintf(stderr, "DEBUG: command: %s\n", command);

	/* fork */
	if ((child_pid = fork()) == 0) {
		/* child process */
		close(2);
		execl("/bin/sh", "/bin/sh", "-c", command, (char*)NULL);
	} else {
		/* parent process */
		wait(&child_stat);
		if (WIFEXITED(child_stat) == 0 || WEXITSTATUS(child_stat) != 0) {
			fprintf(stderr, "ERROR: child process aborted\n");
			ret = 1;
		}
		else {
			fprintf(stderr, "DEBUG: child process exited\n");
			ret = 0;
		}
	}
	
	ppdClose(ppd);

	return ret;
}

