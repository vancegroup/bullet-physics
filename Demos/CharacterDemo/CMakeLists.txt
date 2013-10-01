# This is basically the overall name of the project in Visual Studio this is the name of the Solution File


# For every executable you have with a main method you should have an add_executable line below.
# For every add executable line you should list every .cpp and .h file you have associated with that executable.


# You shouldn't have to modify anything below this line
########################################################


include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL)

link_libraries(OpenGLSupport
	BulletDynamics
	BulletCollision
	LinearMath
	${GLUT_glut_LIBRARY}
	${OPENGL_gl_LIBRARY}
	${OPENGL_glu_LIBRARY})
set(CharacterDemo_SRCS
	DynamicCharacterController.cpp
	DynamicCharacterController.h
	CharacterDemo.cpp
	CharacterDemo.h
	../BspDemo/BspConverter.cpp
	../BspDemo/BspConverter.h
	../BspDemo/BspLoader.cpp
	../BspDemo/BspLoader.h
	main.cpp)

if(WIN32)
	add_executable(AppCharacterDemo
		${CharacterDemo_SRCS}
		${BULLET_PHYSICS_SOURCE_DIR}/build/bullet.rc)
else()
	add_executable(AppCharacterDemo ${CharacterDemo_SRCS})
endif()

if(WIN32)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(CMAKE_CL_64)
			add_custom_command(TARGET
				AppCharacterDemo
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
				AppCharacterDemo
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
		AppCharacterDemo
		POST_BUILD
		COMMAND
		${CMAKE_COMMAND}
		ARGS
		-E
		copy_if_different
		${BULLET_PHYSICS_SOURCE_DIR}/BspDemo.bsp
		${CMAKE_CURRENT_BINARY_DIR})
endif()



if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(AppCharacterDemo
		PROPERTIES
		DEBUG_POSTFIX
		"_Debug")
	set_target_properties(AppCharacterDemo
		PROPERTIES
		MINSIZEREL_POSTFIX
		"_MinsizeRel")
	set_target_properties(AppCharacterDemo
		PROPERTIES
		RELWITHDEBINFO_POSTFIX
		"_RelWithDebugInfo")
endif()
