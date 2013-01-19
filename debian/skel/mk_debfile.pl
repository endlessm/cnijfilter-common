#!/usr/bin/perl

if ( @ARGV != 1 ) {
	printf( "usage : %s ../rules\n", $0 );
}



$fn = $ARGV[0];

open( IN, $fn );
while( <IN> ){
	$line = $_;
	chomp( $line );

	if ( $line =~ /^PRINTER_DEPEND_PKG.+?=(.+$)/ ){
		$info = $1;
		if (  $info =~ /(.+)\-(.+)\-(.+)\-(.+)\-(.+)\-(.+)/ ){
			$model = $2;
			$num = $3;
			$version = $4;
			$lpropt = $6;
			$deco = "cnijfilter-$2-$3";
			$modeluc = uc $model;
			printf( "model: %s\n", $2 );
			printf( "num: %s\n", $3 );
			printf( "lpr: %s\n", $lpropt );
			# doc file
			`cp docs.skel cnijfilter-${model}series.docs`;
			if ( $lpropt eq "yes" ){
				`perl -pe 's/MODEL/${model}/' lproptions.skel >>  cnijfilter-${model}series.docs`;
				`perl -i -pe 's/VERSION/${version}/' cnijfilter-${model}series.docs`;
			}

			# postinst file
			`perl -pe 's/XXXX/${deco}/' postinst.skel >  cnijfilter-${model}series.postinst`;

			# postrm file
			`perl -pe 's/XXXX/${deco}/' postrm.skel > cnijfilter-${model}series.postrm`;

			# install file
			`perl -pe 's/XXXX/${model}/' install.skel > cnijfilter-${model}series.install`;

			# printui.desktop file
			if ( $version eq "3.80" ){
			`perl -pe 's/YYYY/${modeluc}/' maintenance.desktop.skel > maintenance-${model}series.desktop`;
			`perl -i -pe 's/PIXUS/PIXUS-/' maintenance-${model}series.desktop`;
			`perl -i -pe 's/PIXMA/PIXMA-/' maintenance-${model}series.desktop`;
			`perl -i -pe 's/printui/maintenance/' cnijfilter-${model}series.install`;
			}else{
			`perl -pe 's/YYYY/${modeluc}/' printui.desktop.skel > printui-${model}series.desktop`;
			`perl -i -pe 's/PIXUS/PIXUS-/' printui-${model}series.desktop`;
			`perl -i -pe 's/PIXMA/PIXMA-/' printui-${model}series.desktop`;
			}

			# cngpijmon.desktop file
			`perl -pe 's/XXXX/${model}/' cngpijmon.desktop.skel > cngpijmon-${model}series.desktop`;
			`perl -i -pe 's/YYYY/${modeluc}/' cngpijmon-${model}series.desktop`;
		}
	}
}
close( IN );
