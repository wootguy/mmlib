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
	PARENT_SCOPE
)

set(META_HELPER_HEADERS
	${CMAKE_CURRENT_LIST_DIR}/src/meta_init.h
	${CMAKE_CURRENT_LIST_DIR}/src/meta_utils.h
	${CMAKE_CURRENT_LIST_DIR}/src/misc_utils.h
	${CMAKE_CURRENT_LIST_DIR}/src/Scheduler.h
	${CMAKE_CURRENT_LIST_DIR}/src/StartSound.h
	${CMAKE_CURRENT_LIST_DIR}/src/meta_helper.h
	${CMAKE_CURRENT_LIST_DIR}/src/temp_ents.h
	${CMAKE_CURRENT_LIST_DIR}/src/mmlib.h
	PARENT_SCOPE
)

set(META_HELPER_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/src/meta_init.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/meta_utils.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/misc_utils.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Scheduler.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/StartSound.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/meta_helper.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/temp_ents.cpp
	PARENT_SCOPE
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/metamod)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/hlsdk/common)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/hlsdk/dlls)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/hlsdk/engine)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/hlsdk/pm_shared)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/sven)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)



