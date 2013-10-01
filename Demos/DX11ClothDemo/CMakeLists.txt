cmake_minimum_required(VERSION 2.4)


#this line has to appear before 'PROJECT' in order to be able to disable incremental linking
set(MSVC_INCREMENTAL_DEFAULT ON)

project(AppDX11ClothDemo)
set(BULLET_VERSION 2.76)

if(NOT CMAKE_BUILD_TYPE)
	# SET(CMAKE_BUILD_TYPE "Debug")
	set(CMAKE_BUILD_TYPE "Release")
endif()


option(USE_MSVC_RUNTIME_LIBRARY_DLL
	"Use MSVC Runtime Library DLL (/MD or /MDd)"
	ON)
option(USE_MSVC_INCREMENTAL_LINKING "Use MSVC Incremental Linking" OFF)



if(MSVC)
	if(NOT USE_MSVC_INCREMENTAL_LINKING)
		#MESSAGE("MSVC_INCREMENTAL_DEFAULT"+${MSVC_INCREMENTAL_DEFAULT})
		set(MSVC_INCREMENTAL_YES_FLAG "/INCREMENTAL:NO")

		string(REPLACE
			"INCREMENTAL:YES"
			"INCREMENTAL:NO"
			replacementFlags
			${CMAKE_EXE_LINKER_FLAGS_DEBUG})
		set(CMAKE_EXE_LINKER_FLAGS_DEBUG
			"/INCREMENTAL:NO ${replacementFlags}")
		message("CMAKE_EXE_LINKER_FLAGS_DEBUG=${CMAKE_EXE_LINKER_FLAGS_DEBUG}")

		string(REPLACE
			"INCREMENTAL:YES"
			"INCREMENTAL:NO"
			replacementFlags3
			${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO})
		set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO ${replacementFlags3})
		set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO
			"/INCREMENTAL:NO ${replacementFlags3}")
	endif()

	if(NOT USE_MSVC_RUNTIME_LIBRARY_DLL)
		#We statically link to reduce dependancies
		foreach(flag_var
			CMAKE_CXX_FLAGS
			CMAKE_CXX_FLAGS_DEBUG
			CMAKE_CXX_FLAGS_RELEASE
			CMAKE_CXX_FLAGS_MINSIZEREL
			CMAKE_CXX_FLAGS_RELWITHDEBINFO)
			if(${flag_var} MATCHES "/MD")
				string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
			endif()
			if(${flag_var} MATCHES "/MDd")
				string(REGEX REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}")
			endif()
		endforeach()
	endif()

	if(CMAKE_CL_64)
		add_definitions(-D_WIN64)
	else()
		option(USE_MSVC_SSE "Use MSVC /arch:sse option" ON)
		if(USE_MSVC_SSE)
			add_definitions(/arch:SSE)
		endif()
	endif()
	option(USE_MSVC_FAST_FLOATINGPOINT "Use MSVC /fp:fast option" ON)
	if(USE_MSVC_FAST_FLOATINGPOINT)
		add_definitions(/fp:fast)
	endif()
endif()


if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif()




set(DXSDK_DIR $ENV{DXSDK_DIR})
set(DX11_INCLUDE_PATH
	"${DXSDK_DIR}Include"
	CACHE
	DOCSTRING
	"Microsoft directX SDK include path")
if(CMAKE_CL_64)
	set(DX11_LIB_PATH
		"${DXSDK_DIR}Lib/x64"
		CACHE
		DOCSTRING
		"Microsoft DirectX SDK library path")
else()
	set(DX11_LIB_PATH
		"${DXSDK_DIR}Lib/x86"
		CACHE
		DOCSTRING
		"Microsoft DirectX SDK library path")
endif()

set(BulletClothExample_SRCS
	DXUT/Core/DXUT.cpp
	DXUT/Optional/DXUTcamera.cpp
	DXUT/Core/DXUTDevice11.cpp
	DXUT/Core/DXUTDevice9.cpp
	DXUT/Optional/DXUTgui.cpp
	DXUT/Core/DXUTmisc.cpp
	DXUT/Optional/DXUTres.cpp
	DXUT/Optional/DXUTsettingsdlg.cpp
	DXUT/Optional/SDKmesh.cpp
	DXUT/Optional/SDKmisc.cpp
	cloth_renderer.cpp)


