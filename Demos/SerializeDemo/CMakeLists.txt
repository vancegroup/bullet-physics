# This is basically the overall name of the project in Visual Studio this is the name of the Solution File


# For every executable you have with a main method you should have an add_executable line below.
# For every add executable line you should list every .cpp and .h file you have associated with that executable.


# This is the variable for Windows.  I use this to define the root of my directory structure.
set(GLUT_ROOT ${BULLET_PHYSICS_SOURCE_DIR}/Glut)

# You shouldn't have to modify anything below this line
########################################################

if(BUILD_AMD_OPENCL_DEMOS AND BUILD_MULTITHREADING)
	add_subdirectory(AMD)
endif()

include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/BulletFileLoader
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/BulletWorldImporter)

add_definitions(-DDESERIALIZE_SOFT_BODIES)

if(USE_GLUT)
	link_libraries(OpenGLSupport
		BulletWorldImporter
		BulletSoftBody
		BulletDynamics
		BulletCollision
		BulletFileLoader
		LinearMath
		${GLUT_glut_LIBRARY}
		${OPENGL_gl_LIBRARY}
		${OPENGL_glu_LIBRARY})

	if(WIN32)
		add_executable(AppSerializeDemo
			main.cpp
			SerializeDemo.cpp
			SerializeDemo.h
			${BULLET_PHYSICS_SOURCE_DIR}/build/bullet.rc)
	else()
		add_executable(AppSerializeDemo
			main.cpp
			SerializeDemo.cpp
			SerializeDemo.h)
	endif()
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(WIN32)
			if(CMAKE_CL_64)
				add_custom_command(TARGET
					AppSerializeDemo
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
					AppSerializeDemo
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
		BulletSoftBody
		BulletDynamics
		BulletCollision
		BulletFileLoader
		LinearMath
		${OPENGL_gl_LIBRARY}
		${OPENGL_glu_LIBRARY})

	add_executable(AppSerializeDemo
		WIN32
		../OpenGL/Win32AppMain.cpp
		Win32SerializeDemo.cpp
		SerializeDemo.cpp
		SerializeDemo.h
		${BULLET_PHYSICS_SOURCE_DIR}/build/bullet.rc)
endif()

if(NOT
	INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES
	AND
	NOT
	INTERNAL_UPDATE_SERIALIZATION_STRUCTURES)
	add_custom_command(TARGET
		AppSerializeDemo
		POST_BUILD
		COMMAND
		${CMAKE_COMMAND}
		ARGS
		-E
		copy_if_different
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/SerializeDemo/testFile.bullet
		${CMAKE_CURRENT_BINARY_DIR}/testFile.bullet)
endif()


if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(AppSerializeDemo
		PROPERTIES
		DEBUG_POSTFIX
		"_Debug")
	set_target_properties(AppSerializeDemo
		PROPERTIES
		MINSIZEREL_POSTFIX
		"_MinsizeRel")
	set_target_properties(AppSerializeDemo
		PROPERTIES
		RELWITHDEBINFO_POSTFIX
		"_RelWithDebugInfo")
endif()


