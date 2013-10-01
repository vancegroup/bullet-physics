# This is basically the overall name of the project in Visual Studio this is the name of the Solution File


# For every executable you have with a main method you should have an add_executable line below.
# For every add executable line you should list every .cpp and .h file you have associated with that executable.


# This is the variable for Windows.  I use this to define the root of my directory structure.
set(GLUT_ROOT ${BULLET_PHYSICS_SOURCE_DIR}/Glut)

# You shouldn't have to modify anything below this line
########################################################

include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/HACD
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/ConvexDecomposition
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/BulletFileLoader
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/BulletWorldImporter)

if(USE_GLUT)

	link_libraries(OpenGLSupport
		BulletWorldImporter
		BulletDynamics
		BulletCollision
		LinearMath
		BulletFileLoader
		HACD
		ConvexDecomposition
		${GLUT_glut_LIBRARY}
		${OPENGL_gl_LIBRARY}
		${OPENGL_glu_LIBRARY})

	add_executable(AppConvexDecompositionDemo
		main.cpp
		ConvexDecompositionDemo.cpp
		ConvexDecompositionDemo.h)
	if(WIN32)
		if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
			if(CMAKE_CL_64)
				add_custom_command(TARGET
					AppConvexDecompositionDemo
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
					AppConvexDecompositionDemo
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
else()

	link_libraries(OpenGLSupport
		BulletWorldImporter
		BulletDynamics
		BulletCollision
		LinearMath
		BulletFileLoader
		HACD
		ConvexDecomposition
		${OPENGL_gl_LIBRARY}
		${OPENGL_glu_LIBRARY})

	add_executable(AppConvexDecompositionDemo
		WIN32
		../OpenGL/Win32AppMain.cpp
		ConvexDecompositionDemo.cpp
		ConvexDecompositionDemo.h
		Win32ConvexDecompositionDemo.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/build/bullet.rc)

endif()

if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
	add_custom_command(TARGET
		AppConvexDecompositionDemo
		POST_BUILD
		COMMAND
		${CMAKE_COMMAND}
		ARGS
		-E
		copy_if_different
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/SerializeDemo/testFile.bullet
		${CMAKE_CURRENT_BINARY_DIR}/testFile.bullet
		COMMAND
		${CMAKE_COMMAND}
		ARGS
		-E
		copy_if_different
		${BULLET_PHYSICS_SOURCE_DIR}/file.obj
		${CMAKE_CURRENT_BINARY_DIR})
endif()



if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(AppConvexDecompositionDemo
		PROPERTIES
		DEBUG_POSTFIX
		"_Debug")
	set_target_properties(AppConvexDecompositionDemo
		PROPERTIES
		MINSIZEREL_POSTFIX
		"_MinsizeRel")
	set_target_properties(AppConvexDecompositionDemo
		PROPERTIES
		RELWITHDEBINFO_POSTFIX
		"_RelWithDebugInfo")
endif()
