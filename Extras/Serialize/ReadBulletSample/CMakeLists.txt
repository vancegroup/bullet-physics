
include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src)

if(WIN32)
	set(ADDITIONAL_SRC ${BULLET_PHYSICS_SOURCE_DIR}/build/bullet.rc)
endif()

set(READBULLET_SRC
	main.cpp
	BulletDataExtractor.cpp
	BulletDataExtractor.h
	${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btSerializer.cpp
	${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btAlignedAllocator.cpp)

add_executable(AppReadBulletSample ${READBULLET_SRC} ${ADDITIONAL_SRC})

target_link_libraries(AppReadBulletSample BulletFileLoader)

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(AppReadBulletSample
		PROPERTIES
		DEBUG_POSTFIX
		"_Debug")
	set_target_properties(AppReadBulletSample
		PROPERTIES
		MINSIZEREL_POSTFIX
		"_MinsizeRel")
	set_target_properties(AppReadBulletSample
		PROPERTIES
		RELWITHDEBINFO_POSTFIX
		"_RelWithDebugInfo")
endif()
