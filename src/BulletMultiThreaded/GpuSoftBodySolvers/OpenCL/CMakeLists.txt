add_subdirectory(MiniCL)

if(BUILD_INTEL_OPENCL_DEMOS)
	add_subdirectory(Intel)
endif()

if(BUILD_AMD_OPENCL_DEMOS)
	add_subdirectory(AMD)
endif()

if(BUILD_NVIDIA_OPENCL_DEMOS)
	add_subdirectory(NVidia)
endif()

if(APPLE AND OPENCL_LIBRARY)
	add_subdirectory(Apple)
endif()
