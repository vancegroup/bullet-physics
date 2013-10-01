
include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src)

set(DXSDK_DIR $ENV{DXSDK_DIR})
set(DX11_INCLUDE_PATH
	"${DIRECTX_SDK_BASE_DIR}/Include"
	CACHE
	DOCSTRING
	"Microsoft directX SDK include path")


include_directories(${DX11_INCLUDE_PATH}
	"../Shared/"
	${VECTOR_MATH_INCLUDE})

set(BulletSoftBodyDX11Solvers_SRCS
	btSoftBodySolver_DX11.cpp
	btSoftBodySolver_DX11SIMDAware.cpp)

set(BulletSoftBodyDX11Solvers_HDRS
	btSoftBodySolver_DX11.h
	btSoftBodySolver_DX11SIMDAware.h
	../Shared/btSoftBodySolverData.h
	btSoftBodySolverVertexData_DX11.h
	btSoftBodySolverTriangleData_DX11.h
	btSoftBodySolverLinkData_DX11.h
	btSoftBodySolverLinkData_DX11SIMDAware.h
	btSoftBodySolverBuffer_DX11.h
	btSoftBodySolverVertexBuffer_DX11.h)

# OpenCL and HLSL Shaders.
# Build rules generated to stringify these into headers
# which are needed by some of the sources
set(BulletSoftBodyDX11Solvers_Shaders
	OutputToVertexArray
	UpdateNormals
	Integrate
	UpdatePositions
	UpdateNodes
	ComputeBounds
	SolvePositions
	SolvePositionsSIMDBatched
	SolveCollisionsAndUpdateVelocities
	SolveCollisionsAndUpdateVelocitiesSIMDBatched
	UpdatePositionsFromVelocities
	ApplyForces
	PrepareLinks
	VSolveLinks)

foreach(f ${BulletSoftBodyDX11Solvers_Shaders})
	list(APPEND BulletSoftBodyDX11Solvers_HLSL "HLSL/${f}.hlsl")
endforeach()



add_library(BulletSoftBodySolvers_DX11
	${BulletSoftBodyDX11Solvers_SRCS}
	${BulletSoftBodyDX11Solvers_HDRS}
	${BulletSoftBodyDX11Solvers_HLSL})
set_target_properties(BulletSoftBodySolvers_DX11
	PROPERTIES
	VERSION
	${BULLET_VERSION})
set_target_properties(BulletSoftBodySolvers_DX11
	PROPERTIES
	SOVERSION
	${BULLET_VERSION})
if(BUILD_SHARED_LIBS)
	target_link_libraries(BulletSoftBodySolvers_DX11
		BulletSoftBody
		BulletDynamics)
endif()


if(INSTALL_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS BulletSoftBodySolvers_DX11 DESTINATION .)
		else()
			install(TARGETS
				BulletSoftBodySolvers_DX11
				DESTINATION
				lib${LIB_SUFFIX})
			#headers are already installed by BulletMultiThreaded library
		endif()

		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			set_target_properties(BulletSoftBodySolvers_DX11
				PROPERTIES
				FRAMEWORK
				true)
			set_target_properties(BulletSoftBodySolvers_DX11
				PROPERTIES
				PUBLIC_HEADER
				"${BulletSoftBodyDX11Solvers_HDRS}")
		endif()
	endif()
endif()
