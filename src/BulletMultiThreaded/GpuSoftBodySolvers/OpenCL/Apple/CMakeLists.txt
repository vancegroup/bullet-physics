
include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src)




set(BulletSoftBodyOpenCLSolvers_SRCS
	../btSoftBodySolver_OpenCL.cpp
	../btSoftBodySolver_OpenCLSIMDAware.cpp)

set(BulletSoftBodyOpenCLSolvers_HDRS
	../btSoftBodySolver_OpenCL.h
	../../Shared/btSoftBodySolverData.h
	../btSoftBodySolverVertexData_OpenCL.h
	../btSoftBodySolverTriangleData_OpenCL.h
	../btSoftBodySolverLinkData_OpenCL.h
	../btSoftBodySolverBuffer_OpenCL.h)

# OpenCL and HLSL Shaders.
# Build rules generated to stringify these into headers
# which are needed by some of the sources
set(BulletSoftBodyOpenCLSolvers_Shaders
#	OutputToVertexArray
	UpdateNormals
	Integrate
	UpdatePositions
	UpdateNodes
	SolvePositions
	UpdatePositionsFromVelocities
	ApplyForces
	PrepareLinks
	VSolveLinks)

foreach(f ${BulletSoftBodyOpenCLSolvers_Shaders})
	list(APPEND BulletSoftBodyOpenCLSolvers_OpenCLC "../OpenCLC10/${f}.cl")
endforeach()



add_library(BulletSoftBodySolvers_OpenCL_Apple
	${BulletSoftBodyOpenCLSolvers_SRCS}
	${BulletSoftBodyOpenCLSolvers_HDRS}
	${BulletSoftBodyOpenCLSolvers_OpenCLC})

set_target_properties(BulletSoftBodySolvers_OpenCL_Apple
	PROPERTIES
	VERSION
	${BULLET_VERSION})
set_target_properties(BulletSoftBodySolvers_OpenCL_Apple
	PROPERTIES
	SOVERSION
	${BULLET_VERSION})
if(BUILD_SHARED_LIBS)
	if(APPLE AND (BUILD_SHARED_LIBS OR FRAMEWORK))
		set_target_properties(BulletSoftBodySolvers_OpenCL_Apple
			PROPERTIES
			LINK_FLAGS
			"-framework OpenCL")
	endif()
	target_link_libraries(BulletSoftBodySolvers_OpenCL_Apple
		BulletSoftBody)
endif()


if(INSTALL_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS BulletSoftBodySolvers_OpenCL_Apple DESTINATION .)
		else()
			install(TARGETS
				BulletSoftBodySolvers_OpenCL_Apple
				DESTINATION
				lib${LIB_SUFFIX})
			#headers are already installed by BulletMultiThreaded library
		endif()

		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			set_target_properties(BulletSoftBodySolvers_OpenCL_Apple
				PROPERTIES
				FRAMEWORK
				true)
			set_target_properties(BulletSoftBodySolvers_OpenCL_Apple
				PROPERTIES
				PUBLIC_HEADER
				"${BulletSoftBodyOpenCLSolvers_HDRS}")
		endif()
	endif()
endif()
