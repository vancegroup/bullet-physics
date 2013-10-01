# This is basically the overall name of the project in Visual Studio this is the name of the Solution File


# For every executable you have with a main method you should have an add_executable line below.
# For every add executable line you should list every .cpp and .h file you have associated with that executable.


# You shouldn't have to modify anything below this line
########################################################



include_directories(${BULLET_PHYSICS_SOURCE_DIR}/Extras
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/GIMPACTUtils
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/HACD
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/ConvexDecomposition
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/LibXML
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/LibXML/include
	${BULLET_PHYSICS_SOURCE_DIR}/src
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/BulletFileLoader
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/BulletWorldImporter
	${VECTOR_MATH_INCLUDE})

link_libraries(GLUI
	GIMPACTUtils
	HACD
	ConvexDecomposition
	OpenGLSupport
	BulletWorldImporter
	BulletSoftBody
	BulletDynamics
	BulletCollision
	BulletFileLoader
	LinearMath
	${GLUT_glut_LIBRARY}
	${OPENGL_gl_LIBRARY}
	${OPENGL_glu_LIBRARY})

set(AllBulletDemos_SRCS
	Main.cpp
	DemoEntries.cpp
	../CcdPhysicsDemo/CcdPhysicsDemo.cpp
	../BasicDemo/BasicDemo.cpp
	../BspDemo/BspDemo.cpp
	../BspDemo/BspConverter.cpp
	../BspDemo/BspLoader.cpp
	../DynamicControlDemo/MotorDemo.cpp
	../ConcaveDemo/ConcavePhysicsDemo.cpp
	../ConcaveRaycastDemo/ConcaveRaycastDemo.cpp
	../ConcaveConvexcastDemo/ConcaveConvexcastDemo.cpp
	../ConvexDecompositionDemo/ConvexDecompositionDemo.cpp
	../SliderConstraintDemo/SliderConstraintDemo.cpp
	../RagdollDemo/RagdollDemo.cpp
	../GimpactTestDemo/GimpactTestDemo.cpp
	../Raytracer/Raytracer.cpp
	../GjkConvexCastDemo/LinearConvexCastDemo.cpp
	../ForkLiftDemo/ForkLiftDemo.cpp
	../SoftDemo/SoftDemo.cpp
	../ConstraintDemo/ConstraintDemo.cpp
	../Benchmarks/BenchmarkDemo.cpp
	../Box2dDemo/Box2dDemo.cpp)

if(WIN32)
	add_executable(AppAllBulletDemos
		${AllBulletDemos_SRCS}
		${BULLET_PHYSICS_SOURCE_DIR}/build/bullet.rc)
else()
	add_executable(AppAllBulletDemos ${AllBulletDemos_SRCS})
endif()


if(WIN32)
	if(NOT INTERNAL_CREATE_MSVC_RELATIVE_PATH_PROJECTFILES)
		if(CMAKE_CL_64)
			add_custom_command(TARGET
				AppAllBulletDemos
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
				AppAllBulletDemos
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
		AppAllBulletDemos
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
	set_target_properties(AppAllBulletDemos
		PROPERTIES
		DEBUG_POSTFIX
		"_Debug")
	set_target_properties(AppAllBulletDemos
		PROPERTIES
		MINSIZEREL_POSTFIX
		"_MinsizeRel")
	set_target_properties(AppAllBulletDemos
		PROPERTIES
		RELWITHDEBINFO_POSTFIX
		"_RelWithDebugInfo")
endif()
