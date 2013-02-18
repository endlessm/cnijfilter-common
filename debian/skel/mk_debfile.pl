#!/usr/bin/perl

if ( @ARGV != 1 ) {
	printf( "usage : %s ../rules\n", $0 );
}



$fn = $ARGV[0];


open( IN, $fn );
while( <IN> ){
	$line = $_;
	chomp( $line );
	if ( $line =~ /^PRINTER_BUILD_VERSION.?=(.+$)/ ){
		$info = $1;
		if (  $info =~ /(.+)/ ){
		$version = $1;
		}
	}
	if ( $line =~ /^PRINTER_BUILD_64_AS.?=(.+$)/ ){
		$info = $1;
		if (  $info =~ /(.+)/ ){
		$as64build32 = $1;
			if ( $as64build32 eq "64" ){
				`cp control.common.skel control`;
			}
			if ( $as64build32 eq "32" ){
				`cp control.common.i386.skel control`;
			}
			if ( $as64build32 eq "33" ){
				`cp control.common.ia32.skel control`;
				`perl -pe 's/VERSION/${version}/' docs.skel >> cnijfilter-common-64.docs`;
				`cp postinst.common.skel cnijfilter-common-64.postinst`;
				`cp postrm.common.skel cnijfilter-common-64.postrm`;
			}
			`perl -pe 's/VERSION/${version}/' docs.skel >> docs`;
			`cp postinst.common.skel postinst`;
			`cp postrm.common.skel postrm`;
		}
	}
	# PRINTER_DEPEND_PKG+=cnijfilter-mg6300-408-3.80-64-yes
	if ( $line =~ /^PRINTER_DEPEND_PKG.+?=(.+$)/ ){
		$info = $1;
		if (  $info =~ /(.+)\-(.+)\-(.+)\-(.+)\-(.+)\-(.+)/ ){
			$model = $2;
			$num = $3;
			$version2 = $4;
			$cputype = $5;
			$lpropt = $6;
			$deco = "cnijfilter-$2-$3";
			$modeluc = uc $model;
			printf( "model: %s\n", $2 );
			printf( "num: %s\n", $3 );
			printf( "lpr: %s\n", $lpropt );
			if ( $as64build32 eq "33" ){
			if ( $cputype eq "64" ){
				# doc file
				`perl -pe 's/VERSION/${version}/' docs.skel >> cnijfilter-${model}series-64.docs`;
				if ( $lpropt eq "yes" ){
					`perl -pe 's/MODEL/${model}/' lproptions.skel >>  cnijfilter-${model}series-64.docs`;
					`perl -i -pe 's/VERSION/${version2}/' cnijfilter-${model}series-64.docs`;
				}
	
				# postinst file
				`perl -pe 's/XXXX/${deco}/' postinst.package.skel >  cnijfilter-${model}series-64.postinst`;
		
				# postrm file
				`perl -pe 's/XXXX/${deco}/' postrm.package.skel > cnijfilter-${model}series-64.postrm`;
	
				# printui.desktop file
				if ( $version2 eq "3.80" ){
				`perl -pe 's/XXXX/${model}/' install.skel > cnijfilter-${model}series-64.install`;
				`perl -i -pe 's/GGGG/maintenance/' cnijfilter-${model}series-64.install`;
				}else{
				`perl -pe 's/XXXX/${model}/' install.skel > cnijfilter-${model}series-64.install`;
				`perl -i -pe 's/GGGG/printui/' cnijfilter-${model}series-64.install`;
				}
			}}

			# doc file
			`perl -pe 's/VERSION/${version}/' docs.skel >> cnijfilter-${model}series.docs`;
			if ( $lpropt eq "yes" ){
				`perl -pe 's/MODEL/${model}/' lproptions.skel >>  cnijfilter-${model}series.docs`;
				`perl -i -pe 's/VERSION/${version2}/' cnijfilter-${model}series.docs`;
			}

			# postinst file
			`perl -pe 's/XXXX/${deco}/' postinst.package.skel >  cnijfilter-${model}series.postinst`;

			# postrm file
			`perl -pe 's/XXXX/${deco}/' postrm.package.skel > cnijfilter-${model}series.postrm`;

			# printui.desktop file
			if ( $version2 eq "3.80" ){
			`perl -pe 's/YYYY/${modeluc}/' maintenance.desktop.skel > maintenance-${model}series.desktop`;
			`perl -i -pe 's/PIXUS/PIXUS-/' maintenance-${model}series.desktop`;
			`perl -i -pe 's/PIXMA/PIXMA-/' maintenance-${model}series.desktop`;
			`perl -pe 's/XXXX/${model}/' install.skel > cnijfilter-${model}series.install`;
			`perl -i -pe 's/GGGG/maintenance/' cnijfilter-${model}series.install`;
			}else{
			`perl -pe 's/YYYY/${modeluc}/' printui.desktop.skel > printui-${model}series.desktop`;
			`perl -i -pe 's/PIXUS/PIXUS-/' printui-${model}series.desktop`;
			`perl -i -pe 's/PIXMA/PIXMA-/' printui-${model}series.desktop`;
			`perl -pe 's/XXXX/${model}/' install.skel > cnijfilter-${model}series.install`;
			`perl -i -pe 's/GGGG/printui/' cnijfilter-${model}series.install`;
			}

			# cngpijmon.desktop file
			`perl -pe 's/XXXX/${model}/' cngpijmon.desktop.skel > cngpijmon-${model}series.desktop`;
			`perl -i -pe 's/YYYY/${modeluc}/' cngpijmon-${model}series.desktop`;


			# control file
			if ( $as64build32 eq "64" ){
				if ( $cputype eq "64" ){
					$buildtype = "i386 amd64";
				}else{
					$buildtype = "i386";
				}
			}else{
				$buildtype = "i386 amd64";
			}
			if ( $as64build32 eq "33" ){
				`perl -pe 's/XXXX/${model}/' control.package.ia32.skel >> control`;
				`perl -i -pe 's/VERSION/${version}/' control`;
				if ( $cputype eq "64" ){
					`perl -pe 's/XXXX/${model}/' control.package.amd64.skel >> control`;
					`perl -i -pe 's/VERSION/${version}/' control`;
				}
			}else{
				`perl -pe 's/XXXX/${model}/' control.package.skel >> control`;
				`perl -i -pe 's/VERSION/${version}/' control`;
				`perl -i -pe 's/ARCHITECTURE/$buildtype/' control`;
			}
		}
	}
	# PRINTER_PKG_PPD+=cnijfilter-ip5200-2.60-ip4200-32
	if ( $line =~ /^PRINTER_PKG_PPD.+?=(.+$)/ ){
		$info = $1;
		if (  $info =~ /(.+)\-(.+)\-(.+)\-(.+)\-(.+)/ ){
			$model = $2;
			$version2 = $3;
			$model2 = $4;
			$cputype = $5;
			$modeluc = uc $model;
			$model2uc = uc $model2;
			$deco = "cnijfilter-$2";
			printf( "model: %s\n", $2 );
			if ( $as64build32 eq "33" ){
			if ( $cputype eq "64" ){
				# doc file
				`perl -pe 's/VERSION/${version}/' docs.skel >> cnijfilter-${model}series-64.docs`;
	
				# postinst file
				`perl -pe 's/XXXX/${deco}/' postinst.package.ppd.skel >  cnijfilter-${model}series-64.postinst`;
	
				# postrm file
				`perl -pe 's/XXXX/${deco}/' postrm.package.ppd.skel > cnijfilter-${model}series-64.postrm`;

				# printui.desktop file
				if ( $version2 eq "3.80" ){
				`perl -pe 's/XXXX/${model}/' install.skel > cnijfilter-${model}series-64.install`;
				`perl -i -pe 's/GGGG/maintenance/' cnijfilter-${model}series-64.install`;
				}else{
				`perl -pe 's/XXXX/${model}/' install.skel > cnijfilter-${model}series-64.install`;
				`perl -i -pe 's/GGGG/printui/' cnijfilter-${model}series-64.install`;
				}
			}}
			# doc file
			`perl -pe 's/VERSION/${version}/' docs.skel >> cnijfilter-${model}series.docs`;

			# postinst file
			`perl -pe 's/XXXX/${deco}/' postinst.package.ppd.skel >  cnijfilter-${model}series.postinst`;

			# postrm file
			`perl -pe 's/XXXX/${deco}/' postrm.package.ppd.skel > cnijfilter-${model}series.postrm`;

			# printui.desktop file
			if ( $version2 eq "3.80" ){
			`perl -pe 's/YYYY/${modeluc}/' maintenance.desktop.skel > maintenance-${model}series.desktop`;
			`perl -i -pe 's/PIXUS/PIXUS-/' maintenance-${model}series.desktop`;
			`perl -i -pe 's/PIXMA/PIXMA-/' maintenance-${model}series.desktop`;
			`perl -pe 's/XXXX/${model}/' install.skel > cnijfilter-${model}series.install`;
			`perl -i -pe 's/GGGG/maintenance/' cnijfilter-${model}series.install`;
			}else{
			`perl -pe 's/YYYY/${modeluc}/' printui.desktop.skel > printui-${model}series.desktop`;
			`perl -i -pe 's/PIXUS/PIXUS-/' printui-${model}series.desktop`;
			`perl -i -pe 's/PIXMA/PIXMA-/' printui-${model}series.desktop`;
			`perl -pe 's/XXXX/${model}/' install.skel > cnijfilter-${model}series.install`;
			`perl -i -pe 's/GGGG/printui/' cnijfilter-${model}series.install`;
			}

			# cngpijmon.desktop file
			`perl -pe 's/XXXX/${model}/' cngpijmon.desktop.skel > cngpijmon-${model}series.desktop`;
			`perl -i -pe 's/YYYY/${model2uc}/' cngpijmon-${model}series.desktop`;


			# control file
			if ( $as64build32 eq "64" ){
				if ( $cputype eq "64" ){
					$buildtype = "i386 amd64";
				}else{
					$buildtype = "i386";
				}
			}else{
				$buildtype = "i386 amd64";
			}
			if ( $as64build32 eq "33" ){
				`perl -pe 's/XXXX/${model}/' control.package.ppd.ia32.skel >> control`;
				`perl -i -pe 's/VERSION/${version}/' control`;
				`perl -i -pe 's/YYYY/${model2}/' control`;
				if ( $cputype eq "64" ){
					`perl -pe 's/XXXX/${model}/' control.package.ppd.amd64.skel >> control`;
					`perl -i -pe 's/VERSION/${version}/' control`;
					`perl -i -pe 's/YYYY/${model2}/' control`;
				}
			}else{
				`perl -pe 's/XXXX/${model}/' control.package.ppd.skel >> control`;
				`perl -i -pe 's/VERSION/${version}/' control`;
				`perl -i -pe 's/YYYY/${model2}/' control`;
				`perl -i -pe 's/ARCHITECTURE/$buildtype/' control`;
			}
		}
	}
}
close( IN );
