include_directories(${BULLET_PHYSICS_SOURCE_DIR}/Extras/HACD)

set(HACD_SRCS
	hacdGraph.cpp
	hacdHACD.cpp
	hacdICHull.cpp
	hacdManifoldMesh.cpp)

set(HACD_HDRS
	hacdCircularList.h
	hacdGraph.h
	hacdHACD.h
	hacdICHull.h
	hacdManifoldMesh.h
	hacdVector.h
	hacdVersion.h
	hacdCircularList.inl
	hacdVector.inl)

add_library(HACD ${HACD_SRCS} ${HACD_HDRS})
set_target_properties(HACD PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(HACD PROPERTIES SOVERSION ${BULLET_VERSION})

#IF (BUILD_SHARED_LIBS)
#  TARGET_LINK_LIBRARIES(HACD BulletCollision LinearMath)
#ENDIF (BUILD_SHARED_LIBS)

if(INSTALL_EXTRA_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS HACD DESTINATION .)
		else()
			install(TARGETS HACD DESTINATION lib${LIB_SUFFIX})
			install(DIRECTORY
				${CMAKE_CURRENT_SOURCE_DIR}
				DESTINATION
				${INCLUDE_INSTALL_DIR}
				FILES_MATCHING
				PATTERN
				"*.h"
				PATTERN
				"*.inl"
				PATTERN
				".svn"
				EXCLUDE
				PATTERN
				"CMakeFiles"
				EXCLUDE)
		endif()

		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			set_target_properties(HACD PROPERTIES FRAMEWORK true)
			set_target_properties(HACD PROPERTIES PUBLIC_HEADER "${HACD_HDRS}")
		endif()
	endif()
endif()