set(BulletClothExample_HDRS
	DXUT/Core/DXUT.h
	DXUT/Optional/DXUTcamera.h
	DXUT/Core/DXUTDevice11.h
	DXUT/Core/DXUTDevice9.h
	DXUT/Optional/DXUTgui.h
	DXUT/Core/DXUTmisc.h
	DXUT/Optional/DXUTres.h
	DXUT/Optional/DXUTsettingsdlg.h
	DXUT/Optional/SDKmesh.h
	DXUT/Optional/SDKmisc.h
	btDirectComputeSupport.h
	cap.h
	cloth.h
	cylinder.h
	resource.h)	#	FreeImage.h


include_directories(${DX11_INCLUDE_PATH}
	${BULLET_PHYSICS_SOURCE_DIR}/src
	"DXUT/Core"
	"DXUT/Optional"
	${VECTOR_MATH_INCLUDE})
link_directories(${DX11_LIB_PATH})

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

add_executable(AppDX11ClothDemo
	WIN32
	${BulletClothExample_SRCS}
	${BulletClothExample_HDRS})
target_link_libraries(AppDX11ClothDemo
	d3dcompiler
	dxerr
	dxguid
	d3dx9
	d3d9
	winmm
	comctl32
	d3dx11
	BulletDynamics
	BulletCollision
	LinearMath
	BulletSoftBody
	BulletSoftBodySolvers_DX11)

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(AppDX11ClothDemo
		PROPERTIES
		DEBUG_POSTFIX
		"_Debug")
	set_target_properties(AppDX11ClothDemo
		PROPERTIES
		MINSIZEREL_POSTFIX
		"_MinsizeRel")
	set_target_properties(AppDX11ClothDemo
		PROPERTIES
		RELWITHDEBINFO_POSTFIX
		"_RelWithDebugInfo")
endif()


if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
	add_custom_command(TARGET
		AppDX11ClothDemo
		POST_BUILD
		COMMAND
		${CMAKE_COMMAND}
		ARGS
		-E
		copy_if_different
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/DX11ClothDemo/cloth_renderer_PS.hlsl
		${CMAKE_CURRENT_BINARY_DIR}/cloth_renderer_PS.hlsl
		COMMAND
		${CMAKE_COMMAND}
		ARGS
		-E
		copy_if_different
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/DX11ClothDemo/cloth_renderer_VS.hlsl
		${CMAKE_CURRENT_BINARY_DIR}/cloth_renderer_VS.hlsl
		COMMAND
		${CMAKE_COMMAND}
		ARGS
		-E
		copy_if_different
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/DX11ClothDemo/texture.bmp
		${CMAKE_CURRENT_BINARY_DIR}/texture.bmp
		COMMAND
		${CMAKE_COMMAND}
		ARGS
		-E
		copy_if_different
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/DX11ClothDemo/amdFlag.bmp
		${CMAKE_CURRENT_BINARY_DIR}/amdFlag.bmp
		COMMAND
		${CMAKE_COMMAND}
		ARGS
		-E
		copy_if_different
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/DX11ClothDemo/atiFlag.bmp
		${CMAKE_CURRENT_BINARY_DIR}/atiFlag.bmp
		COMMAND
		${CMAKE_COMMAND}
		ARGS
		-E
		copy_if_different
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/DX11ClothDemo/texture.png
		${CMAKE_CURRENT_BINARY_DIR}/texture.png
		COMMAND
		${CMAKE_COMMAND}
		ARGS
		-E
		copy_if_different
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/DX11ClothDemo/Media/UI/Font.dds
		${CMAKE_CURRENT_BINARY_DIR}/Media/UI/Font.dds
		COMMAND
		${CMAKE_COMMAND}
		ARGS
		-E
		copy_if_different
		${BULLET_PHYSICS_SOURCE_DIR}/Demos/DX11ClothDemo/Media/Tiny/tiny.sdkmesh
		${CMAKE_CURRENT_BINARY_DIR}/Media/Tiny/tiny.sdkmesh)
endif()

