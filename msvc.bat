@echo off
cls
echo This script will setup Visual Studio to automatically install the .dll file after builds
echo and launch the game with the debugger attached. You can also launch the game seperately,
echo build the plugin, then do "meta reload <plugin_name>" to reload the plugin without restarting.
echo.
echo Before continuing, make sure the Sven Co-op path is correct in mmlib/CMakeLists.txt
echo The variable is named "SVEN_ROOT_PATH" and defaults to "C:/Games/Steam/steamapps/common/Sven Co-op/"
echo.
pause

mkdir msvc
cd msvc
cmake -A Win32 %* ..

pause