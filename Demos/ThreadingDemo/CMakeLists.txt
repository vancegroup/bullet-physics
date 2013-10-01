# This is basically the overall name of the project in Visual Studio this is the name of the Solution File


# For every executable you have with a main method you should have an add_executable line below.
# For every add executable line you should list every .cpp and .h file you have associated with that executable.


# This is the variable for Windows.  I use this to define the root of my directory structure.
set(GLUT_ROOT ${BULLET_PHYSICS_SOURCE_DIR}/Glut)

# You shouldn't have to modify anything below this line
########################################################

#currently this demo has only been tested under Windows 32bit
#IF (WIN32)

include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL
	${VECTOR_MATH_INCLUDE})

link_libraries(BulletMultiThreaded
	BulletDynamics
	BulletCollision
	LinearMath)

if(WIN32)
	add_executable(AppThreadingDemo
		main.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/build/bullet.rc)
else()
	add_executable(AppThreadingDemo main.cpp)
endif()

if(UNIX)
	target_link_libraries(AppThreadingDemo pthread)
endif()

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(AppThreadingDemo
		PROPERTIES
		DEBUG_POSTFIX
		"_Debug")
	set_target_properties(AppThreadingDemo
		PROPERTIES
		MINSIZEREL_POSTFIX
		"_MinsizeRel")
	set_target_properties(AppThreadingDemo
		PROPERTIES
		RELWITHDEBINFO_POSTFIX
		"_RelWithDebugInfo")
endif()
