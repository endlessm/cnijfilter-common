/*  Canon Bubble Jet Print Filter.
 *  Copyright CANON INC. 2001-2005
 *  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * NOTE:
 *  - As a special exception, this program is permissible to link with the
 *    libraries released as the binary modules.
 *  - If you write modifications of your own for these programs, it is your
 *    choice whether to permit this exception to apply to your modifications.
 *    If you do not wish that, delete this exception.
 */


#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define	SHELL_PATH	"/bin/sh"


int exec_command(char* command)
{
	int pid;

	if( command == NULL )
		return -1;

	pid = fork();

	if( pid == -1 )
		return -1;

	if( pid == 0 )
	{
		char* av[4];
		av[0] = SHELL_PATH;
		av[1] = "-c";
		av[2] = command;
		av[3] = NULL;

		printf("%s\n", command);

		execv(SHELL_PATH, av);

		printf("error\n");
		exit (127);
	}
	else
	{
		int cpid = waitpid(pid, NULL, 0);
		return (cpid > 0)? 0 : -1;
	}
}

int main(int ac, char* av[])
{
	signal(SIGPIPE, SIG_DFL);
	signal(SIGINT , SIG_DFL);
	signal(SIGHUP , SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);

	return exec_command(av[1]);
}


