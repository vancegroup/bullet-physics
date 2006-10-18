/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2006 Erwin Coumans  http://continuousphysics.com/Bullet/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef BT_DISCRETE_DYNAMICS_WORLD_H
#define BT_DISCRETE_DYNAMICS_WORLD_H

#include "btDynamicsWorld.h"

class btDispatcher;
class btOverlappingPairCache;
class btConstraintSolver;
class btSimulationIslandManager;
class btTypedConstraint;
struct btContactSolverInfo;
class btRaycastVehicle;
class btIDebugDraw;

#include <vector>

///btDiscreteDynamicsWorld provides discrete rigid body simulation
///those classes replace the obsolete CcdPhysicsEnvironment/CcdPhysicsController
class btDiscreteDynamicsWorld : public btDynamicsWorld
{
protected:

	btConstraintSolver*	m_constraintSolver;

	btSimulationIslandManager*	m_islandManager;

	std::vector<btTypedConstraint*> m_constraints;

	btIDebugDraw*	m_debugDrawer;

	btVector3	m_gravity;

	//for variable timesteps
	float	m_localTime;
	//for variable timesteps

	bool	m_ownsIslandManager;
	bool	m_ownsConstraintSolver;

	std::vector<btRaycastVehicle*>	m_vehicles;

	int	m_profileTimings;

	void	predictUnconstraintMotion(float timeStep);
	
	void	integrateTransforms(float timeStep);
		
	void	calculateSimulationIslands();

	void	solveNoncontactConstraints(btContactSolverInfo& solverInfo);

	void	solveContactConstraints(btContactSolverInfo& solverInfo);

	void	updateActivationState(float timeStep);

	void	updateVehicles(float timeStep);

	void	startProfiling(float timeStep);

	virtual void	internalSingleStepSimulation( float timeStep);

	void	synchronizeMotionStates();

	void	saveKinematicState(float timeStep);


public:


	///this btDiscreteDynamicsWorld constructor gets created objects from the user, and will not delete those
	btDiscreteDynamicsWorld(btDispatcher* dispatcher,btOverlappingPairCache* pairCache,btConstraintSolver* constraintSolver=0);

	///this btDiscreteDynamicsWorld will create and own dispatcher, pairCache and constraintSolver, and deletes it in the destructor.
	btDiscreteDynamicsWorld();
		
	virtual ~btDiscreteDynamicsWorld();

	///if maxSubSteps > 0, it will interpolate motion between fixedTimeStep's
	virtual int	stepSimulation( float timeStep,int maxSubSteps=1, float fixedTimeStep=1.f/60.f);

	virtual void	updateAabbs();

	void	addConstraint(btTypedConstraint* constraint);

	void	removeConstraint(btTypedConstraint* constraint);

	void	addVehicle(btRaycastVehicle* vehicle);

	void	removeVehicle(btRaycastVehicle* vehicle);

	btSimulationIslandManager*	getSimulationIslandManager()
	{
		return m_islandManager;
	}

	const btSimulationIslandManager*	getSimulationIslandManager() const 
	{
		return m_islandManager;
	}

	btCollisionWorld*	getCollisionWorld()
	{
		return this;
	}

	virtual void	setDebugDrawer(btIDebugDraw*	debugDrawer)
	{
			m_debugDrawer = debugDrawer;
	}

	virtual btIDebugDraw*	getDebugDrawer()
	{
		return m_debugDrawer;
	}

	virtual void	setGravity(const btVector3& gravity);

	virtual void	addRigidBody(btRigidBody* body);

	virtual void	removeRigidBody(btRigidBody* body);

	void	debugDrawObject(const btTransform& worldTransform, const btCollisionShape* shape, const btVector3& color);


};

#endif //BT_DISCRETE_DYNAMICS_WORLD_H
