# This is basically the overall name of the project in Visual Studio this is the name of the Solution File


# For every executable you have with a main method you should have an add_executable line below.
# For every add executable line you should list every .cpp and .h file you have associated with that executable.



# You shouldn't have to modify anything below this line
########################################################


include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL
	${VECTOR_MATH_INCLUDE})

if(WIN32)
	add_definitions(-DGLEW_STATIC)
endif()


add_executable(AppMultiThreadedDemo
	main.cpp
	MultiThreadedDemo.cpp
	MultiThreadedDemo.h)

target_link_libraries(AppMultiThreadedDemo
	OpenGLSupport
	BulletMultiThreaded
	BulletDynamics
	BulletCollision
	LinearMath
	${GLUT_glut_LIBRARY}
	${OPENGL_gl_LIBRARY}
	${OPENGL_glu_LIBRARY})

if(UNIX)
	target_link_libraries(AppMultiThreadedDemo pthread)
endif()

if(WIN32)
	if(CMAKE_CL_64)
		if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
			add_custom_command(TARGET
				AppMultiThreadedDemo
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
				AppMultiThreadedDemo
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


if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(AppMultiThreadedDemo
		PROPERTIES
		DEBUG_POSTFIX
		"_Debug")
	set_target_properties(AppMultiThreadedDemo
		PROPERTIES
		MINSIZEREL_POSTFIX
		"_MinsizeRel")
	set_target_properties(AppMultiThreadedDemo
		PROPERTIES
		RELWITHDEBINFO_POSTFIX
		"_RelWithDebugInfo")
endif()
