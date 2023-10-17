cmake_minimum_required(VERSION 3.6)

set(SVEN_ROOT_PATH "C:/Games/Steam/steamapps/common/Sven Co-op/" CACHE PATH "Where your Sven Co-op folder is")
set(DLL_INSTALL_PATH "svencoop/addons/metamod/dlls" CACHE PATH "Where to install the DLL (relative to Sven Co-op folder)")

option(SKIP_IDE_SETUP "For end users who just want to build the plugin and nothing else" OFF)

if (WIN32)
	set(sven_header_path ${CMAKE_CURRENT_LIST_DIR}/include/sven/windows)
	target_include_directories(${PROJECT_NAME} PUBLIC ${sven_header_path})
	set(OS_SPECIFIC_SRCS
		${CMAKE_CURRENT_LIST_DIR}/src/net/Socket_win.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/net/network_win.cpp
	)
	
	# static link the MSVC runtime so user's don't need to install Visual Studio to load the plugin
	# disable warnings in release builds (users don't care about that)
	set(MMLIB_CXX_FLAGS "" PARENT_SCOPE)
	set(MMLIB_CXX_FLAGS_RELEASE "/MT /w" PARENT_SCOPE)
	set(MMLIB_CXX_FLAGS_DEBUG "/MTd" PARENT_SCOPE)
	
	# WinSock libraries for network utils
	set(MMLIB_LINK_LIBS WS2_32 IPHLPAPI PARENT_SCOPE)
else()
	set(sven_header_path ${CMAKE_CURRENT_LIST_DIR}/include/sven/linux)
	target_include_directories(${PROJECT_NAME} PUBLIC ${sven_header_path})
	set(OS_SPECIFIC_SRCS
		${CMAKE_CURRENT_LIST_DIR}/src/net/Socket_unix.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/net/network_unix.cpp
	)
	
	# Static linking libstd++ and libgcc so that the plugin can load on distros other than one it was compiled on.
	# -fvisibility=hidden fixes a weird bug where the metamod confuses game functions with plugin functions.
	# -g includes debug symbols which provides useful crash logs, but also inflates the .so file size a lot.
	# warnings are disabled in release mode (users don't care about that)
	set(MMLIB_CXX_FLAGS "-m32 -std=c++11 -fvisibility=hidden -static-libstdc++ -static-libgcc -g" PARENT_SCOPE)
	set(MMLIB_CXX_FLAGS_DEBUG "-O0 -Wall" PARENT_SCOPE)
	set(MMLIB_CXX_FLAGS_RELEASE "-Os -w -Wfatal-errors" PARENT_SCOPE)
	
	set(CMAKE_SHARED_LIBRARY_PREFIX "" PARENT_SCOPE)
	
	# required for metamod osdep.h
	target_compile_definitions(${PROJECT_NAME} PUBLIC -Dlinux)
endif()

function(mmlib_ide_setup)
	if (SKIP_IDE_SETUP)
		return()
	endif()

	# setup Visual Studio for debugging and add project files to subfolders
	if (MSVC)
		# write dll files directly to your metamod folder
		set_target_properties(${PROJECT_NAME} PROPERTIES
						  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${SVEN_ROOT_PATH}/${DLL_INSTALL_PATH}"
						  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${SVEN_ROOT_PATH}/${DLL_INSTALL_PATH}")

		# options for launching the game from Visual Studio
		set_target_properties(${PROJECT_NAME} PROPERTIES
						  VS_STARTUP_PROJECT ${PROJECT_NAME}
						  VS_DEBUGGER_COMMAND "svencoop.exe"
						  VS_DEBUGGER_COMMAND_ARGUMENTS "+map stadium4 -dll addons/metamod/dlls/metamod.dll"
						  VS_DEBUGGER_WORKING_DIRECTORY "${SVEN_ROOT_PATH}/") # path must end with a slash
	
		cmake_path(SET DLLS_PATH NORMALIZE "${SVEN_ROOT_PATH}/${DLL_INSTALL_PATH}")

		# can't overwrite a dll while its loaded but it can be renamed, then you can run "meta reload <plugin>"
		# to load the new dll with the old file name.
		file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/replace_dll.bat"
			"cd ${DLLS_PATH}\n"
			"if exist ${PROJECT_NAME}_old.dll \(\n"
			"\tdel ${PROJECT_NAME}_old.dll\n"
			"\)\n"
			"if exist ${PROJECT_NAME}.dll \(\n"
			"\trename ${PROJECT_NAME}.dll ${PROJECT_NAME}_old.dll\n"
			"\)\n"
			"exit /b 0\n"
		)
		add_custom_command(
			TARGET ${PROJECT_NAME} PRE_BUILD
			COMMAND ${CMAKE_CURRENT_BINARY_DIR}/replace_dll.bat
		)
		
		source_group("Header Files\\sven" FILES ${SVEN_API_HEADERS})
		source_group("Header Files\\mmlib" FILES ${META_HELPER_HEADERS})
		source_group("Source Files\\mmlib" FILES ${META_HELPER_SOURCES})
	endif()
