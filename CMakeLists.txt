cmake_minimum_required(VERSION 3.6)

if (WIN32)
	set(sven_header_path ${CMAKE_CURRENT_LIST_DIR}/include/sven/windows)
	target_include_directories(${PROJECT_NAME} PUBLIC ${sven_header_path})
else()
	set(sven_header_path ${CMAKE_CURRENT_LIST_DIR}/include/sven/linux)
	target_include_directories(${PROJECT_NAME} PUBLIC ${sven_header_path})
endif()

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
)

set(META_HELPER_SOURCES
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
