# This is basically the overall name of the project in Visual Studio this is the name of the Solution File


# For every executable you have with a main method you should have an add_executable line below.
# For every add executable line you should list every .cpp and .h file you have associated with that executable.



# You shouldn't have to modify anything below this line
########################################################



include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL)

if(WIN32)
	add_executable(AppCcdPhysicsDemo
		main.cpp
		CcdPhysicsDemo.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/build/bullet.rc)
else()
	add_executable(AppCcdPhysicsDemo main.cpp CcdPhysicsDemo.cpp)
endif()

target_link_libraries(AppCcdPhysicsDemo
	OpenGLSupport
	BulletDynamics
	BulletCollision
	LinearMath
	${GLUT_glut_LIBRARY}
	${OPENGL_gl_LIBRARY}
	${OPENGL_glu_LIBRARY})

if(WIN32)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(CMAKE_CL_64)
			add_custom_command(TARGET
				AppCcdPhysicsDemo
				POST_BUILD
				COMMAND
				${CMAKE_COMMAND}
				ARGS
				-E
				copy_if_different
				${BULLET_PHYSICS_SOURCE_DIR}/glut64.dll
				${CMAKE_CURRENT_BINARY_DIR}
				COMMAND
				${CMAKE_COMMAND}
				ARGS
				-E
				copy_if_different
				${BULLET_PHYSICS_SOURCE_DIR}/glut64.dll
				${CMAKE_CURRENT_BINARY_DIR}/Debug)
		else()
			add_custom_command(TARGET
				AppCcdPhysicsDemo
				POST_BUILD
				COMMAND
				${CMAKE_COMMAND}
				ARGS
				-E
				copy_if_different
				${BULLET_PHYSICS_SOURCE_DIR}/GLUT32.DLL
				${CMAKE_CURRENT_BINARY_DIR}
				COMMAND
				${CMAKE_COMMAND}
				ARGS
				-E
				copy_if_different
				${BULLET_PHYSICS_SOURCE_DIR}/GLUT32.DLL
				${CMAKE_CURRENT_BINARY_DIR}/Debug)
		endif()
	endif()
endif()

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(AppCcdPhysicsDemo
		PROPERTIES
		DEBUG_POSTFIX
		"_Debug")
	set_target_properties(AppCcdPhysicsDemo
		PROPERTIES
		MINSIZEREL_POSTFIX
		"_MinsizeRel")
	set_target_properties(AppCcdPhysicsDemo
		PROPERTIES
		RELWITHDEBINFO_POSTFIX
		"_RelWithDebugInfo")
endif()
