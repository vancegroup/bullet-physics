

include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL)

add_definitions(-DUSE_MINICL)

#to get this to compile under linux, you could try setting CMAK_GLEW_LIBRARY
#to  /usr/lib/libGLEW.so

if(WIN32)
	add_definitions(-DGLEW_STATIC)
endif()

if(WIN32)
	if(CMAKE_CL_64)
		set(CMAK_GLEW_LIBRARY ${BULLET_PHYSICS_SOURCE_DIR}/Glut/glew64s.lib)
	else()
		set(CMAK_GLEW_LIBRARY ${BULLET_PHYSICS_SOURCE_DIR}/Glut/glew32s.lib)
	endif()
endif()

if(UNIX AND NOT APPLE)
	set(CMAK_GLEW_LIBRARY /usr/lib/libGLEW.so)
endif()

if(USE_GLUT)
	link_libraries(OpenGLSupport
		BulletDynamics
		BulletCollision
		MiniCL
		BulletMultiThreaded
		LinearMath
		${GLUT_glut_LIBRARY}
		${OPENGL_gl_LIBRARY}
		${OPENGL_glu_LIBRARY}
		${CMAK_GLEW_LIBRARY})


	add_executable(AppParticlesOCL_Mini
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/btParticlesDynamicsWorld.h
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/btParticlesSharedDefs.h
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/btParticlesSharedTypes.h
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/ParticlesDemo.h
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/btParticlesDemoDynamicsWorld.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/main.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/ParticlesDemo.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/shaders.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/shaders.h
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/MiniCL/MiniCLTaskWrap.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL/btOpenCLUtils.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL/btOpenCLUtils.h
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL/btOpenCLInclude.h
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/ParticlesOCL.cl)
else()
endif()


if(WIN32)
	if(CMAKE_CL_64)
		if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
			add_custom_command(TARGET
				AppParticlesOCL_Mini
				POST_BUILD
				COMMAND
				${CMAKE_COMMAND}
				ARGS
				-E
				copy_if_different
				${BULLET_PHYSICS_SOURCE_DIR}/glut64.dll
				${CMAKE_CURRENT_BINARY_DIR})
		endif()
	else()
		if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
			add_custom_command(TARGET
				AppParticlesOCL_Mini
				POST_BUILD
				COMMAND
				${CMAKE_COMMAND}
				ARGS
				-E
				copy_if_different
				${BULLET_PHYSICS_SOURCE_DIR}/GLUT32.DLL
				${CMAKE_CURRENT_BINARY_DIR})
		endif()
	endif()
endif()

add_custom_command(TARGET
	AppParticlesOCL_Mini
	POST_BUILD
	COMMAND
	${CMAKE_COMMAND}
	ARGS
	-E
	copy_if_different
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/ParticlesOpenCL/ParticlesOCL.cl
	${CMAKE_CURRENT_BINARY_DIR})


if(UNIX)
	target_link_libraries(AppParticlesOCL_Mini pthread)
endif()

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(AppParticlesOCL_Mini
		PROPERTIES
		DEBUG_POSTFIX
		"_Debug")
	set_target_properties(AppParticlesOCL_Mini
		PROPERTIES
		MINSIZEREL_POSTFIX
		"_MinsizeRel")
	set_target_properties(AppParticlesOCL_Mini
		PROPERTIES
		RELWITHDEBINFO_POSTFIX
		"_RelWithDebugInfo")
endif()
