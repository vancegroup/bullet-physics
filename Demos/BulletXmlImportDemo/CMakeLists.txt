# This is basically the overall name of the project in Visual Studio this is the name of the Solution File


# For every executable you have with a main method you should have an add_executable line below.
# For every add executable line you should list every .cpp and .h file you have associated with that executable.


# This is the variable for Windows.  I use this to define the root of my directory structure.
set(GLUT_ROOT ${BULLET_PHYSICS_SOURCE_DIR}/Glut)

# You shouldn't have to modify anything below this line
########################################################


include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/BulletFileLoader
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/BulletWorldImporter
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/BulletXmlWorldImporter)

add_definitions(-DDESERIALIZE_SOFT_BODIES)

if(USE_GLUT)
	link_libraries(OpenGLSupport
		BulletXmlWorldImporter
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
		add_executable(AppBulletXmlImportDemo
			main.cpp
			BulletXmlImportDemo.cpp
			BulletXmlImportDemo.h
			${BULLET_PHYSICS_SOURCE_DIR}/build/bullet.rc)
	else()
		add_executable(AppBulletXmlImportDemo
			main.cpp
			BulletXmlImportDemo.cpp
			BulletXmlImportDemo.h)
	endif()
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(WIN32)
			if(CMAKE_CL_64)
				add_custom_command(TARGET
					AppBulletXmlImportDemo
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
					AppBulletXmlImportDemo
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
		BulletXmlWorldImporter
		BulletWorldImporter
		BulletSoftBody
		BulletDynamics
		BulletCollision
		BulletFileLoader
		LinearMath
		${OPENGL_gl_LIBRARY}
		${OPENGL_glu_LIBRARY})

	add_executable(AppBulletXmlImportDemo
		WIN32
		../OpenGL/Win32AppMain.cpp
		Win32BulletXmlImportDemo.cpp
		BulletXmlImportDemo.cpp
		BulletXmlImportDemo.h
		${BULLET_PHYSICS_SOURCE_DIR}/build/bullet.rc)
endif()

if(NOT
	INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES
	AND
	NOT
	INTERNAL_UPDATE_SERIALIZATION_STRUCTURES)
	add_custom_command(TARGET
		AppBulletXmlImportDemo
		POST_BUILD
		COMMAND
		${CMAKE_COMMAND}
		ARGS
		-E
		copy_if_different
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/BulletXmlImportDemo/bullet_basic.xml
		${CMAKE_CURRENT_BINARY_DIR}/bullet_basic.xml
		COMMAND
		${CMAKE_COMMAND}
		ARGS
		-E
		copy_if_different
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/BulletXmlImportDemo/bullet_basic.xml
		${CMAKE_CURRENT_BINARY_DIR}/Debug/bullet_basic.xml)
endif()


if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(AppBulletXmlImportDemo
		PROPERTIES
		DEBUG_POSTFIX
		"_Debug")
	set_target_properties(AppBulletXmlImportDemo
		PROPERTIES
		MINSIZEREL_POSTFIX
		"_MinsizeRel")
	set_target_properties(AppBulletXmlImportDemo
		PROPERTIES
		RELWITHDEBINFO_POSTFIX
		"_RelWithDebugInfo")
endif()


