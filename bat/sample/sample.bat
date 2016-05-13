@echo off
setlocal enabledelayedexpansion

set dir_dat=..\..\dat
set dir_bin=..\..\bin\release

set file_in=!dir_dat!/Input/sample_gray.png

for %%a in (1 2 3 4) do (

	set file_LoG=!dir_dat!/output/sample_LoG_sigma%%a.png

	!dir_bin!\TestLoGFilter !file_in! !file_LoG!


	set file_zero_cross=!dir_dat!/output/sample_zero_cross_sigma%%a.png

	!dir_bin!\TestZeroCross !file_LoG! !file_zero_cross!

)

endlocal
