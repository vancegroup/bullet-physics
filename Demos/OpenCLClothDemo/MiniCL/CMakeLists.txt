

include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL)

add_definitions(-DUSE_MINICL)

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

if(USE_GLUT)
	link_libraries(OpenGLSupport
		BulletSoftBodySolvers_OpenCL_Mini
		MiniCL
		BulletMultiThreaded
		BulletSoftBody
		BulletDynamics
		BulletCollision
		LinearMath
		${GLUT_glut_LIBRARY}
		${OPENGL_gl_LIBRARY}
		${OPENGL_glu_LIBRARY}
		${CMAK_GLEW_LIBRARY})


	add_executable(AppOpenCLClothDemo_Mini
		../cl_cloth_demo.cpp
		../gl_win.cpp
		../clstuff.cpp
		../clstuff.h
		../gl_win.h
		${BULLET_PHYSICS_SOURCE_DIR}/src/BulletMultiThreaded/GpuSoftBodySolvers/OpenCL/MiniCL/MiniCLTaskWrap.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL/btOpenCLUtils.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL/btOpenCLUtils.h
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL/btOpenCLInclude.h)
else()
endif()

if(WIN32)
	if(CMAKE_CL_64)
		if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
			add_custom_command(TARGET
				AppOpenCLClothDemo_Mini
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
				AppOpenCLClothDemo_Mini
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

if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
	add_custom_command(TARGET
		AppOpenCLClothDemo_Mini
		POST_BUILD
		COMMAND
		${CMAKE_COMMAND}
		ARGS
		-E
		copy_if_different
		${BULLET_PHYSICS_SOURCE_DIR}/bullet_logo.png
		${CMAKE_CURRENT_BINARY_DIR})
endif()
if(UNIX)
	target_link_libraries(AppOpenCLClothDemo_Mini pthread)
endif()


if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(AppOpenCLClothDemo_Mini
		PROPERTIES
		DEBUG_POSTFIX
		"_Debug")
	set_target_properties(AppOpenCLClothDemo_Mini
		PROPERTIES
		MINSIZEREL_POSTFIX
		"_MinsizeRel")
	set_target_properties(AppOpenCLClothDemo_Mini
		PROPERTIES
		RELWITHDEBINFO_POSTFIX
		"_RelWithDebugInfo")
endif()
