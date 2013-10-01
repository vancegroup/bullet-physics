

include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL
	${AMD_OPENCL_INCLUDES})

add_definitions(-DUSE_AMD_OPENCL)
add_definitions(-DCL_PLATFORM_AMD)

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
		BulletSoftBodySolvers_OpenCL_AMD
		BulletMultiThreaded
		BulletSoftBody
		BulletDynamics
		BulletCollision
		LinearMath
		${GLUT_glut_LIBRARY}
		${OPENGL_gl_LIBRARY}
		${OPENGL_glu_LIBRARY}
		${CMAK_GLEW_LIBRARY}
		${CMAKE_ATISTREAMSDK_LIBRARY})


	add_executable(AppOpenCLClothDemo_AMD
		../cl_cloth_demo.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL/btOpenCLUtils.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL/btOpenCLUtils.h
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/SharedOpenCL/btOpenCLInclude.h
		../gl_win.cpp
		../clstuff.cpp
		../clstuff.h
		../gl_win.h
		../cloth.h)	#		${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL/GLDebugDrawer.cpp
else()
endif()

if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
	if(WIN32)
		if(CMAKE_CL_64)
			add_custom_command(TARGET
				AppOpenCLClothDemo_AMD
				POST_BUILD
				COMMAND
				${CMAKE_COMMAND}
				ARGS
				-E
				copy_if_different
				${BULLET_PHYSICS_SOURCE_DIR}/glut64.dll
				${CMAKE_CURRENT_BINARY_DIR})
		else()

			add_custom_command(TARGET
				AppOpenCLClothDemo_AMD
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
	add_custom_command(TARGET
		AppOpenCLClothDemo_AMD
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
	target_link_libraries(AppOpenCLClothDemo_AMD pthread)
endif()

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(AppOpenCLClothDemo_AMD
		PROPERTIES
		DEBUG_POSTFIX
		"_Debug")
	set_target_properties(AppOpenCLClothDemo_AMD
		PROPERTIES
		MINSIZEREL_POSTFIX
		"_MinsizeRel")
	set_target_properties(AppOpenCLClothDemo_AMD
		PROPERTIES
		RELWITHDEBINFO_POSTFIX
		"_RelWithDebugInfo")
endif()
