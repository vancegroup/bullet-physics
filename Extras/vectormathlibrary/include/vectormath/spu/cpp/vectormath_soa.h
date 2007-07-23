/*
   Copyright (C) 2006, 2007 Sony Computer Entertainment Inc.
   All rights reserved.

   Redistribution and use in source and binary forms,
   with or without modification, are permitted provided that the
   following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Sony Computer Entertainment Inc nor the names
      of its contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _VECTORMATH_SOA_CPP_H
#define _VECTORMATH_SOA_CPP_H

#include <math.h>
#include <spu_intrinsics.h>
#include "floatInVec.h"
#include "boolInVec.h"
#include "stdio.h"
#include "vectormath_aos.h"

#ifdef _VECTORMATH_DEBUG
#endif

namespace Vectormath {

namespace Soa {

//-----------------------------------------------------------------------------
// Forward Declarations
//

class Vector3;
class Vector4;
class Point3;
class Quat;
class Matrix3;
class Matrix4;
class Transform3;

// A set of four 3-D vectors in structure-of-arrays format
//
class Vector3
{
    typedef vec_float4 vec_float4_t;
    vec_float4 mX;
    vec_float4 mY;
    vec_float4 mZ;

public:
    // Default constructor; does no initialization
    // 
    inline Vector3( ) { };

    // Copy a 3-D vector
    // 
    inline Vector3( const Vector3 & vec );

    // Construct a 3-D vector from x, y, and z elements
    // 
    inline Vector3( vec_float4 x, vec_float4 y, vec_float4 z );

    // Copy elements from a 3-D point into a 3-D vector
    // 
    explicit inline Vector3( const Point3 & pnt );

    // Set all elements of a 3-D vector to the same scalar value
    // 
    explicit inline Vector3( vec_float4 scalar );

    // Replicate an AoS 3-D vector
    // 
    inline Vector3( Aos::Vector3 vec );

    // Insert four AoS 3-D vectors
    // 
    inline Vector3( Aos::Vector3 vec0, Aos::Vector3 vec1, Aos::Vector3 vec2, Aos::Vector3 vec3 );

    // Extract four AoS 3-D vectors
    // 
    inline void get4Aos( Aos::Vector3 & result0, Aos::Vector3 & result1, Aos::Vector3 & result2, Aos::Vector3 & result3 ) const;

    // Assign one 3-D vector to another
    // 
    inline Vector3 & operator =( const Vector3 & vec );

    // Set the x element of a 3-D vector
    // 
    inline Vector3 & setX( vec_float4 x );

    // Set the y element of a 3-D vector
    // 
    inline Vector3 & setY( vec_float4 y );

    // Set the z element of a 3-D vector
    // 
    inline Vector3 & setZ( vec_float4 z );

    // Get the x element of a 3-D vector
    // 
    inline vec_float4 getX( ) const;

    // Get the y element of a 3-D vector
    // 
    inline vec_float4 getY( ) const;

    // Get the z element of a 3-D vector
    // 
    inline vec_float4 getZ( ) const;

    // Set an x, y, or z element of a 3-D vector by index
    // 
    inline Vector3 & setElem( int idx, vec_float4 value );

    // Get an x, y, or z element of a 3-D vector by index
    // 
    inline vec_float4 getElem( int idx ) const;

    // Subscripting operator to set or get an element
    // 
    inline vec_float4_t & operator []( int idx );

    // Subscripting operator to get an element
    // 
    inline vec_float4 operator []( int idx ) const;

    // Add two 3-D vectors
    // 
    inline const Vector3 operator +( const Vector3 & vec ) const;

    // Subtract a 3-D vector from another 3-D vector
    // 
    inline const Vector3 operator -( const Vector3 & vec ) const;

    // Add a 3-D vector to a 3-D point
    // 
    inline const Point3 operator +( const Point3 & pnt ) const;

    // Multiply a 3-D vector by a scalar
    // 
    inline const Vector3 operator *( vec_float4 scalar ) const;

    // Divide a 3-D vector by a scalar
    // 
    inline const Vector3 operator /( vec_float4 scalar ) const;

    // Perform compound assignment and addition with a 3-D vector
    // 
    inline Vector3 & operator +=( const Vector3 & vec );

    // Perform compound assignment and subtraction by a 3-D vector
    // 
    inline Vector3 & operator -=( const Vector3 & vec );

    // Perform compound assignment and multiplication by a scalar
    // 
    inline Vector3 & operator *=( vec_float4 scalar );

    // Perform compound assignment and division by a scalar
    // 
    inline Vector3 & operator /=( vec_float4 scalar );

    // Negate all elements of a 3-D vector
    // 
    inline const Vector3 operator -( ) const;

    // Construct x axis
    // 
    static inline const Vector3 xAxis( );

    // Construct y axis
    // 
    static inline const Vector3 yAxis( );

    // Construct z axis
    // 
    static inline const Vector3 zAxis( );

};

// Multiply a 3-D vector by a scalar
// 
inline const Vector3 operator *( vec_float4 scalar, const Vector3 & vec );

// Multiply two 3-D vectors per element
// 
inline const Vector3 mulPerElem( const Vector3 & vec0, const Vector3 & vec1 );

// Divide two 3-D vectors per element
// NOTE: 
// Floating-point behavior matches standard library function divf4.
// 
inline const Vector3 divPerElem( const Vector3 & vec0, const Vector3 & vec1 );

// Compute the reciprocal of a 3-D vector per element
// NOTE: 
// Floating-point behavior matches standard library function recipf4.
// 
inline const Vector3 recipPerElem( const Vector3 & vec );

// Compute the square root of a 3-D vector per element
// NOTE: 
// Floating-point behavior matches standard library function sqrtf4.
// 
inline const Vector3 sqrtPerElem( const Vector3 & vec );

// Compute the reciprocal square root of a 3-D vector per element
// NOTE: 
// Floating-point behavior matches standard library function rsqrtf4.
// 
inline const Vector3 rsqrtPerElem( const Vector3 & vec );

// Compute the absolute value of a 3-D vector per element
// 
inline const Vector3 absPerElem( const Vector3 & vec );

// Copy sign from one 3-D vector to another, per element
// 
inline const Vector3 copySignPerElem( const Vector3 & vec0, const Vector3 & vec1 );

// Maximum of two 3-D vectors per element
// 
inline const Vector3 maxPerElem( const Vector3 & vec0, const Vector3 & vec1 );

// Minimum of two 3-D vectors per element
// 
inline const Vector3 minPerElem( const Vector3 & vec0, const Vector3 & vec1 );

// Maximum element of a 3-D vector
// 
inline vec_float4 maxElem( const Vector3 & vec );

// Minimum element of a 3-D vector
// 
inline vec_float4 minElem( const Vector3 & vec );

// Compute the sum of all elements of a 3-D vector
// 
inline vec_float4 sum( const Vector3 & vec );

// Compute the dot product of two 3-D vectors
// 
inline vec_float4 dot( const Vector3 & vec0, const Vector3 & vec1 );

// Compute the square of the length of a 3-D vector
// 
inline vec_float4 lengthSqr( const Vector3 & vec );

// Compute the length of a 3-D vector
// 
inline vec_float4 length( const Vector3 & vec );

// Normalize a 3-D vector
// NOTE: 
// The result is unpredictable when all elements of vec are at or near zero.
// 
inline const Vector3 normalize( const Vector3 & vec );

// Compute cross product of two 3-D vectors
// 
inline const Vector3 cross( const Vector3 & vec0, const Vector3 & vec1 );

// Outer product of two 3-D vectors
// 
inline const Matrix3 outer( const Vector3 & vec0, const Vector3 & vec1 );

// Pre-multiply a row vector by a 3x3 matrix
// 
inline const Vector3 rowMul( const Vector3 & vec, const Matrix3 & mat );

// Cross-product matrix of a 3-D vector
// 
inline const Matrix3 crossMatrix( const Vector3 & vec );

// Create cross-product matrix and multiply
// NOTE: 
// Faster than separately creating a cross-product matrix and multiplying.
// 
inline const Matrix3 crossMatrixMul( const Vector3 & vec, const Matrix3 & mat );

// Linear interpolation between two 3-D vectors
// NOTE: 
// Does not clamp t between 0 and 1.
// 
inline const Vector3 lerp( vec_float4 t, const Vector3 & vec0, const Vector3 & vec1 );

// Spherical linear interpolation between two 3-D vectors
// NOTE: 
// The result is unpredictable if the vectors point in opposite directions.
// Does not clamp t between 0 and 1.
// 
inline const Vector3 slerp( vec_float4 t, const Vector3 & unitVec0, const Vector3 & unitVec1 );

// Conditionally select between two 3-D vectors
// NOTE: 
// This function uses a conditional select instruction to avoid a branch.
// 
inline const Vector3 select( const Vector3 & vec0, const Vector3 & vec1, vec_uint4 select1 );

// Load four three-float 3-D vectors, stored in three quadwords
// 
inline void loadXYZArray( Vector3 & vec, const vec_float4 * threeQuads );

// Store four slots of an SoA 3-D vector in three quadwords
// 
inline void storeXYZArray( const Vector3 & vec, vec_float4 * threeQuads );

// Store eight slots of two SoA 3-D vectors as half-floats
// 
inline void storeHalfFloats( const Vector3 & vec0, const Vector3 & vec1, vec_ushort8 * threeQuads );

#ifdef _VECTORMATH_DEBUG

// Print a 3-D vector
// NOTE: 
// Function is only defined when _VECTORMATH_DEBUG is defined.
// 
inline void print( const Vector3 & vec );

// Print a 3-D vector and an associated string identifier
// NOTE: 
// Function is only defined when _VECTORMATH_DEBUG is defined.
// 
inline void print( const Vector3 & vec, const char * name );

#endif

// A set of four 4-D vectors in structure-of-arrays format
//
class Vector4
{
    typedef vec_float4 vec_float4_t;
    vec_float4 mX;
    vec_float4 mY;
    vec_float4 mZ;
    vec_float4 mW;

public:
    // Default constructor; does no initialization
    // 
    inline Vector4( ) { };

    // Copy a 4-D vector
    // 
    inline Vector4( const Vector4 & vec );

    // Construct a 4-D vector from x, y, z, and w elements
    // 
    inline Vector4( vec_float4 x, vec_float4 y, vec_float4 z, vec_float4 w );

    // Construct a 4-D vector from a 3-D vector and a scalar
    // 
    inline Vector4( const Vector3 & xyz, vec_float4 w );

    // Copy x, y, and z from a 3-D vector into a 4-D vector, and set w to 0
    // 
    explicit inline Vector4( const Vector3 & vec );

    // Copy x, y, and z from a 3-D point into a 4-D vector, and set w to 1
    // 
    explicit inline Vector4( const Point3 & pnt );

    // Copy elements from a quaternion into a 4-D vector
    // 
    explicit inline Vector4( const Quat & quat );

    // Set all elements of a 4-D vector to the same scalar value
    // 
    explicit inline Vector4( vec_float4 scalar );

    // Replicate an AoS 4-D vector
    // 
    inline Vector4( Aos::Vector4 vec );

    // Insert four AoS 4-D vectors
    // 
    inline Vector4( Aos::Vector4 vec0, Aos::Vector4 vec1, Aos::Vector4 vec2, Aos::Vector4 vec3 );

    // Extract four AoS 4-D vectors
    // 
    inline void get4Aos( Aos::Vector4 & result0, Aos::Vector4 & result1, Aos::Vector4 & result2, Aos::Vector4 & result3 ) const;

    // Assign one 4-D vector to another
    // 
    inline Vector4 & operator =( const Vector4 & vec );

    // Set the x, y, and z elements of a 4-D vector
    // NOTE: 
    // This function does not change the w element.
    // 
    inline Vector4 & setXYZ( const Vector3 & vec );

    // Get the x, y, and z elements of a 4-D vector
    // 
    inline const Vector3 getXYZ( ) const;

    // Set the x element of a 4-D vector
    // 
    inline Vector4 & setX( vec_float4 x );

    // Set the y element of a 4-D vector
    // 
    inline Vector4 & setY( vec_float4 y );

    // Set the z element of a 4-D vector
    // 
    inline Vector4 & setZ( vec_float4 z );

    // Set the w element of a 4-D vector
    // 
    inline Vector4 & setW( vec_float4 w );

    // Get the x element of a 4-D vector
    // 
    inline vec_float4 getX( ) const;

    // Get the y element of a 4-D vector
    // 
    inline vec_float4 getY( ) const;

    // Get the z element of a 4-D vector
    // 
    inline vec_float4 getZ( ) const;

    // Get the w element of a 4-D vector
    // 
    inline vec_float4 getW( ) const;

    // Set an x, y, z, or w element of a 4-D vector by index
    // 
    inline Vector4 & setElem( int idx, vec_float4 value );

    // Get an x, y, z, or w element of a 4-D vector by index
    // 
    inline vec_float4 getElem( int idx ) const;

    // Subscripting operator to set or get an element
    // 
    inline vec_float4_t & operator []( int idx );

    // Subscripting operator to get an element
    // 
    inline vec_float4 operator []( int idx ) const;

    // Add two 4-D vectors
    // 
    inline const Vector4 operator +( const Vector4 & vec ) const;

    // Subtract a 4-D vector from another 4-D vector
    // 
    inline const Vector4 operator -( const Vector4 & vec ) const;

    // Multiply a 4-D vector by a scalar
    // 
    inline const Vector4 operator *( vec_float4 scalar ) const;

    // Divide a 4-D vector by a scalar
    // 
    inline const Vector4 operator /( vec_float4 scalar ) const;

    // Perform compound assignment and addition with a 4-D vector
    // 
    inline Vector4 & operator +=( const Vector4 & vec );

    // Perform compound assignment and subtraction by a 4-D vector
    // 
    inline Vector4 & operator -=( const Vector4 & vec );

    // Perform compound assignment and multiplication by a scalar
    // 
    inline Vector4 & operator *=( vec_float4 scalar );

    // Perform compound assignment and division by a scalar
    // 
    inline Vector4 & operator /=( vec_float4 scalar );

    // Negate all elements of a 4-D vector
    // 
    inline const Vector4 operator -( ) const;

    // Construct x axis
    // 
    static inline const Vector4 xAxis( );

    // Construct y axis
    // 
    static inline const Vector4 yAxis( );

    // Construct z axis
    // 
    static inline const Vector4 zAxis( );

    // Construct w axis
    // 
    static inline const Vector4 wAxis( );

};

// Multiply a 4-D vector by a scalar
// 
inline const Vector4 operator *( vec_float4 scalar, const Vector4 & vec );

// Multiply two 4-D vectors per element
// 
inline const Vector4 mulPerElem( const Vector4 & vec0, const Vector4 & vec1 );

// Divide two 4-D vectors per element
// NOTE: 
// Floating-point behavior matches standard library function divf4.
// 
inline const Vector4 divPerElem( const Vector4 & vec0, const Vector4 & vec1 );

// Compute the reciprocal of a 4-D vector per element
// NOTE: 
// Floating-point behavior matches standard library function recipf4.
// 
inline const Vector4 recipPerElem( const Vector4 & vec );

// Compute the square root of a 4-D vector per element
// NOTE: 
// Floating-point behavior matches standard library function sqrtf4.
// 
inline const Vector4 sqrtPerElem( const Vector4 & vec );

// Compute the reciprocal square root of a 4-D vector per element
// NOTE: 
// Floating-point behavior matches standard library function rsqrtf4.
// 
inline const Vector4 rsqrtPerElem( const Vector4 & vec );

// Compute the absolute value of a 4-D vector per element
// 
inline const Vector4 absPerElem( const Vector4 & vec );

// Copy sign from one 4-D vector to another, per element
// 
inline const Vector4 copySignPerElem( const Vector4 & vec0, const Vector4 & vec1 );

// Maximum of two 4-D vectors per element
// 
inline const Vector4 maxPerElem( const Vector4 & vec0, const Vector4 & vec1 );

// Minimum of two 4-D vectors per element
// 
inline const Vector4 minPerElem( const Vector4 & vec0, const Vector4 & vec1 );

// Maximum element of a 4-D vector
// 
inline vec_float4 maxElem( const Vector4 & vec );

// Minimum element of a 4-D vector
// 
inline vec_float4 minElem( const Vector4 & vec );

// Compute the sum of all elements of a 4-D vector
// 
inline vec_float4 sum( const Vector4 & vec );

// Compute the dot product of two 4-D vectors
// 
inline vec_float4 dot( const Vector4 & vec0, const Vector4 & vec1 );

// Compute the square of the length of a 4-D vector
// 
inline vec_float4 lengthSqr( const Vector4 & vec );

// Compute the length of a 4-D vector
// 
inline vec_float4 length( const Vector4 & vec );

// Normalize a 4-D vector
// NOTE: 
// The result is unpredictable when all elements of vec are at or near zero.
// 
inline const Vector4 normalize( const Vector4 & vec );

// Outer product of two 4-D vectors
// 
inline const Matrix4 outer( const Vector4 & vec0, const Vector4 & vec1 );

// Linear interpolation between two 4-D vectors
// NOTE: 
// Does not clamp t between 0 and 1.
// 
inline const Vector4 lerp( vec_float4 t, const Vector4 & vec0, const Vector4 & vec1 );

// Spherical linear interpolation between two 4-D vectors
// NOTE: 
// The result is unpredictable if the vectors point in opposite directions.
// Does not clamp t between 0 and 1.
// 
inline const Vector4 slerp( vec_float4 t, const Vector4 & unitVec0, const Vector4 & unitVec1 );

// Conditionally select between two 4-D vectors
// NOTE: 
// This function uses a conditional select instruction to avoid a branch.
// 
inline const Vector4 select( const Vector4 & vec0, const Vector4 & vec1, vec_uint4 select1 );

// Store four slots of an SoA 4-D vector as half-floats
// 
inline void storeHalfFloats( const Vector4 & vec, vec_ushort8 * twoQuads );

#ifdef _VECTORMATH_DEBUG

// Print a 4-D vector
// NOTE: 
// Function is only defined when _VECTORMATH_DEBUG is defined.
// 
inline void print( const Vector4 & vec );

// Print a 4-D vector and an associated string identifier
// NOTE: 
// Function is only defined when _VECTORMATH_DEBUG is defined.
// 
inline void print( const Vector4 & vec, const char * name );

#endif

// A set of four 3-D points in structure-of-arrays format
//
class Point3
{
    typedef vec_float4 vec_float4_t;
    vec_float4 mX;
    vec_float4 mY;
    vec_float4 mZ;

public:
    // Default constructor; does no initialization
    // 
    inline Point3( ) { };

    // Copy a 3-D point
    // 
    inline Point3( const Point3 & pnt );

    // Construct a 3-D point from x, y, and z elements
    // 
    inline Point3( vec_float4 x, vec_float4 y, vec_float4 z );

    // Copy elements from a 3-D vector into a 3-D point
    // 
    explicit inline Point3( const Vector3 & vec );

    // Set all elements of a 3-D point to the same scalar value
    // 
    explicit inline Point3( vec_float4 scalar );

    // Replicate an AoS 3-D point
    // 
    inline Point3( Aos::Point3 pnt );

    // Insert four AoS 3-D points
    // 
    inline Point3( Aos::Point3 pnt0, Aos::Point3 pnt1, Aos::Point3 pnt2, Aos::Point3 pnt3 );

    // Extract four AoS 3-D points
    // 
    inline void get4Aos( Aos::Point3 & result0, Aos::Point3 & result1, Aos::Point3 & result2, Aos::Point3 & result3 ) const;

    // Assign one 3-D point to another
    // 
    inline Point3 & operator =( const Point3 & pnt );

    // Set the x element of a 3-D point
    // 
    inline Point3 & setX( vec_float4 x );

    // Set the y element of a 3-D point
    // 
    inline Point3 & setY( vec_float4 y );

    // Set the z element of a 3-D point
    // 
    inline Point3 & setZ( vec_float4 z );

    // Get the x element of a 3-D point
    // 
    inline vec_float4 getX( ) const;

    // Get the y element of a 3-D point
    // 
    inline vec_float4 getY( ) const;

    // Get the z element of a 3-D point
    // 
    inline vec_float4 getZ( ) const;

    // Set an x, y, or z element of a 3-D point by index
    // 
    inline Point3 & setElem( int idx, vec_float4 value );

    // Get an x, y, or z element of a 3-D point by index
    // 
    inline vec_float4 getElem( int idx ) const;

    // Subscripting operator to set or get an element
    // 
    inline vec_float4_t & operator []( int idx );

    // Subscripting operator to get an element
    // 
    inline vec_float4 operator []( int idx ) const;

    // Subtract a 3-D point from another 3-D point
    // 
    inline const Vector3 operator -( const Point3 & pnt ) const;

    // Add a 3-D point to a 3-D vector
    // 
    inline const Point3 operator +( const Vector3 & vec ) const;

    // Subtract a 3-D vector from a 3-D point
    // 
    inline const Point3 operator -( const Vector3 & vec ) const;

    // Perform compound assignment and addition with a 3-D vector
    // 
    inline Point3 & operator +=( const Vector3 & vec );

    // Perform compound assignment and subtraction by a 3-D vector
    // 
    inline Point3 & operator -=( const Vector3 & vec );

};

// Multiply two 3-D points per element
// 
inline const Point3 mulPerElem( const Point3 & pnt0, const Point3 & pnt1 );

// Divide two 3-D points per element
// NOTE: 
// Floating-point behavior matches standard library function divf4.
// 
inline const Point3 divPerElem( const Point3 & pnt0, const Point3 & pnt1 );

// Compute the reciprocal of a 3-D point per element
// NOTE: 
// Floating-point behavior matches standard library function recipf4.
// 
inline const Point3 recipPerElem( const Point3 & pnt );

// Compute the square root of a 3-D point per element
// NOTE: 
// Floating-point behavior matches standard library function sqrtf4.
// 
inline const Point3 sqrtPerElem( const Point3 & pnt );

// Compute the reciprocal square root of a 3-D point per element
// NOTE: 
// Floating-point behavior matches standard library function rsqrtf4.
// 
inline const Point3 rsqrtPerElem( const Point3 & pnt );

// Compute the absolute value of a 3-D point per element
// 
inline const Point3 absPerElem( const Point3 & pnt );

// Copy sign from one 3-D point to another, per element
// 
inline const Point3 copySignPerElem( const Point3 & pnt0, const Point3 & pnt1 );

// Maximum of two 3-D points per element
// 
inline const Point3 maxPerElem( const Point3 & pnt0, const Point3 & pnt1 );

// Minimum of two 3-D points per element
// 
inline const Point3 minPerElem( const Point3 & pnt0, const Point3 & pnt1 );

// Maximum element of a 3-D point
// 
inline vec_float4 maxElem( const Point3 & pnt );

// Minimum element of a 3-D point
// 
inline vec_float4 minElem( const Point3 & pnt );

// Compute the sum of all elements of a 3-D point
// 
inline vec_float4 sum( const Point3 & pnt );

// Apply uniform scale to a 3-D point
// 
inline const Point3 scale( const Point3 & pnt, vec_float4 scaleVal );

// Apply non-uniform scale to a 3-D point
// 
inline const Point3 scale( const Point3 & pnt, const Vector3 & scaleVec );

// Scalar projection of a 3-D point on a unit-length 3-D vector
// 
inline vec_float4 projection( const Point3 & pnt, const Vector3 & unitVec );

// Compute the square of the distance of a 3-D point from the coordinate-system origin
// 
inline vec_float4 distSqrFromOrigin( const Point3 & pnt );

// Compute the distance of a 3-D point from the coordinate-system origin
// 
inline vec_float4 distFromOrigin( const Point3 & pnt );

// Compute the square of the distance between two 3-D points
// 
inline vec_float4 distSqr( const Point3 & pnt0, const Point3 & pnt1 );

// Compute the distance between two 3-D points
// 
inline vec_float4 dist( const Point3 & pnt0, const Point3 & pnt1 );

// Linear interpolation between two 3-D points
// NOTE: 
// Does not clamp t between 0 and 1.
// 
inline const Point3 lerp( vec_float4 t, const Point3 & pnt0, const Point3 & pnt1 );

// Conditionally select between two 3-D points
// NOTE: 
// This function uses a conditional select instruction to avoid a branch.
// 
inline const Point3 select( const Point3 & pnt0, const Point3 & pnt1, vec_uint4 select1 );

// Load four three-float 3-D points, stored in three quadwords
// 
inline void loadXYZArray( Point3 & pnt, const vec_float4 * threeQuads );

// Store four slots of an SoA 3-D point in three quadwords
// 
inline void storeXYZArray( const Point3 & pnt, vec_float4 * threeQuads );

// Store eight slots of two SoA 3-D points as half-floats
// 
inline void storeHalfFloats( const Point3 & pnt0, const Point3 & pnt1, vec_ushort8 * threeQuads );

#ifdef _VECTORMATH_DEBUG

// Print a 3-D point
// NOTE: 
// Function is only defined when _VECTORMATH_DEBUG is defined.
// 
inline void print( const Point3 & pnt );

// Print a 3-D point and an associated string identifier
// NOTE: 
// Function is only defined when _VECTORMATH_DEBUG is defined.
// 
inline void print( const Point3 & pnt, const char * name );

#endif

// A set of four quaternions in structure-of-arrays format
//
class Quat
{
    typedef vec_float4 vec_float4_t;
    vec_float4 mX;
    vec_float4 mY;
    vec_float4 mZ;
    vec_float4 mW;

public:
    // Default constructor; does no initialization
    // 
    inline Quat( ) { };

    // Copy a quaternion
    // 
    inline Quat( const Quat & quat );

    // Construct a quaternion from x, y, z, and w elements
    // 
    inline Quat( vec_float4 x, vec_float4 y, vec_float4 z, vec_float4 w );

    // Construct a quaternion from a 3-D vector and a scalar
    // 
    inline Quat( const Vector3 & xyz, vec_float4 w );

    // Copy elements from a 4-D vector into a quaternion
    // 
    explicit inline Quat( const Vector4 & vec );

    // Convert a rotation matrix to a unit-length quaternion
    // 
    explicit inline Quat( const Matrix3 & rotMat );

    // Set all elements of a quaternion to the same scalar value
    // 
    explicit inline Quat( vec_float4 scalar );

    // Replicate an AoS quaternion
    // 
    inline Quat( Aos::Quat quat );

    // Insert four AoS quaternions
    // 
    inline Quat( Aos::Quat quat0, Aos::Quat quat1, Aos::Quat quat2, Aos::Quat quat3 );

    // Extract four AoS quaternions
    // 
    inline void get4Aos( Aos::Quat & result0, Aos::Quat & result1, Aos::Quat & result2, Aos::Quat & result3 ) const;

    // Assign one quaternion to another
    // 
    inline Quat & operator =( const Quat & quat );

    // Set the x, y, and z elements of a quaternion
    // NOTE: 
    // This function does not change the w element.
    // 
    inline Quat & setXYZ( const Vector3 & vec );

    // Get the x, y, and z elements of a quaternion
    // 
    inline const Vector3 getXYZ( ) const;

    // Set the x element of a quaternion
    // 
    inline Quat & setX( vec_float4 x );

    // Set the y element of a quaternion
    // 
    inline Quat & setY( vec_float4 y );

    // Set the z element of a quaternion
    // 
    inline Quat & setZ( vec_float4 z );

    // Set the w element of a quaternion
    // 
    inline Quat & setW( vec_float4 w );

    // Get the x element of a quaternion
    // 
    inline vec_float4 getX( ) const;

    // Get the y element of a quaternion
    // 
    inline vec_float4 getY( ) const;

    // Get the z element of a quaternion
    // 
    inline vec_float4 getZ( ) const;

    // Get the w element of a quaternion
    // 
    inline vec_float4 getW( ) const;

    // Set an x, y, z, or w element of a quaternion by index
    // 
    inline Quat & setElem( int idx, vec_float4 value );

    // Get an x, y, z, or w element of a quaternion by index
    // 
    inline vec_float4 getElem( int idx ) const;

    // Subscripting operator to set or get an element
    // 
    inline vec_float4_t & operator []( int idx );

    // Subscripting operator to get an element
    // 
    inline vec_float4 operator []( int idx ) const;

    // Add two quaternions
    // 
    inline const Quat operator +( const Quat & quat ) const;

    // Subtract a quaternion from another quaternion
    // 
    inline const Quat operator -( const Quat & quat ) const;

    // Multiply two quaternions
    // 
    inline const Quat operator *( const Quat & quat ) const;

    // Multiply a quaternion by a scalar
    // 
    inline const Quat operator *( vec_float4 scalar ) const;

    // Divide a quaternion by a scalar
    // 
    inline const Quat operator /( vec_float4 scalar ) const;

    // Perform compound assignment and addition with a quaternion
    // 
    inline Quat & operator +=( const Quat & quat );

    // Perform compound assignment and subtraction by a quaternion
    // 
    inline Quat & operator -=( const Quat & quat );

    // Perform compound assignment and multiplication by a quaternion
    // 
    inline Quat & operator *=( const Quat & quat );

    // Perform compound assignment and multiplication by a scalar
    // 
    inline Quat & operator *=( vec_float4 scalar );

    // Perform compound assignment and division by a scalar
    // 
    inline Quat & operator /=( vec_float4 scalar );

    // Negate all elements of a quaternion
    // 
    inline const Quat operator -( ) const;

    // Construct an identity quaternion
    // 
    static inline const Quat identity( );

    // Construct a quaternion to rotate between two unit-length 3-D vectors
    // NOTE: 
    // The result is unpredictable if unitVec0 and unitVec1 point in opposite directions.
    // 
    static inline const Quat rotation( const Vector3 & unitVec0, const Vector3 & unitVec1 );

    // Construct a quaternion to rotate around a unit-length 3-D vector
    // 
    static inline const Quat rotation( vec_float4 radians, const Vector3 & unitVec );

    // Construct a quaternion to rotate around the x axis
    // 
    static inline const Quat rotationX( vec_float4 radians );

    // Construct a quaternion to rotate around the y axis
    // 
    static inline const Quat rotationY( vec_float4 radians );

    // Construct a quaternion to rotate around the z axis
    // 
    static inline const Quat rotationZ( vec_float4 radians );

};

// Multiply a quaternion by a scalar
// 
inline const Quat operator *( vec_float4 scalar, const Quat & quat );

// Compute the conjugate of a quaternion
// 
inline const Quat conj( const Quat & quat );

// Use a unit-length quaternion to rotate a 3-D vector
// 
inline const Vector3 rotate( const Quat & unitQuat, const Vector3 & vec );

// Compute the dot product of two quaternions
// 
inline vec_float4 dot( const Quat & quat0, const Quat & quat1 );

// Compute the norm of a quaternion
// 
inline vec_float4 norm( const Quat & quat );

// Compute the length of a quaternion
// 
inline vec_float4 length( const Quat & quat );

// Normalize a quaternion
// NOTE: 
// The result is unpredictable when all elements of quat are at or near zero.
// 
inline const Quat normalize( const Quat & quat );

// Linear interpolation between two quaternions
// NOTE: 
// Does not clamp t between 0 and 1.
// 
inline const Quat lerp( vec_float4 t, const Quat & quat0, const Quat & quat1 );

// Spherical linear interpolation between two quaternions
// NOTE: 
// Interpolates along the shortest path between orientations.
// Does not clamp t between 0 and 1.
// 
inline const Quat slerp( vec_float4 t, const Quat & unitQuat0, const Quat & unitQuat1 );

// Spherical quadrangle interpolation
// 
inline const Quat squad( vec_float4 t, const Quat & unitQuat0, const Quat & unitQuat1, const Quat & unitQuat2, const Quat & unitQuat3 );

// Conditionally select between two quaternions
// NOTE: 
// This function uses a conditional select instruction to avoid a branch.
// 
inline const Quat select( const Quat & quat0, const Quat & quat1, vec_uint4 select1 );

#ifdef _VECTORMATH_DEBUG

// Print a quaternion
// NOTE: 
// Function is only defined when _VECTORMATH_DEBUG is defined.
// 
inline void print( const Quat & quat );

// Print a quaternion and an associated string identifier
// NOTE: 
// Function is only defined when _VECTORMATH_DEBUG is defined.
// 
inline void print( const Quat & quat, const char * name );

#endif

// A set of four 3x3 matrices in structure-of-arrays format
//
class Matrix3
{
    Vector3 mCol0;
    Vector3 mCol1;
    Vector3 mCol2;

public:
    // Default constructor; does no initialization
    // 
    inline Matrix3( ) { };

    // Copy a 3x3 matrix
    // 
    inline Matrix3( const Matrix3 & mat );

    // Construct a 3x3 matrix containing the specified columns
    // 
    inline Matrix3( const Vector3 & col0, const Vector3 & col1, const Vector3 & col2 );

    // Construct a 3x3 rotation matrix from a unit-length quaternion
    // 
    explicit inline Matrix3( const Quat & unitQuat );

    // Set all elements of a 3x3 matrix to the same scalar value
    // 
    explicit inline Matrix3( vec_float4 scalar );

    // Replicate an AoS 3x3 matrix
    // 
    inline Matrix3( const Aos::Matrix3 & mat );

    // Insert four AoS 3x3 matrices
    // 
    inline Matrix3( const Aos::Matrix3 & mat0, const Aos::Matrix3 & mat1, const Aos::Matrix3 & mat2, const Aos::Matrix3 & mat3 );

    // Extract four AoS 3x3 matrices
    // 
    inline void get4Aos( Aos::Matrix3 & result0, Aos::Matrix3 & result1, Aos::Matrix3 & result2, Aos::Matrix3 & result3 ) const;

    // Assign one 3x3 matrix to another
    // 
    inline Matrix3 & operator =( const Matrix3 & mat );

    // Set column 0 of a 3x3 matrix
    // 
    inline Matrix3 & setCol0( const Vector3 & col0 );

    // Set column 1 of a 3x3 matrix
    // 
    inline Matrix3 & setCol1( const Vector3 & col1 );

    // Set column 2 of a 3x3 matrix
    // 
    inline Matrix3 & setCol2( const Vector3 & col2 );

    // Get column 0 of a 3x3 matrix
    // 
    inline const Vector3 getCol0( ) const;

    // Get column 1 of a 3x3 matrix
    // 
    inline const Vector3 getCol1( ) const;

    // Get column 2 of a 3x3 matrix
    // 
    inline const Vector3 getCol2( ) const;

    // Set the column of a 3x3 matrix referred to by the specified index
    // 
    inline Matrix3 & setCol( int col, const Vector3 & vec );

    // Set the row of a 3x3 matrix referred to by the specified index
    // 
    inline Matrix3 & setRow( int row, const Vector3 & vec );

    // Get the column of a 3x3 matrix referred to by the specified index
    // 
    inline const Vector3 getCol( int col ) const;

    // Get the row of a 3x3 matrix referred to by the specified index
    // 
    inline const Vector3 getRow( int row ) const;

    // Subscripting operator to set or get a column
    // 
    inline Vector3 & operator []( int col );

    // Subscripting operator to get a column
    // 
    inline const Vector3 operator []( int col ) const;

    // Set the element of a 3x3 matrix referred to by column and row indices
    // 
    inline Matrix3 & setElem( int col, int row, vec_float4 val );

    // Get the element of a 3x3 matrix referred to by column and row indices
    // 
    inline vec_float4 getElem( int col, int row ) const;

    // Add two 3x3 matrices
    // 
    inline const Matrix3 operator +( const Matrix3 & mat ) const;

    // Subtract a 3x3 matrix from another 3x3 matrix
    // 
    inline const Matrix3 operator -( const Matrix3 & mat ) const;

    // Negate all elements of a 3x3 matrix
    // 
    inline const Matrix3 operator -( ) const;

    // Multiply a 3x3 matrix by a scalar
    // 
    inline const Matrix3 operator *( vec_float4 scalar ) const;

    // Multiply a 3x3 matrix by a 3-D vector
    // 
    inline const Vector3 operator *( const Vector3 & vec ) const;

    // Multiply two 3x3 matrices
    // 
    inline const Matrix3 operator *( const Matrix3 & mat ) const;

    // Perform compound assignment and addition with a 3x3 matrix
    // 
    inline Matrix3 & operator +=( const Matrix3 & mat );

    // Perform compound assignment and subtraction by a 3x3 matrix
    // 
    inline Matrix3 & operator -=( const Matrix3 & mat );

    // Perform compound assignment and multiplication by a scalar
    // 
    inline Matrix3 & operator *=( vec_float4 scalar );

    // Perform compound assignment and multiplication by a 3x3 matrix
    // 
    inline Matrix3 & operator *=( const Matrix3 & mat );

    // Construct an identity 3x3 matrix
    // 
    static inline const Matrix3 identity( );

    // Construct a 3x3 matrix to rotate around the x axis
    // 
    static inline const Matrix3 rotationX( vec_float4 radians );

    // Construct a 3x3 matrix to rotate around the y axis
    // 
    static inline const Matrix3 rotationY( vec_float4 radians );

    // Construct a 3x3 matrix to rotate around the z axis
    // 
    static inline const Matrix3 rotationZ( vec_float4 radians );

    // Construct a 3x3 matrix to rotate around the x, y, and z axes
    // 
    static inline const Matrix3 rotationZYX( const Vector3 & radiansXYZ );

    // Construct a 3x3 matrix to rotate around a unit-length 3-D vector
    // 
    static inline const Matrix3 rotation( vec_float4 radians, const Vector3 & unitVec );

    // Construct a rotation matrix from a unit-length quaternion
    // 
    static inline const Matrix3 rotation( const Quat & unitQuat );

    // Construct a 3x3 matrix to perform scaling
    // 
    static inline const Matrix3 scale( const Vector3 & scaleVec );

};
// Multiply a 3x3 matrix by a scalar
// 
inline const Matrix3 operator *( vec_float4 scalar, const Matrix3 & mat );

// Append (post-multiply) a scale transformation to a 3x3 matrix
// NOTE: 
// Faster than creating and multiplying a scale transformation matrix.
// 
inline const Matrix3 appendScale( const Matrix3 & mat, const Vector3 & scaleVec );

// Prepend (pre-multiply) a scale transformation to a 3x3 matrix
// NOTE: 
// Faster than creating and multiplying a scale transformation matrix.
// 
inline const Matrix3 prependScale( const Vector3 & scaleVec, const Matrix3 & mat );

// Multiply two 3x3 matrices per element
// 
inline const Matrix3 mulPerElem( const Matrix3 & mat0, const Matrix3 & mat1 );

// Compute the absolute value of a 3x3 matrix per element
// 
inline const Matrix3 absPerElem( const Matrix3 & mat );

// Transpose of a 3x3 matrix
// 
inline const Matrix3 transpose( const Matrix3 & mat );

// Compute the inverse of a 3x3 matrix
// NOTE: 
// Result is unpredictable when the determinant of mat is equal to or near 0.
// 
inline const Matrix3 inverse( const Matrix3 & mat );

// Determinant of a 3x3 matrix
// 
inline vec_float4 determinant( const Matrix3 & mat );

// Conditionally select between two 3x3 matrices
// NOTE: 
// This function uses a conditional select instruction to avoid a branch.
// 
inline const Matrix3 select( const Matrix3 & mat0, const Matrix3 & mat1, vec_uint4 select1 );

#ifdef _VECTORMATH_DEBUG

// Print a 3x3 matrix
// NOTE: 
// Function is only defined when _VECTORMATH_DEBUG is defined.
// 
inline void print( const Matrix3 & mat );

// Print a 3x3 matrix and an associated string identifier
// NOTE: 
// Function is only defined when _VECTORMATH_DEBUG is defined.
// 
inline void print( const Matrix3 & mat, const char * name );

#endif

// A set of four 4x4 matrices in structure-of-arrays format
//
class Matrix4
{
    Vector4 mCol0;
    Vector4 mCol1;
    Vector4 mCol2;
    Vector4 mCol3;

public:
    // Default constructor; does no initialization
    // 
    inline Matrix4( ) { };

    // Copy a 4x4 matrix
    // 
    inline Matrix4( const Matrix4 & mat );

    // Construct a 4x4 matrix containing the specified columns
    // 
    inline Matrix4( const Vector4 & col0, const Vector4 & col1, const Vector4 & col2, const Vector4 & col3 );

    // Construct a 4x4 matrix from a 3x4 transformation matrix
    // 
    explicit inline Matrix4( const Transform3 & mat );

    // Construct a 4x4 matrix from a 3x3 matrix and a 3-D vector
    // 
    inline Matrix4( const Matrix3 & mat, const Vector3 & translateVec );

    // Construct a 4x4 matrix from a unit-length quaternion and a 3-D vector
    // 
    inline Matrix4( const Quat & unitQuat, const Vector3 & translateVec );

    // Set all elements of a 4x4 matrix to the same scalar value
    // 
    explicit inline Matrix4( vec_float4 scalar );

    // Replicate an AoS 4x4 matrix
    // 
    inline Matrix4( const Aos::Matrix4 & mat );

    // Insert four AoS 4x4 matrices
    // 
    inline Matrix4( const Aos::Matrix4 & mat0, const Aos::Matrix4 & mat1, const Aos::Matrix4 & mat2, const Aos::Matrix4 & mat3 );

    // Extract four AoS 4x4 matrices
    // 
    inline void get4Aos( Aos::Matrix4 & result0, Aos::Matrix4 & result1, Aos::Matrix4 & result2, Aos::Matrix4 & result3 ) const;

    // Assign one 4x4 matrix to another
    // 
    inline Matrix4 & operator =( const Matrix4 & mat );

    // Set the upper-left 3x3 submatrix
    // NOTE: 
    // This function does not change the bottom row elements.
    // 
    inline Matrix4 & setUpper3x3( const Matrix3 & mat3 );

    // Get the upper-left 3x3 submatrix of a 4x4 matrix
    // 
    inline const Matrix3 getUpper3x3( ) const;

    // Set translation component
    // NOTE: 
    // This function does not change the bottom row elements.
    // 
    inline Matrix4 & setTranslation( const Vector3 & translateVec );

    // Get the translation component of a 4x4 matrix
    // 
    inline const Vector3 getTranslation( ) const;

    // Set column 0 of a 4x4 matrix
    // 
    inline Matrix4 & setCol0( const Vector4 & col0 );

    // Set column 1 of a 4x4 matrix
    // 
    inline Matrix4 & setCol1( const Vector4 & col1 );

    // Set column 2 of a 4x4 matrix
    // 
    inline Matrix4 & setCol2( const Vector4 & col2 );

    // Set column 3 of a 4x4 matrix
    // 
    inline Matrix4 & setCol3( const Vector4 & col3 );

    // Get column 0 of a 4x4 matrix
    // 
    inline const Vector4 getCol0( ) const;

    // Get column 1 of a 4x4 matrix
    // 
    inline const Vector4 getCol1( ) const;

    // Get column 2 of a 4x4 matrix
    // 
    inline const Vector4 getCol2( ) const;

    // Get column 3 of a 4x4 matrix
    // 
    inline const Vector4 getCol3( ) const;

    // Set the column of a 4x4 matrix referred to by the specified index
    // 
    inline Matrix4 & setCol( int col, const Vector4 & vec );

    // Set the row of a 4x4 matrix referred to by the specified index
    // 
    inline Matrix4 & setRow( int row, const Vector4 & vec );

    // Get the column of a 4x4 matrix referred to by the specified index
    // 
    inline const Vector4 getCol( int col ) const;

    // Get the row of a 4x4 matrix referred to by the specified index
    // 
    inline const Vector4 getRow( int row ) const;

    // Subscripting operator to set or get a column
    // 
    inline Vector4 & operator []( int col );

    // Subscripting operator to get a column
    // 
    inline const Vector4 operator []( int col ) const;

    // Set the element of a 4x4 matrix referred to by column and row indices
    // 
    inline Matrix4 & setElem( int col, int row, vec_float4 val );

    // Get the element of a 4x4 matrix referred to by column and row indices
    // 
    inline vec_float4 getElem( int col, int row ) const;

    // Add two 4x4 matrices
    // 
    inline const Matrix4 operator +( const Matrix4 & mat ) const;

    // Subtract a 4x4 matrix from another 4x4 matrix
    // 
    inline const Matrix4 operator -( const Matrix4 & mat ) const;

    // Negate all elements of a 4x4 matrix
    // 
    inline const Matrix4 operator -( ) const;

    // Multiply a 4x4 matrix by a scalar
    // 
    inline const Matrix4 operator *( vec_float4 scalar ) const;

    // Multiply a 4x4 matrix by a 4-D vector
    // 
    inline const Vector4 operator *( const Vector4 & vec ) const;

    // Multiply a 4x4 matrix by a 3-D vector
    // 
    inline const Vector4 operator *( const Vector3 & vec ) const;

    // Multiply a 4x4 matrix by a 3-D point
    // 
    inline const Vector4 operator *( const Point3 & pnt ) const;

    // Multiply two 4x4 matrices
    // 
    inline const Matrix4 operator *( const Matrix4 & mat ) const;

    // Multiply a 4x4 matrix by a 3x4 transformation matrix
    // 
    inline const Matrix4 operator *( const Transform3 & tfrm ) const;

    // Perform compound assignment and addition with a 4x4 matrix
    // 
    inline Matrix4 & operator +=( const Matrix4 & mat );

    // Perform compound assignment and subtraction by a 4x4 matrix
    // 
    inline Matrix4 & operator -=( const Matrix4 & mat );

    // Perform compound assignment and multiplication by a scalar
    // 
    inline Matrix4 & operator *=( vec_float4 scalar );

    // Perform compound assignment and multiplication by a 4x4 matrix
    // 
    inline Matrix4 & operator *=( const Matrix4 & mat );

    // Perform compound assignment and multiplication by a 3x4 transformation matrix
    // 
    inline Matrix4 & operator *=( const Transform3 & tfrm );

    // Construct an identity 4x4 matrix
    // 
    static inline const Matrix4 identity( );

    // Construct a 4x4 matrix to rotate around the x axis
    // 
    static inline const Matrix4 rotationX( vec_float4 radians );

    // Construct a 4x4 matrix to rotate around the y axis
    // 
    static inline const Matrix4 rotationY( vec_float4 radians );

    // Construct a 4x4 matrix to rotate around the z axis
    // 
    static inline const Matrix4 rotationZ( vec_float4 radians );

    // Construct a 4x4 matrix to rotate around the x, y, and z axes
    // 
    static inline const Matrix4 rotationZYX( const Vector3 & radiansXYZ );

    // Construct a 4x4 matrix to rotate around a unit-length 3-D vector
    // 
    static inline const Matrix4 rotation( vec_float4 radians, const Vector3 & unitVec );

    // Construct a rotation matrix from a unit-length quaternion
    // 
    static inline const Matrix4 rotation( const Quat & unitQuat );

    // Construct a 4x4 matrix to perform scaling
    // 
    static inline const Matrix4 scale( const Vector3 & scaleVec );

    // Construct a 4x4 matrix to perform translation
    // 
    static inline const Matrix4 translation( const Vector3 & translateVec );

    // Construct viewing matrix based on eye position, position looked at, and up direction
    // 
    static inline const Matrix4 lookAt( const Point3 & eyePos, const Point3 & lookAtPos, const Vector3 & upVec );

    // Construct a perspective projection matrix
    // 
    static inline const Matrix4 perspective( vec_float4 fovyRadians, vec_float4 aspect, vec_float4 zNear, vec_float4 zFar );

    // Construct a perspective projection matrix based on frustum
    // 
    static inline const Matrix4 frustum( vec_float4 left, vec_float4 right, vec_float4 bottom, vec_float4 top, vec_float4 zNear, vec_float4 zFar );

    // Construct an orthographic projection matrix
    // 
    static inline const Matrix4 orthographic( vec_float4 left, vec_float4 right, vec_float4 bottom, vec_float4 top, vec_float4 zNear, vec_float4 zFar );

};
// Multiply a 4x4 matrix by a scalar
// 
inline const Matrix4 operator *( vec_float4 scalar, const Matrix4 & mat );

// Append (post-multiply) a scale transformation to a 4x4 matrix
// NOTE: 
// Faster than creating and multiplying a scale transformation matrix.
// 
inline const Matrix4 appendScale( const Matrix4 & mat, const Vector3 & scaleVec );

// Prepend (pre-multiply) a scale transformation to a 4x4 matrix
// NOTE: 
// Faster than creating and multiplying a scale transformation matrix.
// 
inline const Matrix4 prependScale( const Vector3 & scaleVec, const Matrix4 & mat );

// Multiply two 4x4 matrices per element
// 
inline const Matrix4 mulPerElem( const Matrix4 & mat0, const Matrix4 & mat1 );

// Compute the absolute value of a 4x4 matrix per element
// 
inline const Matrix4 absPerElem( const Matrix4 & mat );

// Transpose of a 4x4 matrix
// 
inline const Matrix4 transpose( const Matrix4 & mat );

// Compute the inverse of a 4x4 matrix
// NOTE: 
// Result is unpredictable when the determinant of mat is equal to or near 0.
// 
inline const Matrix4 inverse( const Matrix4 & mat );

// Compute the inverse of a 4x4 matrix, which is expected to be an affine matrix
// NOTE: 
// This can be used to achieve better performance than a general inverse when the specified 4x4 matrix meets the given restrictions.  The result is unpredictable when the determinant of mat is equal to or near 0.
// 
inline const Matrix4 affineInverse( const Matrix4 & mat );

// Compute the inverse of a 4x4 matrix, which is expected to be an affine matrix with an orthogonal upper-left 3x3 submatrix
// NOTE: 
// This can be used to achieve better performance than a general inverse when the specified 4x4 matrix meets the given restrictions.
// 
inline const Matrix4 orthoInverse( const Matrix4 & mat );

// Determinant of a 4x4 matrix
// 
inline vec_float4 determinant( const Matrix4 & mat );

// Conditionally select between two 4x4 matrices
// NOTE: 
// This function uses a conditional select instruction to avoid a branch.
// 
inline const Matrix4 select( const Matrix4 & mat0, const Matrix4 & mat1, vec_uint4 select1 );

#ifdef _VECTORMATH_DEBUG

// Print a 4x4 matrix
// NOTE: 
// Function is only defined when _VECTORMATH_DEBUG is defined.
// 
inline void print( const Matrix4 & mat );

// Print a 4x4 matrix and an associated string identifier
// NOTE: 
// Function is only defined when _VECTORMATH_DEBUG is defined.
// 
inline void print( const Matrix4 & mat, const char * name );

#endif

// A set of four 3x4 transformation matrices in structure-of-arrays format
//
class Transform3
{
    Vector3 mCol0;
    Vector3 mCol1;
    Vector3 mCol2;
    Vector3 mCol3;

public:
    // Default constructor; does no initialization
    // 
    inline Transform3( ) { };

    // Copy a 3x4 transformation matrix
    // 
    inline Transform3( const Transform3 & tfrm );

    // Construct a 3x4 transformation matrix containing the specified columns
    // 
    inline Transform3( const Vector3 & col0, const Vector3 & col1, const Vector3 & col2, const Vector3 & col3 );

    // Construct a 3x4 transformation matrix from a 3x3 matrix and a 3-D vector
    // 
    inline Transform3( const Matrix3 & tfrm, const Vector3 & translateVec );

    // Construct a 3x4 transformation matrix from a unit-length quaternion and a 3-D vector
    // 
    inline Transform3( const Quat & unitQuat, const Vector3 & translateVec );

    // Set all elements of a 3x4 transformation matrix to the same scalar value
    // 
    explicit inline Transform3( vec_float4 scalar );

    // Replicate an AoS 3x4 transformation matrix
    // 
    inline Transform3( const Aos::Transform3 & tfrm );

    // Insert four AoS 3x4 transformation matrices
    // 
    inline Transform3( const Aos::Transform3 & tfrm0, const Aos::Transform3 & tfrm1, const Aos::Transform3 & tfrm2, const Aos::Transform3 & tfrm3 );

    // Extract four AoS 3x4 transformation matrices
    // 
    inline void get4Aos( Aos::Transform3 & result0, Aos::Transform3 & result1, Aos::Transform3 & result2, Aos::Transform3 & result3 ) const;

    // Assign one 3x4 transformation matrix to another
    // 
    inline Transform3 & operator =( const Transform3 & tfrm );

    // Set the upper-left 3x3 submatrix
    // 
    inline Transform3 & setUpper3x3( const Matrix3 & mat3 );

    // Get the upper-left 3x3 submatrix of a 3x4 transformation matrix
    // 
    inline const Matrix3 getUpper3x3( ) const;

    // Set translation component
    // 
    inline Transform3 & setTranslation( const Vector3 & translateVec );

    // Get the translation component of a 3x4 transformation matrix
    // 
    inline const Vector3 getTranslation( ) const;

    // Set column 0 of a 3x4 transformation matrix
    // 
    inline Transform3 & setCol0( const Vector3 & col0 );

    // Set column 1 of a 3x4 transformation matrix
    // 
    inline Transform3 & setCol1( const Vector3 & col1 );

    // Set column 2 of a 3x4 transformation matrix
    // 
    inline Transform3 & setCol2( const Vector3 & col2 );

    // Set column 3 of a 3x4 transformation matrix
    // 
    inline Transform3 & setCol3( const Vector3 & col3 );

    // Get column 0 of a 3x4 transformation matrix
    // 
    inline const Vector3 getCol0( ) const;

    // Get column 1 of a 3x4 transformation matrix
    // 
    inline const Vector3 getCol1( ) const;

    // Get column 2 of a 3x4 transformation matrix
    // 
    inline const Vector3 getCol2( ) const;

    // Get column 3 of a 3x4 transformation matrix
    // 
    inline const Vector3 getCol3( ) const;

    // Set the column of a 3x4 transformation matrix referred to by the specified index
    // 
    inline Transform3 & setCol( int col, const Vector3 & vec );

    // Set the row of a 3x4 transformation matrix referred to by the specified index
    // 
    inline Transform3 & setRow( int row, const Vector4 & vec );

    // Get the column of a 3x4 transformation matrix referred to by the specified index
    // 
    inline const Vector3 getCol( int col ) const;

    // Get the row of a 3x4 transformation matrix referred to by the specified index
    // 
    inline const Vector4 getRow( int row ) const;

    // Subscripting operator to set or get a column
    // 
    inline Vector3 & operator []( int col );

    // Subscripting operator to get a column
    // 
    inline const Vector3 operator []( int col ) const;

    // Set the element of a 3x4 transformation matrix referred to by column and row indices
    // 
    inline Transform3 & setElem( int col, int row, vec_float4 val );

    // Get the element of a 3x4 transformation matrix referred to by column and row indices
    // 
    inline vec_float4 getElem( int col, int row ) const;

    // Multiply a 3x4 transformation matrix by a 3-D vector
    // 
    inline const Vector3 operator *( const Vector3 & vec ) const;

    // Multiply a 3x4 transformation matrix by a 3-D point
    // 
    inline const Point3 operator *( const Point3 & pnt ) const;

    // Multiply two 3x4 transformation matrices
    // 
    inline const Transform3 operator *( const Transform3 & tfrm ) const;

    // Perform compound assignment and multiplication by a 3x4 transformation matrix
    // 
    inline Transform3 & operator *=( const Transform3 & tfrm );

    // Construct an identity 3x4 transformation matrix
    // 
    static inline const Transform3 identity( );

    // Construct a 3x4 transformation matrix to rotate around the x axis
    // 
    static inline const Transform3 rotationX( vec_float4 radians );

    // Construct a 3x4 transformation matrix to rotate around the y axis
    // 
    static inline const Transform3 rotationY( vec_float4 radians );

    // Construct a 3x4 transformation matrix to rotate around the z axis
    // 
    static inline const Transform3 rotationZ( vec_float4 radians );

    // Construct a 3x4 transformation matrix to rotate around the x, y, and z axes
    // 
    static inline const Transform3 rotationZYX( const Vector3 & radiansXYZ );

    // Construct a 3x4 transformation matrix to rotate around a unit-length 3-D vector
    // 
    static inline const Transform3 rotation( vec_float4 radians, const Vector3 & unitVec );

    // Construct a rotation matrix from a unit-length quaternion
    // 
    static inline const Transform3 rotation( const Quat & unitQuat );

    // Construct a 3x4 transformation matrix to perform scaling
    // 
    static inline const Transform3 scale( const Vector3 & scaleVec );

    // Construct a 3x4 transformation matrix to perform translation
    // 
    static inline const Transform3 translation( const Vector3 & translateVec );

};
// Append (post-multiply) a scale transformation to a 3x4 transformation matrix
// NOTE: 
// Faster than creating and multiplying a scale transformation matrix.
// 
inline const Transform3 appendScale( const Transform3 & tfrm, const Vector3 & scaleVec );

// Prepend (pre-multiply) a scale transformation to a 3x4 transformation matrix
// NOTE: 
// Faster than creating and multiplying a scale transformation matrix.
// 
inline const Transform3 prependScale( const Vector3 & scaleVec, const Transform3 & tfrm );

// Multiply two 3x4 transformation matrices per element
// 
inline const Transform3 mulPerElem( const Transform3 & tfrm0, const Transform3 & tfrm1 );

// Compute the absolute value of a 3x4 transformation matrix per element
// 
inline const Transform3 absPerElem( const Transform3 & tfrm );

// Inverse of a 3x4 transformation matrix
// NOTE: 
// Result is unpredictable when the determinant of the left 3x3 submatrix is equal to or near 0.
// 
inline const Transform3 inverse( const Transform3 & tfrm );

// Compute the inverse of a 3x4 transformation matrix, expected to have an orthogonal upper-left 3x3 submatrix
// NOTE: 
// This can be used to achieve better performance than a general inverse when the specified 3x4 transformation matrix meets the given restrictions.
// 
inline const Transform3 orthoInverse( const Transform3 & tfrm );

// Conditionally select between two 3x4 transformation matrices
// NOTE: 
// This function uses a conditional select instruction to avoid a branch.
// 
inline const Transform3 select( const Transform3 & tfrm0, const Transform3 & tfrm1, vec_uint4 select1 );

#ifdef _VECTORMATH_DEBUG

// Print a 3x4 transformation matrix
// NOTE: 
// Function is only defined when _VECTORMATH_DEBUG is defined.
// 
inline void print( const Transform3 & tfrm );

// Print a 3x4 transformation matrix and an associated string identifier
// NOTE: 
// Function is only defined when _VECTORMATH_DEBUG is defined.
// 
inline void print( const Transform3 & tfrm, const char * name );

#endif

} // namespace Soa
} // namespace Vectormath

#include "vec_soa.h"
#include "quat_soa.h"
#include "mat_soa.h"

#endif