endfunction()

function(mmlib_default_setup)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MMLIB_CXX_FLAGS}" PARENT_SCOPE)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${MMLIB_CXX_FLAGS_DEBUG}" PARENT_SCOPE)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${MMLIB_CXX_FLAGS_RELEASE}" PARENT_SCOPE)
	target_link_libraries(${PROJECT_NAME} ${MMLIB_LINK_LIBS})
	mmlib_ide_setup()
endfunction()
	
set(SVEN_API_HEADERS
	${sven_header_path}/CBaseAnimating.h
	${sven_header_path}/CBaseButton.h
	${sven_header_path}/CBaseDelay.h
	${sven_header_path}/CBaseEntity.h
	${sven_header_path}/CBaseMonster.h
	${sven_header_path}/CBasePlayer.h
	${sven_header_path}/CBasePlayerItem.h
	${sven_header_path}/CBasePlayerWeapon.h
	${sven_header_path}/CBaseTank.h
	${sven_header_path}/CBaseToggle.h
	${sven_header_path}/CCineMonster.h
	${sven_header_path}/CItemInventory.h
	${sven_header_path}/CPathTrack.h
	${sven_header_path}/EHandle.h
	${sven_header_path}/private_api.h
	${sven_header_path}/sc_enums.h
)

set(META_HELPER_HEADERS
	${CMAKE_CURRENT_LIST_DIR}/src/mmlib.h
	${CMAKE_CURRENT_LIST_DIR}/src/meta_init.h
	${CMAKE_CURRENT_LIST_DIR}/src/meta_utils.h
	${CMAKE_CURRENT_LIST_DIR}/src/misc_utils.h
	${CMAKE_CURRENT_LIST_DIR}/src/Scheduler.h
	${CMAKE_CURRENT_LIST_DIR}/src/StartSound.h
	${CMAKE_CURRENT_LIST_DIR}/src/meta_helper.h
	${CMAKE_CURRENT_LIST_DIR}/src/temp_ents.h
	${CMAKE_CURRENT_LIST_DIR}/src/HUDSprite.h
	${CMAKE_CURRENT_LIST_DIR}/src/TextMenu.h
	${CMAKE_CURRENT_LIST_DIR}/src/ThreadSafeQueue.h
	${CMAKE_CURRENT_LIST_DIR}/src/UserInfo.h
	${CMAKE_CURRENT_LIST_DIR}/src/NetMessage.h
	${CMAKE_CURRENT_LIST_DIR}/src/HashPak.h
	${CMAKE_CURRENT_LIST_DIR}/src/net/IPV4.h
	${CMAKE_CURRENT_LIST_DIR}/src/net/Socket.h
	${CMAKE_CURRENT_LIST_DIR}/src/net/Packet.h
	${CMAKE_CURRENT_LIST_DIR}/src/ThreadSafeInt.h
	${CMAKE_CURRENT_LIST_DIR}/src/mstream.h
	${CMAKE_CURRENT_LIST_DIR}/src/crc32.h
)

set(META_HELPER_SOURCES ${OS_SPECIFIC_SRCS}
	${CMAKE_CURRENT_LIST_DIR}/src/meta_init.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/meta_utils.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/misc_utils.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Scheduler.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/StartSound.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/meta_helper.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/temp_ents.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/HUDSprite.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/TextMenu.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ThreadSafeQueue.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/UserInfo.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/NetMessage.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/HashPak.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/MD5.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/net/IPV4.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/net/Packet.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ThreadSafeInt.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/mstream.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/crc32.cpp
)

set(SVEN_API_HEADERS ${SVEN_API_HEADERS} PARENT_SCOPE)
set(META_HELPER_HEADERS ${META_HELPER_HEADERS} PARENT_SCOPE)
set(META_HELPER_SOURCES ${META_HELPER_SOURCES} PARENT_SCOPE)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES} ${META_HELPER_SOURCES} ${META_HELPER_HEADERS} ${SVEN_API_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/metamod)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/hlsdk/common)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/hlsdk/dlls)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/hlsdk/engine)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/hlsdk/pm_shared)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/net)
