#!/usr/bin/perl

$dst_dir = "_nozzle_check_image";

if ( @ARGV != 1 ){
	printf( "usage : %s [tbl file]\n", $0 );
	exit 1;
}

$fn = $ARGV[0];
open( IN, $fn );

if ( -d $dst_dir ){
	`rm -rf $dst_dir`;
}
`mkdir $dst_dir`;

while( <IN> ){
	$line = $_;
	chomp( $line );

	if ( $line =~ /^#.+/ ) {
		goto NEXT_LINE;
	}

	@parm = split( /\t/, $line );

	$model_id = $parm[0];
	$model_name = $parm[1];
	$nozzle_id = $parm[2];

	$ret = CopyData( $nozzle_id, $model_name, $dst_dir, "okptn" );
	if ( $ret != 0 ) {
		exit 1;
	}
	$ret = CopyData( $nozzle_id, $model_name, $dst_dir, "ngptn" );
	if ( $ret != 0 ) {
		exit 1;
	}
NEXT_LINE:
}

close( IN );

# arg[0] : $nozzle_id
# arg[1] : $model_name
# arg[2] : $dst_dir
# arg[4] : $tgt_head 

sub CopyData {
	my $nozzle_id = $_[0];
	my $model_name = $_[1];
	my $dst_dir = $_[2];
	my $tgt_head  = $_[3];

	$src_name = sprintf( "%s_%s.xpm", $tgt_head, $nozzle_id );
	$dst_name = sprintf( "%s/%s_%s.xpm", $dst_dir, $tgt_head, $model_name );

	#printf( "src_name : %s\n", $src_name );
	#printf( "dst_name : %s\n", $dst_name );

	if ( -f $src_name ) {
		printf( "Creating nozzle check image file : %s\n", $model_name );
		`cp -f $src_name $dst_name`;
	}
	else {
		printf( "Source File Not Found.\n" );
		return 1;
	}
	return 0;
}
