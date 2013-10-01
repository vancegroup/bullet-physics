# This is basically the overall name of the project in Visual Studio this is the name of the Solution File


# For every executable you have with a main method you should have an add_executable line below.
# For every add executable line you should list every .cpp and .h file you have associated with that executable.



# You shouldn't have to modify anything below this line
########################################################

if(USE_GLUT)
	include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL)

	link_libraries(OpenGLSupport
		BulletDynamics
		BulletCollision
		LinearMath
		GIMPACTUtils
		ConvexDecomposition
		${GLUT_glut_LIBRARY}
		${OPENGL_gl_LIBRARY}
		${OPENGL_glu_LIBRARY})

	add_executable(AppGimpactTestDemo
		GimpactTestDemo.cpp
		GimpactTestDemo.h
		main.cpp)
	if(WIN32)
		if(CMAKE_CL_64)
			add_custom_command(TARGET
				AppGimpactTestDemo
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
				AppGimpactTestDemo
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
else()

	include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL)

	link_libraries(OpenGLSupport
		BulletDynamics
		BulletCollision
		LinearMath
		GIMPACTUtils
		ConvexDecomposition
		${OPENGL_gl_LIBRARY}
		${OPENGL_glu_LIBRARY})

	add_executable(AppGimpactTestDemo
		WIN32
		GimpactTestDemo.cpp
		GimpactTestDemo.h
		../OpenGL/Win32AppMain.cpp
		Win32GimpactDemo.cpp)
endif()
