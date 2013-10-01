
include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${INTEL_OPENCL_INCLUDES})

add_definitions(-DUSE_INTEL_OPENCL)
add_definitions(-DCL_PLATFORM_INTEL)



set(BulletSoftBodyOpenCLSolvers_SRCS
	../btSoftBodySolver_OpenCL.cpp
	../btSoftBodySolver_OpenCLSIMDAware.cpp
	../btSoftBodySolverOutputCLtoGL.cpp)

set(BulletSoftBodyOpenCLSolvers_HDRS
	../btSoftBodySolver_OpenCL.h
	../btSoftBodySolver_OpenCLSIMDAware.h
	../../Shared/btSoftBodySolverData.h
	../btSoftBodySolverVertexData_OpenCL.h
	../btSoftBodySolverTriangleData_OpenCL.h
	../btSoftBodySolverLinkData_OpenCL.h
	../btSoftBodySolverLinkData_OpenCLSIMDAware.h
	../btSoftBodySolverBuffer_OpenCL.h
	../btSoftBodySolverVertexBuffer_OpenGL.h
	../btSoftBodySolverOutputCLtoGL.h)

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



add_library(BulletSoftBodySolvers_OpenCL_Intel
	${BulletSoftBodyOpenCLSolvers_SRCS}
	${BulletSoftBodyOpenCLSolvers_HDRS}
	${BulletSoftBodyOpenCLSolvers_OpenCLC})

set_target_properties(BulletSoftBodySolvers_OpenCL_Intel
	PROPERTIES
	VERSION
	${BULLET_VERSION})
set_target_properties(BulletSoftBodySolvers_OpenCL_Intel
	PROPERTIES
	SOVERSION
	${BULLET_VERSION})
if(BUILD_SHARED_LIBS)
	target_link_libraries(BulletSoftBodySolvers_OpenCL_Intel
		BulletSoftBody)
endif()


if(INSTALL_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS BulletSoftBodySolvers_OpenCL_Intel DESTINATION .)
		else()
			install(TARGETS
				BulletSoftBodySolvers_OpenCL_Intel
				DESTINATION
				lib${LIB_SUFFIX})
			#headers are already installed by BulletMultiThreaded library
		endif()

		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			set_target_properties(BulletSoftBodySolvers_OpenCL_Intel
				PROPERTIES
				FRAMEWORK
				true)
			set_target_properties(BulletSoftBodySolvers_OpenCL_Intel
				PROPERTIES
				PUBLIC_HEADER
				"${BulletSoftBodyOpenCLSolvers_HDRS}")
		endif()
	endif()
endif()
