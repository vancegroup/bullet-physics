
include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src
	${BULLET_PHYSICS_SOURCE_DIR}/UnitTests/cppunit/include
	${VECTOR_MATH_INCLUDE})

add_executable(AppBulletUnitTests
	Main.cpp
	TestBulletOnly.h
	TestLinearMath.h
	TestCholeskyDecomposition.cpp
	TestCholeskyDecomposition.h
	TestPolarDecomposition.cpp
	TestPolarDecomposition.h
	btCholeskyDecomposition.cpp
	btCholeskyDecomposition.h
)

target_link_libraries(AppBulletUnitTests
	cppunit
	BulletMultiThreaded
	BulletSoftBody
	BulletDynamics
	BulletCollision
	LinearMath)


