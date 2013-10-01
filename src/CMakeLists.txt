add_subdirectory(BulletSoftBody)
add_subdirectory(BulletCollision)
add_subdirectory(BulletDynamics)
add_subdirectory(LinearMath)

if(BUILD_MULTITHREADING)
	add_subdirectory(MiniCL)
	add_subdirectory(BulletMultiThreaded)
endif()

if(INSTALL_LIBS)
	if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
		# Don't actually need to install any common files, the frameworks include everything
	else()
		install(FILES
			btBulletCollisionCommon.h
			btBulletDynamicsCommon.h
			Bullet-C-Api.h
			DESTINATION
			${INCLUDE_INSTALL_DIR})
		install(FILES
			vectormath/vmInclude.h
			DESTINATION
			${INCLUDE_INSTALL_DIR}/vectormath)
		install(FILES
			vectormath/scalar/boolInVec.h
			vectormath/scalar/floatInVec.h
			vectormath/scalar/mat_aos.h
			vectormath/scalar/quat_aos.h
			vectormath/scalar/vec_aos.h
			vectormath/scalar/vectormath_aos.h
			DESTINATION
			${INCLUDE_INSTALL_DIR}/vectormath/scalar)
		install(FILES
			vectormath/sse/boolInVec.h
			vectormath/sse/floatInVec.h
			vectormath/sse/mat_aos.h
			vectormath/sse/quat_aos.h
			vectormath/sse/vec_aos.h
			vectormath/sse/vecidx_aos.h
			vectormath/sse/vectormath_aos.h
			DESTINATION
			${INCLUDE_INSTALL_DIR}/vectormath/sse)
	endif()
endif()
