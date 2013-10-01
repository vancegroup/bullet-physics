



include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${NVIDIA_OPENCL_INCLUDES})

add_executable(AppVectorAdd_NVidia
	../MiniCL_VectorAdd.cpp
	../VectorAddKernels.cl)

target_link_libraries(AppVectorAdd_NVidia LinearMath ${NVIDIA_OPENCL_LIBRARIES})

if(UNIX)
	target_link_libraries(AppVectorAdd_NVidia pthread)
endif()

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(AppVectorAdd_NVidia
		PROPERTIES
		DEBUG_POSTFIX
		"_Debug")
	set_target_properties(AppVectorAdd_NVidia
		PROPERTIES
		MINSIZEREL_POSTFIX
		"_MinsizeRel")
	set_target_properties(AppVectorAdd_NVidia
		PROPERTIES
		RELWITHDEBINFO_POSTFIX
		"_RelWithDebugInfo")
endif()
