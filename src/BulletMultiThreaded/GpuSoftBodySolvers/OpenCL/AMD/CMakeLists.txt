
include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${AMD_OPENCL_INCLUDES})

add_definitions(-DUSE_AMD_OPENCL)
add_definitions(-DCL_PLATFORM_AMD)



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




add_library(BulletSoftBodySolvers_OpenCL_AMD
	${BulletSoftBodyOpenCLSolvers_SRCS}
	${BulletSoftBodyOpenCLSolvers_HDRS})

set_target_properties(BulletSoftBodySolvers_OpenCL_AMD
	PROPERTIES
	VERSION
	${BULLET_VERSION})
set_target_properties(BulletSoftBodySolvers_OpenCL_AMD
	PROPERTIES
	SOVERSION
	${BULLET_VERSION})
if(BUILD_SHARED_LIBS)
	target_link_libraries(BulletSoftBodySolvers_OpenCL_AMD BulletSoftBody)
endif()


if(INSTALL_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS BulletSoftBodySolvers_OpenCL_AMD DESTINATION .)
		else()
			install(TARGETS
				BulletSoftBodySolvers_OpenCL_AMD
				DESTINATION
				lib${LIB_SUFFIX})
			#headers are already installed by BulletMultiThreaded library
		endif()

		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			set_target_properties(BulletSoftBodySolvers_OpenCL_AMD
				PROPERTIES
				FRAMEWORK
				true)
			set_target_properties(BulletSoftBodySolvers_OpenCL_AMD
				PROPERTIES
				PUBLIC_HEADER
				"${BulletSoftBodyOpenCLSolvers_HDRS}")
		endif()
	endif()
endif()
