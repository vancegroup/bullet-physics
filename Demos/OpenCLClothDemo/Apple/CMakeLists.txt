

include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL)


if(APPLE)
	find_library(OPENCL_LIBRARY OpenCL DOC "OpenCL lib for OSX")
	find_path(OPENCL_INCLUDE_DIR
		OpenCL/cl.h
		DOC
		"Include for OpenCL on OSX")
endif()


if(USE_GLUT)
	link_libraries(OpenGLSupport
		BulletSoftBodySolvers_OpenCL_Apple
		BulletMultiThreaded
		BulletSoftBody
		BulletDynamics
		BulletCollision
		LinearMath
		${OPENCL_LIBRARY}
		${GLUT_glut_LIBRARY}
		${OPENGL_gl_LIBRARY}
		${OPENGL_glu_LIBRARY}
		${CMAK_GLEW_LIBRARY})


	add_executable(AppOpenCLClothDemo_Apple
		../cl_cloth_demo.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL/btOpenCLUtils.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL/btOpenCLUtils.h
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL/btOpenCLInclude.h
		../gl_win.cpp
		../clstuff.cpp
		../clstuff.h
		../gl_win.h)
else()
endif()


add_custom_command(TARGET
	AppOpenCLClothDemo_Apple
	POST_BUILD
	COMMAND
	${CMAKE_COMMAND}
	ARGS
	-E
	copy_if_different
	${BULLET_PHYSICS_SOURCE_DIR}/bullet_logo.png
	${CMAKE_CURRENT_BINARY_DIR})

if(UNIX)
	target_link_libraries(AppOpenCLClothDemo_Apple pthread)
endif()

