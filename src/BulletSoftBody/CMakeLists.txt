
include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src)


set(BulletSoftBody_SRCS
	btSoftBody.cpp
	btSoftBodyConcaveCollisionAlgorithm.cpp
	btSoftBodyHelpers.cpp
	btSoftBodyRigidBodyCollisionConfiguration.cpp
	btSoftRigidCollisionAlgorithm.cpp
	btSoftRigidDynamicsWorld.cpp
	btSoftSoftCollisionAlgorithm.cpp
	btDefaultSoftBodySolver.cpp)

set(BulletSoftBody_HDRS
	btSoftBody.h
	btSoftBodyData.h
	btSoftBodyConcaveCollisionAlgorithm.h
	btSoftBodyHelpers.h
	btSoftBodyRigidBodyCollisionConfiguration.h
	btSoftRigidCollisionAlgorithm.h
	btSoftRigidDynamicsWorld.h
	btSoftSoftCollisionAlgorithm.h
	btSparseSDF.h
	btSoftBodySolvers.h
	btDefaultSoftBodySolver.h
	btSoftBodySolverVertexBuffer.h)



add_library(BulletSoftBody
	${BulletSoftBody_SRCS}
	${BulletSoftBody_HDRS})
set_target_properties(BulletSoftBody
	PROPERTIES
	VERSION
	${BULLET_VERSION})
set_target_properties(BulletSoftBody
	PROPERTIES
	SOVERSION
	${BULLET_VERSION})
if(BUILD_SHARED_LIBS)
	target_link_libraries(BulletSoftBody BulletDynamics)
endif()

if(INSTALL_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS BulletSoftBody DESTINATION .)
		else()
			install(TARGETS BulletSoftBody DESTINATION lib${LIB_SUFFIX})
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
			set_target_properties(BulletSoftBody PROPERTIES FRAMEWORK true)
			set_target_properties(BulletSoftBody
				PROPERTIES
				PUBLIC_HEADER
				"${BulletSoftBody_HDRS}")
		endif()
	endif()
endif()
