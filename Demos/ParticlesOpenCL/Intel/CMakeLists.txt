

include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL
	${INTEL_OPENCL_INCLUDES})

add_definitions(-DUSE_INTEL_OPENCL)
add_definitions(-DCL_PLATFORM_INTEL)

if(WIN32)
	add_definitions(-DGLEW_STATIC)
endif()

if(CMAKE_CL_64)
	set(CMAK_GLEW_LIBRARY ${BULLET_PHYSICS_SOURCE_DIR}/Glut/glew64s.lib)
else()
	set(CMAK_GLEW_LIBRARY ${BULLET_PHYSICS_SOURCE_DIR}/Glut/glew32s.lib)
endif()


if(USE_GLUT)
	link_libraries(OpenGLSupport
		BulletDynamics
		BulletCollision
		BulletMultiThreaded
		LinearMath
		${GLUT_glut_LIBRARY}
		${OPENGL_gl_LIBRARY}
		${OPENGL_glu_LIBRARY}
		${CMAK_GLEW_LIBRARY}
		${INTEL_OPENCL_LIBRARIES})


	add_executable(AppParticlesOCL_Intel
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
				AppParticlesOCL_Intel
				POST_BUILD
				COMMAND
				${CMAKE_COMMAND}
				ARGS
				-E
				copy_if_different
				${BULLET_PHYSICS_SOURCE_DIR}/glut64.dll
				${CMAKE_CURRENT_BINARY_DIR})
			add_custom_command(TARGET
				AppParticlesOCL_Intel
				POST_BUILD
				COMMAND
				${CMAKE_COMMAND}
				ARGS
				-E
				copy_if_different
				${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/ParticlesOCL.cl
				${CMAKE_CURRENT_BINARY_DIR})
		endif()
	else()
		if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
			add_custom_command(TARGET
				AppParticlesOCL_Intel
				POST_BUILD
				COMMAND
				${CMAKE_COMMAND}
				ARGS
				-E
				copy_if_different
				${BULLET_PHYSICS_SOURCE_DIR}/GLUT32.DLL
				${CMAKE_CURRENT_BINARY_DIR})
			add_custom_command(TARGET
				AppParticlesOCL_Intel
				POST_BUILD
				COMMAND
				${CMAKE_COMMAND}
				ARGS
				-E
				copy_if_different
				${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/ParticlesOCL.cl
				${CMAKE_CURRENT_BINARY_DIR})
		endif()
	endif()
endif()

if(UNIX)
	target_link_libraries(AppParticlesOCL_Intel pthread)
endif()

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(AppParticlesOCL_Intel
		PROPERTIES
		DEBUG_POSTFIX
		"_Debug")
	set_target_properties(AppParticlesOCL_Intel
		PROPERTIES
		MINSIZEREL_POSTFIX
		"_MinsizeRel")
	set_target_properties(AppParticlesOCL_Intel
		PROPERTIES
		RELWITHDEBINFO_POSTFIX
		"_RelWithDebugInfo")
endif()
