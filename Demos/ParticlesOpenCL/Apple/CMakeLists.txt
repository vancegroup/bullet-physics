

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


#ADD_DEFINITIONS(-DUSE_MINICL)

if(WIN32)
	if(CMAKE_CL_64)
		set(CMAK_GLEW_LIBRARY ${BULLET_PHYSICS_SOURCE_DIR}/Glut/glew64.lib)
	else()
		set(CMAK_GLEW_LIBRARY ${BULLET_PHYSICS_SOURCE_DIR}/Glut/glew32.lib)
	endif()
endif()


if(USE_GLUT)
	link_libraries(OpenGLSupport
		BulletDynamics
		BulletCollision
		LinearMath
		${OPENCL_LIBRARY}
		${GLUT_glut_LIBRARY}
		${OPENGL_gl_LIBRARY}
		${OPENGL_glu_LIBRARY}
		${CMAK_GLEW_LIBRARY})


	add_executable(AppParticlesOCL_Apple
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/btParticlesDynamicsWorld.h
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/btParticlesSharedDefs.h
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/btParticlesSharedTypes.h
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/ParticlesDemo.h
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/shaders.h
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL/btOpenCLUtils.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL/btOpenCLUtils.h
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL/btOpenCLInclude.h
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/btParticlesDemoDynamicsWorld.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/main.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/ParticlesDemo.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/shaders.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/ParticlesOCL.cl)
else()
endif()


if(WIN32)
	if(CMAKE_CL_64)
		if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
			add_custom_command(TARGET
				AppParticlesOCL_Apple
				POST_BUILD
				COMMAND
				${CMAKE_COMMAND}
				ARGS
				-E
				copy_if_different
				${BULLET_PHYSICS_SOURCE_DIR}/glut64.dll
				${CMAKE_CURRENT_BINARY_DIR})
			add_custom_command(TARGET
				AppParticlesOCL_Apple
				POST_BUILD
				COMMAND
				${CMAKE_COMMAND}
				ARGS
				-E
				copy_if_different
				${BULLET_PHYSICS_SOURCE_DIR}/GLEW64.DLL
				${CMAKE_CURRENT_BINARY_DIR})
		endif()
	else()
		if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
			add_custom_command(TARGET
				AppParticlesOCL_Apple
				POST_BUILD
				COMMAND
				${CMAKE_COMMAND}
				ARGS
				-E
				copy_if_different
				${BULLET_PHYSICS_SOURCE_DIR}/GLUT32.DLL
				${CMAKE_CURRENT_BINARY_DIR})
			add_custom_command(TARGET
				AppParticlesOCL_Apple
				POST_BUILD
				COMMAND
				${CMAKE_COMMAND}
				ARGS
				-E
				copy_if_different
				${BULLET_PHYSICS_SOURCE_DIR}/GLEW32.DLL
				${CMAKE_CURRENT_BINARY_DIR})
		endif()
	endif()
endif()

add_custom_command(TARGET
	AppParticlesOCL_Apple
	POST_BUILD
	COMMAND
	${CMAKE_COMMAND}
	ARGS
	-E
	copy_if_different
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/ParticlesOCL.cl
	${CMAKE_CURRENT_BINARY_DIR})


if(UNIX)
	target_link_libraries(AppParticlesOCL_Apple pthread)
endif()

