
if(USE_DX11 AND BUILD_MULTITHREADING)
	add_subdirectory(DX11ClothDemo)
endif()

add_subdirectory(HelloWorld)


if(USE_GLUT)
	if(GLUT_FOUND)
		if(BUILD_CPU_DEMOS)
			set(SharedDemoSubdirs
				OpenGL
				AllBulletDemos
				ConvexDecompositionDemo
				CcdPhysicsDemo
				BulletXmlImportDemo
				ConstraintDemo
				SliderConstraintDemo
				GenericJointDemo
				Raytracer
				RagdollDemo
				ForkLiftDemo
				BasicDemo
				RollingFrictionDemo
				RaytestDemo
				VoronoiFractureDemo
				GyroscopicDemo
				FractureDemo
				Box2dDemo
				BspDemo
				MovingConcaveDemo
				VehicleDemo
				UserCollisionAlgorithm
				CharacterDemo
				SoftDemo
				CollisionInterfaceDemo
				ConcaveConvexcastDemo
				SimplexDemo
				DynamicControlDemo
				ConvexHullDistance
				DoublePrecisionDemo
				ConcaveDemo
				CollisionDemo
				ContinuousConvexCollision
				ConcaveRaycastDemo
				GjkConvexCastDemo
				MultiMaterialDemo
				SerializeDemo
				InternalEdgeDemo)
		else()
			set(SharedDemoSubdirs OpenGL)
		endif()

		if(BUILD_MULTITHREADING)
			add_subdirectory(MultiThreadedDemo)
			add_subdirectory(ParticlesOpenCL)
			add_subdirectory(OpenCLClothDemo)
		endif()

		add_subdirectory(${SharedDemoSubdirs})
		add_subdirectory(Benchmarks)

		if(BUILD_MULTITHREADING)
			add_subdirectory(ThreadingDemo)
			add_subdirectory(VectorAdd_OpenCL)
		endif()

	endif()
else()
	if(WIN32)
		add_subdirectory(OpenGL)
		add_subdirectory(BasicDemo)
		add_subdirectory(RaytestDemo)
		add_subdirectory(FractureDemo)
		add_subdirectory(Benchmarks)
		add_subdirectory(Box2dDemo)
		add_subdirectory(CollisionInterfaceDemo)
		add_subdirectory(ConcaveDemo)
		add_subdirectory(ConstraintDemo)
		add_subdirectory(RollingFrictionDemo)
		add_subdirectory(ConvexDecompositionDemo)
		add_subdirectory(InternalEdgeDemo)
		add_subdirectory(GimpactTestDemo)
		add_subdirectory(GyroscopicDemo)
		add_subdirectory(GenericJointDemo)
		add_subdirectory(SerializeDemo)
		add_subdirectory(SoftDemo)
		add_subdirectory(VectorAdd_OpenCL)
		add_subdirectory(VoronoiFractureDemo)
	endif()
endif()

