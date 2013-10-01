
include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src)

add_definitions(-DUSE_MINICL)




set(BulletSoftBodyOpenCLSolvers_SRCS ../btSoftBodySolver_OpenCL.cpp)

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



add_library(BulletSoftBodySolvers_OpenCL_Mini
	${BulletSoftBodyOpenCLSolvers_SRCS}
	${BulletSoftBodyOpenCLSolvers_HDRS}
	${BulletSoftBodyOpenCLSolvers_OpenCLC})

set_target_properties(BulletSoftBodySolvers_OpenCL_Mini
	PROPERTIES
	VERSION
	${BULLET_VERSION})
set_target_properties(BulletSoftBodySolvers_OpenCL_Mini
	PROPERTIES
	SOVERSION
	${BULLET_VERSION})
if(BUILD_SHARED_LIBS)
	target_link_libraries(BulletSoftBodySolvers_OpenCL_Mini
		MiniCL
		BulletMultiThreaded
		BulletSoftBody)
endif()


if(INSTALL_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS BulletSoftBodySolvers_OpenCL_Mini DESTINATION .)
		else()
			install(TARGETS
				BulletSoftBodySolvers_OpenCL_Mini
				DESTINATION
				lib${LIB_SUFFIX})
			#headers are already installed by BulletMultiThreaded library
		endif()

		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			set_target_properties(BulletSoftBodySolvers_OpenCL_Mini
				PROPERTIES
				FRAMEWORK
				true)
			set_target_properties(BulletSoftBodySolvers_OpenCL_Mini
				PROPERTIES
				PUBLIC_HEADER
				"${BulletSoftBodyOpenCLSolvers_HDRS}")
		endif()
	endif()
endif()
