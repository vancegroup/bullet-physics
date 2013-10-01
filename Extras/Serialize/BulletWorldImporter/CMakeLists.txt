include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/BulletFileLoader)

add_library(BulletWorldImporter
	btBulletWorldImporter.cpp
	btBulletWorldImporter.h
	btWorldImporter.cpp
	btWorldImporter.h)

set_target_properties(BulletWorldImporter
	PROPERTIES
	VERSION
	${BULLET_VERSION})
set_target_properties(BulletWorldImporter
	PROPERTIES
	SOVERSION
	${BULLET_VERSION})

if(BUILD_SHARED_LIBS)
	target_link_libraries(BulletWorldImporter
		BulletDynamics
		BulletCollision
		BulletFileLoader
		LinearMath)
endif()

if(INSTALL_EXTRA_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS BulletWorldImporter DESTINATION .)
		else()
			install(TARGETS BulletWorldImporter DESTINATION lib${LIB_SUFFIX})
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

		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			set_target_properties(BulletWorldImporter PROPERTIES FRAMEWORK true)
			set_target_properties(BulletWorldImporter
				PROPERTIES
				PUBLIC_HEADER
				"btBulletWorldImporter.h")
		endif()
	endif()
endif()
