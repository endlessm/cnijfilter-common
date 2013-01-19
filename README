
How to build rpm:
=================
    * When you build one printer driver package.
    --------------------------------------------
    $ rpmbuild -tb cnijfilter-source-X.XX-Y.tar.gz --define="MODEL [Printer Model Name]" --define="MODEL_NUM [Printer Model ID]" --with build_common_package	


    * When you build plural printer driver packages.
    ------------------------------------------------
	step 1)
    $ rpmbuild -tc cnijfilter-source-X.XX-Y.tar.gz --with prepare_fastbuild
	step 2)
    $ rpmbuild -tb cnijfilter-source-X.XX-Y.tar.gz --with fastbuild --define="MODEL [Printer Model Name]" --define="MODEL_NUM [Printer Model ID]" --with build_common_package	
	step 3) and after step 3)
    $ rpmbuild -tb cnijfilter-source-X.XX-Y.tar.gz --with fastbuild --define="MODEL [Printer Model Name]" --define="MODEL_NUM [Printer Model ID]"

    You can set the following [Printer Model Name]/[Printer Model ID].
        [Printer Model Name]        [Printer Model ID]
    ------------------------------------------------------------------
         mp230                       401
         mg2200                      402
         e510                        403
         mg3200                      404
         mg4200                      405
         ip7200                      406
         mg5400                      407
         mg6300                      408


Example:
========
    * Example for build MP230 package:
	----------------------------------
    $ rpmbuild -tb cnijfilter-source-X.XX-Y.tar.gz --define="MODEL MP230" --define="MODEL_NUM 401" --with build_common_package	

    * Example for build MG2200/E510/MG3200 packages:
	-----------------------------------------------
    $ rpmbuild -tc cnijfilter-source-X.XX-Y.tar.gz --with prepare_fastbuild
    $ rpmbuild -tb cnijfilter-source-X.XX-Y.tar.gz --with fastbuild --define="MODEL MG2200" --define="MODEL_NUM 402" --with build_common_package	
    $ rpmbuild -tb cnijfilter-source-X.XX-Y.tar.gz --with fastbuild --define="MODEL E510" --define="MODEL_NUM 403"	
    $ rpmbuild -tb cnijfilter-source-X.XX-Y.tar.gz --with fastbuild --define="MODEL MG3200" --define="MODEL_NUM 404"	
