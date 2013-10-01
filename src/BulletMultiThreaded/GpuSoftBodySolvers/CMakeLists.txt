
include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src)


add_subdirectory(OpenCL)

if(USE_DX11)
	add_subdirectory(DX11)
endif()
