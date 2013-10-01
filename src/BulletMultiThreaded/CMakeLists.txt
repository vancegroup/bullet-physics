include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${VECTOR_MATH_INCLUDE})

set(BulletMultiThreaded_SRCS
	SpuFakeDma.cpp
	SpuLibspe2Support.cpp
	btThreadSupportInterface.cpp
	Win32ThreadSupport.cpp
	PosixThreadSupport.cpp
	SequentialThreadSupport.cpp
	SpuSampleTaskProcess.cpp
	SpuCollisionObjectWrapper.cpp
	SpuCollisionTaskProcess.cpp
	SpuGatheringCollisionDispatcher.cpp
	SpuContactManifoldCollisionAlgorithm.cpp
	btParallelConstraintSolver.cpp
	
	#SPURS_PEGatherScatterTask/SpuPEGatherScatterTask.cpp
	#SpuPEGatherScatterTaskProcess.cpp

	SpuNarrowPhaseCollisionTask/boxBoxDistance.cpp
	SpuNarrowPhaseCollisionTask/SpuContactResult.cpp
	SpuNarrowPhaseCollisionTask/SpuMinkowskiPenetrationDepthSolver.cpp
	SpuNarrowPhaseCollisionTask/SpuGatheringCollisionTask.cpp
	SpuNarrowPhaseCollisionTask/SpuCollisionShapes.cpp

	#Some GPU related stuff, mainly CUDA and perhaps OpenCL
	btGpu3DGridBroadphase.cpp)

set(Root_HDRS
	PlatformDefinitions.h
	PpuAddressSpace.h
	SpuFakeDma.h
	SpuDoubleBuffer.h
	SpuLibspe2Support.h
	btThreadSupportInterface.h
	Win32ThreadSupport.h
	PosixThreadSupport.h
	SequentialThreadSupport.h
	SpuSampleTaskProcess.h
	SpuCollisionObjectWrapper.cpp
	SpuCollisionObjectWrapper.h
	SpuCollisionTaskProcess.h
	SpuGatheringCollisionDispatcher.h
	SpuContactManifoldCollisionAlgorithm.h
	btParallelConstraintSolver.h

	#SPURS_PEGatherScatterTask/SpuPEGatherScatterTask.h
	#SpuPEGatherScatterTaskProcess.h

	#Some GPU related stuff, mainly CUDA and perhaps OpenCL
	btGpu3DGridBroadphase.h
	btGpu3DGridBroadphaseSharedCode.h
	btGpu3DGridBroadphaseSharedDefs.h
	btGpu3DGridBroadphaseSharedTypes.h
	btGpuDefines.h
	btGpuUtilsSharedCode.h
	btGpuUtilsSharedDefs.h)

set(SpuNarrowPhaseCollisionTask_HDRS
	SpuNarrowPhaseCollisionTask/Box.h
	SpuNarrowPhaseCollisionTask/boxBoxDistance.h
	SpuNarrowPhaseCollisionTask/SpuContactResult.h
	SpuNarrowPhaseCollisionTask/SpuMinkowskiPenetrationDepthSolver.h
	SpuNarrowPhaseCollisionTask/SpuConvexPenetrationDepthSolver.h
	SpuNarrowPhaseCollisionTask/SpuPreferredPenetrationDirections.h
	SpuNarrowPhaseCollisionTask/SpuGatheringCollisionTask.h
	SpuNarrowPhaseCollisionTask/SpuCollisionShapes.h)

set(BulletMultiThreaded_HDRS
	${Root_HDRS}
	${SpuNarrowPhaseCollisionTask_HDRS})

add_library(BulletMultiThreaded
	${BulletMultiThreaded_SRCS}
	${BulletMultiThreaded_HDRS})
set_target_properties(BulletMultiThreaded
	PROPERTIES
	VERSION
	${BULLET_VERSION})
set_target_properties(BulletMultiThreaded
	PROPERTIES
	SOVERSION
	${BULLET_VERSION})


add_subdirectory(GpuSoftBodySolvers)


if(UNIX)
	target_link_libraries(BulletMultiThreaded
		BulletDynamics
		BulletCollision
		pthread)
else()
	target_link_libraries(BulletMultiThreaded
		BulletDynamics
		BulletCollision)
endif()


if(INSTALL_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS BulletMultiThreaded DESTINATION .)
		else()
			install(TARGETS BulletMultiThreaded DESTINATION lib${LIB_SUFFIX})
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
			set_target_properties(BulletMultiThreaded PROPERTIES FRAMEWORK true)

			set_target_properties(BulletMultiThreaded
				PROPERTIES
				PUBLIC_HEADER
				"${Root_HDRS}")
			# Have to list out sub-directories manually:
			set_property(SOURCE
				${SpuNarrowPhaseCollisionTask_HDRS}
				PROPERTY
				MACOSX_PACKAGE_LOCATION
				Headers/SpuNarrowPhaseCollisionTask)

		endif()
	endif()
endif()

