#MiniCL provides a small subset of OpenCL

include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${VECTOR_MATH_INCLUDE})

set(MiniCL_SRCS
	MiniCL.cpp
	MiniCLTaskScheduler.cpp
	MiniCLTask/MiniCLTask.cpp)

set(Root_HDRS
	MiniCLTaskScheduler.h
	cl.h
	cl_gl.h
	cl_platform.h
	cl_MiniCL_Defs.h)

set(MiniCLTask_HDRS MiniCLTask/MiniCLTask.h)

set(MiniCL_HDRS ${Root_HDRS} ${MiniCLTask_HDRS})

add_library(MiniCL ${MiniCL_SRCS} ${MiniCL_HDRS})
set_target_properties(MiniCL PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(MiniCL PROPERTIES SOVERSION ${BULLET_VERSION})

target_link_libraries(MiniCL
	BulletMultiThreaded
	BulletDynamics
	BulletCollision)

if(INSTALL_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS MiniCL DESTINATION .)
		else()
			install(TARGETS MiniCL DESTINATION lib${LIB_SUFFIX})
			install(DIRECTORY
				${CMAKE_CURRENT_SOURCE_DIR}
				DESTINATION
				${INCLUDE_INSTALL_DIR}
				FILES_MATCHING
				PATTERN
				"*.h"
				PATTERN
				".svn"
				EXCLUDE
				PATTERN
				"CMakeFiles"
				EXCLUDE)
		endif()

		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			set_target_properties(MiniCL PROPERTIES FRAMEWORK true)

			set_target_properties(MiniCL PROPERTIES PUBLIC_HEADER "${Root_HDRS}")
			# Have to list out sub-directories manually:
			set_property(SOURCE
				${MiniCLTask_HDRS}
				PROPERTY
				MACOSX_PACKAGE_LOCATION
				Headers/MiniCLTask)

		endif()
	endif()
endif()

