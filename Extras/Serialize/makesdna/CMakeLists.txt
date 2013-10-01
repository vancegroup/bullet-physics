cmake_minimum_required(VERSION 2.6.3)

if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif()

include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src)

#FILE(GLOB INC_FILES ../*.h)

set(INC_FILES
	DNA_rigidbody.h
	
	${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btVector3.h
	${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btMatrix3x3.h
	${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btTransform.h
	${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btCollisionShape.h
	${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btConvexInternalShape.h
	${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionDispatch/btCollisionObject.h)

# Build makesdna executable
set(SRC makesdna.cpp)
add_executable(makesdna ${SRC} ${INC_FILES})

# Output BulletDNA.c
add_custom_command(OUTPUT
	${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btSerializer.cpp
	COMMAND
	${CMAKE_CFG_INTDIR}/makesdna
	${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btSerializer.cpp
	${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/CommonSerialize/
	DEPENDS
	makesdna)

# Build bf_dna library
set(SRC ${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btSerializer.cpp)
add_library(BulletDNA ${SRC} ${INC_FILES})

message(STATUS "Configuring makesdna")
