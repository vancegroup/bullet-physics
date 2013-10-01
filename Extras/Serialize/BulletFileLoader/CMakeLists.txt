include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src)

set(BulletFileLoader_SRCS
	bChunk.cpp
	bDNA.cpp
	bFile.cpp
	btBulletFile.cpp)

set(BulletFileLoader_HDRS
	bChunk.h
	bCommon.h
	bDefines.h
	bDNA.h
	bFile.h
	btBulletFile.h)

add_library(BulletFileLoader
	${BulletFileLoader_SRCS}
	${BulletFileLoader_HDRS})

target_link_libraries(BulletFileLoader LinearMath)

set_target_properties(BulletFileLoader
	PROPERTIES
	VERSION
	${BULLET_VERSION})
set_target_properties(BulletFileLoader
	PROPERTIES
	SOVERSION
	${BULLET_VERSION})

if(INSTALL_EXTRA_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		#FILES_MATCHING requires CMake 2.6
		if(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 2.5)
			if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
				install(TARGETS BulletFileLoader DESTINATION .)
			else()
				install(TARGETS BulletFileLoader DESTINATION lib${LIB_SUFFIX})
				install(DIRECTORY
					${CMAKE_CURRENT_SOURCE_DIR}
					DESTINATION
					${INCLUDE_INSTALL_DIR}
					FILES_MATCHING
					PATTERN
					"*.h"
					PATTERN
					".svn"
					EXCLUDE
					PATTERN
					"CMakeFiles"
					EXCLUDE)
			endif()
		endif()

		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			set_target_properties(BulletFileLoader PROPERTIES FRAMEWORK true)
			set_target_properties(BulletFileLoader
				PROPERTIES
				PUBLIC_HEADER
				"${BulletFileLoader_HDRS}")
		endif()
	endif()
endif()
