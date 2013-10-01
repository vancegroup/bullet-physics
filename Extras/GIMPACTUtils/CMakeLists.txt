include_directories(${BULLET_PHYSICS_SOURCE_DIR}/Extras/GIMPACT/include
	${BULLET_PHYSICS_SOURCE_DIR}/src
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/GIMPACTUtils
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/ConvexDecomposition)

add_library(GIMPACTUtils
	btGImpactConvexDecompositionShape.cpp
	btGImpactConvexDecompositionShape.h)
set_target_properties(GIMPACTUtils PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(GIMPACTUtils
	PROPERTIES
	SOVERSION
	${BULLET_VERSION})

target_link_libraries(GIMPACTUtils ConvexDecomposition BulletCollision)

if(INSTALL_EXTRA_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS GIMPACTUtils DESTINATION .)
		else()
			install(TARGETS GIMPACTUtils DESTINATION lib${LIB_SUFFIX})
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
			set_target_properties(GIMPACTUtils PROPERTIES FRAMEWORK true)
			set_target_properties(GIMPACTUtils
				PROPERTIES
				PUBLIC_HEADER
				"btGImpactConvexDecompositionShape.h")
		endif()
	endif()
endif()
