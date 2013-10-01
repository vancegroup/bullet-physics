include_directories(${BULLET_PHYSICS_SOURCE_DIR}/Extras/ConvexDecomposition
	${BULLET_PHYSICS_SOURCE_DIR}/src)

set(ConvexDecomposition_SRCS
	bestfitobb.cpp
	ConvexBuilder.cpp
	cd_wavefront.cpp
	fitsphere.cpp
	meshvolume.cpp
	raytri.cpp
	vlookup.cpp
	bestfit.cpp
	cd_hull.cpp
	ConvexDecomposition.cpp
	concavity.cpp
	float_math.cpp
	planetri.cpp
	splitplane.cpp)

set(ConvexDecomposition_HDRS
	ConvexDecomposition.h
	cd_vector.h
	concavity.h
	bestfitobb.h
	ConvexBuilder.h
	cd_wavefront.h
	fitsphere.h
	meshvolume.h
	raytri.h
	vlookup.h
	bestfit.h
	cd_hull.h)

add_library(ConvexDecomposition
	${ConvexDecomposition_SRCS}
	${ConvexDecomposition_HDRS})
set_target_properties(ConvexDecomposition
	PROPERTIES
	VERSION
	${BULLET_VERSION})
set_target_properties(ConvexDecomposition
	PROPERTIES
	SOVERSION
	${BULLET_VERSION})

target_link_libraries(ConvexDecomposition BulletCollision LinearMath)

if(INSTALL_EXTRA_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS ConvexDecomposition DESTINATION .)
		else()
			install(TARGETS ConvexDecomposition DESTINATION lib${LIB_SUFFIX})
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
			set_target_properties(ConvexDecomposition PROPERTIES FRAMEWORK true)
			set_target_properties(ConvexDecomposition
				PROPERTIES
				PUBLIC_HEADER
				"${ConvexDecomposition_HDRS}")
		endif()
	endif()
endif()
