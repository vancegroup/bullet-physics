
include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src)

set(LinearMath_SRCS
	btAlignedAllocator.cpp
	btConvexHull.cpp
	btConvexHullComputer.cpp
	btGeometryUtil.cpp
	btPolarDecomposition.cpp
	btQuickprof.cpp
	btSerializer.cpp
	btVector3.cpp)

set(LinearMath_HDRS
	btAabbUtil2.h
	btAlignedAllocator.h
	btAlignedObjectArray.h
	btConvexHull.h
	btConvexHullComputer.h
	btDefaultMotionState.h
	btGeometryUtil.h
	btGrahamScan2dConvexHull.h
	btHashMap.h
	btIDebugDraw.h
	btList.h
	btMatrix3x3.h
	btMinMax.h
	btMotionState.h
	btPolarDecomposition.h
	btPoolAllocator.h
	btQuadWord.h
	btQuaternion.h
	btQuickprof.h
	btRandom.h
	btScalar.h
	btSerializer.h
	btStackAlloc.h
	btTransform.h
	btTransformUtil.h
	btVector3.h)

add_library(LinearMath ${LinearMath_SRCS} ${LinearMath_HDRS})
set_target_properties(LinearMath PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(LinearMath PROPERTIES SOVERSION ${BULLET_VERSION})

if(INSTALL_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS LinearMath DESTINATION .)
		else()
			install(TARGETS LinearMath DESTINATION lib${LIB_SUFFIX})
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
			set_target_properties(LinearMath PROPERTIES FRAMEWORK true)
			set_target_properties(LinearMath
				PROPERTIES
				PUBLIC_HEADER
				"${LinearMath_HDRS}")
		endif()
	endif()
endif()
