# mmlib
Utility code for metamod plugins. It handles metamod initialization so that you only need to define `PluginInit()`, `PluginExit()`, and a `Plugin_info` struct to create a functional plugin. Private API headers for Sven Co-op are included so you can use game-specific data/functions for things like CBaseEntity and CBasePlayer.

Some non-trivial utilities included here:  
- Text menus
- g_Scheduler (like in Angelscript)
- PlaySound
- Network sockets

MetaHelper.as exists for private APIs and hooks which are not accessible to metamod plugins. As [ApiGenerator](https://github.com/wootguy/ApiGenerator) improves, fewer of those functions will be necessary.

# Creating a new project that uses mmlib
1. Download the code and extract the "example_project" folder somewhere
2. Open a shell in the example_project folder and run these commands to setup a git repo with the mmlib submodule
```
git init
git submodule add https://github.com/wootguy/mmlib
```
4. Open `CMakeLists.txt` and edit the name of the project and add source files to the `SOURCE_FILES` list.
5. Open `mmlib/CMakelists.txt` and make sure the [path to Sven Co-op](https://github.com/wootguy/mmlib/blob/master/CMakeLists.txt#L3) is correct.
6. Run `msvc.bat` to generate Visual Studio project files
7. Open the Visual Studio solution, then right click the `mmlib_example` project and select `Set as startup project`
8. Add `win32 addons/metamod/dlls/mmlib_example.dll` to your metamod `plugins.ini` file
9. Press F5 in VS. The game should start up with the debugger attached.
10. Type something in chat and the example plugin should tell you something.

To pull updates from this mmlib repo into your project, run:  
```
git submodule update --recursive --remote
```

# Generic build instructions for plugins that use mmlib
Most of my plugins don't change the mmlib build process and so you can follow the instructions below to build them all.

Windows:  
1. Intall Git for windows, CMake, and Visual Studio 2022 (select "Desktop development with C++")
2. Open a command prompt somewhere and run this command to download the code (replace `PluginName` with the name of the plugin repo):
    ```
    git clone --recurse-submodules https://github.com/wootguy/PluginName
    ```
3. Open the folder that was created and run `build.bat`

Linux:
1. Install Git, CMake, and a compiler.  
    Debian: `sudo apt install build-essential git cmake`
2. Open a terminal somewhere and and run these commands, replacing `PluginName` with the name of the plugin repo: 
    ```
    git clone --recurse-submodules https://github.com/wootguy/PluginName
    cd PluginName
    sh build.sh
    ```
