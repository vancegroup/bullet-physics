include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/BulletFileLoader
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/BulletWorldImporter)

add_library(BulletXmlWorldImporter
	btBulletXmlWorldImporter.cpp
	btBulletXmlWorldImporter.h
	string_split.cpp
	string_split.h
	tinyxml.cpp
	tinyxml.h
	tinystr.cpp
	tinystr.h
	tinyxmlerror.cpp
	tinyxmlparser.cpp)

set_target_properties(BulletXmlWorldImporter
	PROPERTIES
	VERSION
	${BULLET_VERSION})
set_target_properties(BulletXmlWorldImporter
	PROPERTIES
	SOVERSION
	${BULLET_VERSION})

target_link_libraries(BulletXmlWorldImporter
	BulletWorldImporter
	BulletDynamics
	BulletCollision
	BulletFileLoader
	LinearMath)

if(INSTALL_EXTRA_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS BulletXmlWorldImporter DESTINATION .)
		else()
			install(TARGETS BulletXmlWorldImporter DESTINATION lib${LIB_SUFFIX})
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
			set_target_properties(BulletXmlWorldImporter
				PROPERTIES
				FRAMEWORK
				true)
			set_target_properties(BulletXmlWorldImporter
				PROPERTIES
				PUBLIC_HEADER
				"btBulletXmlWorldImporter.h")
		endif()
	endif()
endif()
