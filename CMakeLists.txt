cmake_minimum_required(VERSION 3.6)

set(SVEN_API_HEADERS
	${CMAKE_CURRENT_LIST_DIR}/include/sven/CBaseAnimating.h
	${CMAKE_CURRENT_LIST_DIR}/include/sven/CBaseButton.h
	${CMAKE_CURRENT_LIST_DIR}/include/sven/CBaseDelay.h
	${CMAKE_CURRENT_LIST_DIR}/include/sven/CBaseEntity.h
	${CMAKE_CURRENT_LIST_DIR}/include/sven/CBaseMonster.h
	${CMAKE_CURRENT_LIST_DIR}/include/sven/CBasePlayer.h
	${CMAKE_CURRENT_LIST_DIR}/include/sven/CBasePlayerItem.h
	${CMAKE_CURRENT_LIST_DIR}/include/sven/CBasePlayerWeapon.h
	${CMAKE_CURRENT_LIST_DIR}/include/sven/CBaseTank.h
	${CMAKE_CURRENT_LIST_DIR}/include/sven/CBaseToggle.h
	${CMAKE_CURRENT_LIST_DIR}/include/sven/CCineMonster.h
	${CMAKE_CURRENT_LIST_DIR}/include/sven/CItemInventory.h
	${CMAKE_CURRENT_LIST_DIR}/include/sven/CPathTrack.h
	${CMAKE_CURRENT_LIST_DIR}/include/sven/EHandle.h
	${CMAKE_CURRENT_LIST_DIR}/include/sven/private_api.h
	${CMAKE_CURRENT_LIST_DIR}/include/sven/sc_enums.h
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
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/sven)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)



