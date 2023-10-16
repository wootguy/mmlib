@echo off
cls
echo This script will build the plugin and copy the .dll to the same folder as this script.
echo Before continuing, you should have installed:
echo - CMake 
echo - Visual Studio (with "Desktop development with C++" selected in the installer)
echo.
pause

mkdir build
cd build
cmake -A Win32 -DSKIP_IDE_SETUP=ON ..
cmake --build . --config Release

@echo off
IF EXIST "Release\*.dll" (
	copy "Release\*.dll" .. /Y
	echo.
	echo The build finished! Look for a .dll file next to this script.
) ELSE (
	echo.
	echo "Oopsie whoopsie! The build failed! Look above for errors.
)

echo.
pause