

include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${AMD_OPENCL_INCLUDES})

link_libraries(BulletMultiThreaded
	LinearMath
	${CMAKE_ATISTREAMSDK_LIBRARY})

add_executable(AppVectorAdd_AMD
	../MiniCL_VectorAdd.cpp
	../VectorAddKernels.cl)

if(UNIX)
	target_link_libraries(AppVectorAdd_AMD pthread)
endif()

if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
	add_custom_command(TARGET
		AppVectorAdd_AMD
		POST_BUILD
		COMMAND
		${CMAKE_COMMAND}
		ARGS
		-E
		copy_if_different
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/VectorAdd_OpenCL/VectorAddKernels.cl
		${CMAKE_CURRENT_BINARY_DIR})
endif()

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(AppVectorAdd_AMD
		PROPERTIES
		DEBUG_POSTFIX
		"_Debug")
	set_target_properties(AppVectorAdd_AMD
		PROPERTIES
		MINSIZEREL_POSTFIX
		"_MinsizeRel")
	set_target_properties(AppVectorAdd_AMD
		PROPERTIES
		RELWITHDEBINFO_POSTFIX
		"_RelWithDebugInfo")
endif()
