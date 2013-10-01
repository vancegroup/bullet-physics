include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src)



set(BulletDynamics_SRCS
	Character/btKinematicCharacterController.cpp
	ConstraintSolver/btConeTwistConstraint.cpp
	ConstraintSolver/btContactConstraint.cpp
	ConstraintSolver/btGearConstraint.cpp
	ConstraintSolver/btGeneric6DofConstraint.cpp
	ConstraintSolver/btGeneric6DofSpringConstraint.cpp
	ConstraintSolver/btHinge2Constraint.cpp
	ConstraintSolver/btHingeConstraint.cpp
	ConstraintSolver/btPoint2PointConstraint.cpp
	ConstraintSolver/btSequentialImpulseConstraintSolver.cpp
	ConstraintSolver/btSliderConstraint.cpp
	ConstraintSolver/btSolve2LinearConstraint.cpp
	ConstraintSolver/btTypedConstraint.cpp
	ConstraintSolver/btUniversalConstraint.cpp
	Dynamics/btDiscreteDynamicsWorld.cpp
	Dynamics/btRigidBody.cpp
	Dynamics/btSimpleDynamicsWorld.cpp
	Dynamics/Bullet-C-API.cpp
	Vehicle/btRaycastVehicle.cpp
	Vehicle/btWheelInfo.cpp)

set(Root_HDRS ../btBulletDynamicsCommon.h ../btBulletCollisionCommon.h)
set(ConstraintSolver_HDRS
	ConstraintSolver/btConeTwistConstraint.h
	ConstraintSolver/btConstraintSolver.h
	ConstraintSolver/btContactConstraint.h
	ConstraintSolver/btContactSolverInfo.h
	ConstraintSolver/btGearConstraint.h
	ConstraintSolver/btGeneric6DofConstraint.h
	ConstraintSolver/btGeneric6DofSpringConstraint.h
	ConstraintSolver/btHinge2Constraint.h
	ConstraintSolver/btHingeConstraint.h
	ConstraintSolver/btJacobianEntry.h
	ConstraintSolver/btPoint2PointConstraint.h
	ConstraintSolver/btSequentialImpulseConstraintSolver.h
	ConstraintSolver/btSliderConstraint.h
	ConstraintSolver/btSolve2LinearConstraint.h
	ConstraintSolver/btSolverBody.h
	ConstraintSolver/btSolverConstraint.h
	ConstraintSolver/btTypedConstraint.h
	ConstraintSolver/btUniversalConstraint.h)
set(Dynamics_HDRS
	Dynamics/btActionInterface.h
	Dynamics/btDiscreteDynamicsWorld.h
	Dynamics/btDynamicsWorld.h
	Dynamics/btSimpleDynamicsWorld.h
	Dynamics/btRigidBody.h)
set(Vehicle_HDRS
	Vehicle/btRaycastVehicle.h
	Vehicle/btVehicleRaycaster.h
	Vehicle/btWheelInfo.h)

set(Character_HDRS
	Character/btCharacterControllerInterface.h
	Character/btKinematicCharacterController.h)



set(BulletDynamics_HDRS
	${Root_HDRS}
	${ConstraintSolver_HDRS}
	${Dynamics_HDRS}
	${Vehicle_HDRS}
	${Character_HDRS})


add_library(BulletDynamics
	${BulletDynamics_SRCS}
	${BulletDynamics_HDRS})
set_target_properties(BulletDynamics
	PROPERTIES
	VERSION
	${BULLET_VERSION})
set_target_properties(BulletDynamics
	PROPERTIES
	SOVERSION
	${BULLET_VERSION})

target_link_libraries(BulletDynamics BulletCollision LinearMath)


if(INSTALL_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS BulletDynamics DESTINATION .)
		else()
			install(TARGETS BulletDynamics DESTINATION lib${LIB_SUFFIX})
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
			install(FILES
				../btBulletDynamicsCommon.h
				DESTINATION
				${INCLUDE_INSTALL_DIR}/BulletDynamics)
		endif()

		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			set_target_properties(BulletDynamics PROPERTIES FRAMEWORK true)
			set_target_properties(BulletDynamics
				PROPERTIES
				PUBLIC_HEADER
				"${Root_HDRS}")
			# Have to list out sub-directories manually:
			set_property(SOURCE
				${ConstraintSolver_HDRS}
				PROPERTY
				MACOSX_PACKAGE_LOCATION
				Headers/ConstraintSolver)
			set_property(SOURCE
				${Dynamics_HDRS}
				PROPERTY
				MACOSX_PACKAGE_LOCATION
				Headers/Dynamics)
			set_property(SOURCE
				${Vehicle_HDRS}
				PROPERTY
				MACOSX_PACKAGE_LOCATION
				Headers/Vehicle)
			set_property(SOURCE
				${Character_HDRS}
				PROPERTY
				MACOSX_PACKAGE_LOCATION
				Headers/Character)

		endif()
	endif()
endif()
