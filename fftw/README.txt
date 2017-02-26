This directory is for the Windows build of fftw. On other platforms, fftw is provided as a system library.

Grab windows binariess from: http://www.fftw.org/install/windows.html

To create the *.lib files, open a Visual Studio Tools command window and run lib.exe as follows:
lib /def:libfftw3-3.def
lib /def:libfftw3f-3.def
lib /def:libfftw3l-3.def

