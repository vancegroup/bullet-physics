# This is basically the overall name of the project in Visual Studio this is the name of the Solution File


# For every executable you have with a main method you should have an add_executable line below.
# For every add executable line you should list every .cpp and .h file you have associated with that executable.


# You shouldn't have to modify anything below this line
########################################################

if(USE_GRAPHICAL_BENCHMARK)
	if(USE_GLUT)
		include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
			${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL)

		if(USE_MULTITHREADED_BENCHMARK)
			include_directories(${VECTOR_MATH_INCLUDE})
			link_libraries(OpenGLSupport
				BulletMultiThreaded
				BulletDynamics
				BulletCollision
				LinearMath
				${GLUT_glut_LIBRARY}
				${OPENGL_gl_LIBRARY}
				${OPENGL_glu_LIBRARY})
		else()
			link_libraries(OpenGLSupport
				BulletDynamics
				BulletCollision
				LinearMath
				${GLUT_glut_LIBRARY}
				${OPENGL_gl_LIBRARY}
				${OPENGL_glu_LIBRARY})
		endif()

		if(WIN32)
			add_executable(AppBenchmarks
				main.cpp
				BenchmarkDemo.cpp
				BenchmarkDemo.h
				${BULLET_PHYSICS_SOURCE_DIR}/build/bullet.rc)
		else()
			add_executable(AppBenchmarks
				main.cpp
				BenchmarkDemo.cpp
				BenchmarkDemo.h)
		endif()
		if(WIN32)
			if(NOT INTERNAL_CREATE_MSVC_RELATIVE_PATH_PROJECTFILES)
				if(CMAKE_CL_64)
					add_custom_command(TARGET
						AppBenchmarks
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
						AppBenchmarks
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
			if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
				set_target_properties(AppBenchmarks
					PROPERTIES
					DEBUG_POSTFIX
					"_Debug")
				set_target_properties(AppBenchmarks
					PROPERTIES
					MINSIZEREL_POSTFIX
					"_MinsizeRel")
				set_target_properties(AppBenchmarks
					PROPERTIES
					RELWITHDEBINFO_POSTFIX
					"_RelWithDebugInfo")
			endif()

		endif()
	else()
		include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
			${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL)

		if(USE_MULTITHREADED_BENCHMARK)
			include_directories(${VECTOR_MATH_INCLUDE})
			link_libraries(OpenGLSupport
				BulletMultiThreaded
				BulletDynamics
				BulletCollision
				LinearMath
				${OPENGL_gl_LIBRARY}
				${OPENGL_glu_LIBRARY})
		else()
			link_libraries(OpenGLSupport
				BulletDynamics
				BulletCollision
				LinearMath
				${OPENGL_gl_LIBRARY}
				${OPENGL_glu_LIBRARY})

		endif()

		add_executable(AppBenchmarks
			WIN32
			../OpenGL/Win32AppMain.cpp
			BenchmarkDemo.cpp
			BenchmarkDemo.h
			Win32BenchmarkDemo.cpp
			${BULLET_PHYSICS_SOURCE_DIR}/build/bullet.rc)
	endif()
else()

	include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL)

	if(USE_MULTITHREADED_BENCHMARK)
		link_libraries(BulletMultiThreaded
			BulletDynamics
			BulletCollision
			LinearMath)
	else()
		link_libraries(BulletDynamics BulletCollision LinearMath)
	endif()


	add_executable(AppBenchmarks main.cpp BenchmarkDemo.cpp)
endif()
