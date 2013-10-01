# AppVectorAdd is a very basic test OpenCL/MiniCL.

if(APPLE)
	find_library(OPENCL_LIBRARY OpenCL DOC "OpenCL lib for OSX")
	find_path(OPENCL_INCLUDE_DIR
		OpenCL/cl.h
		DOC
		"Include for OpenCL on OSX")
endif()


include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src)

add_executable(AppVectorAdd_Apple
	../MiniCL_VectorAdd.cpp
	../VectorAddKernels.cl)

target_link_libraries(AppVectorAdd_Apple LinearMath ${OPENCL_LIBRARY})

if(UNIX)
	target_link_libraries(AppVectorAdd_Apple pthread)
endif()

