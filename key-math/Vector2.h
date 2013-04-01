#pragma once

#include "Vector.h"

//	+ : addition of points
//	- : different of points
//	* : dot product or scalar multiplication
//	/ : scalar division
//	^ : cross product (determinant)
//	~ : perpendicular

template<class T>
class Vector<T, 2>
{
public:
	Vector();
	Vector(T inX, T inY);
	Vector(const Vector<T, 1> &inX, const Vector<T, 1> &inY);
	Vector(const T &inX, const Vector<T, 1> &inY);
	Vector(const Vector<T, 1> &inX, const T &inY);
	explicit Vector(T inVal);
	Vector(const Matrix<T, 1, 2> &rhs);
	Vector(const Vector &rhs);
	Vector& operator = (const Vector &rhs);
	Vector& operator = (const Matrix<T, 1, 2> &rhs);
	bool operator == (const Vector &rhs) const;
	bool operator != (const Vector &rhs) const;
	bool operator < (const Vector &rhs) const;
	bool operator <= (const Vector &rhs) const;
	bool operator > (const Vector &rhs) const;
	bool operator >= (const Vector &rhs) const;
	const T& operator [] (int index) const;
	T& operator [] (int index);

	T* ptr();
	const T* ptr() const;
	
	Vector operator + (const Vector &rhs) const;
	Vector operator - (const Vector &rhs) const;
	T operator * (const Vector &rhs) const;
	T operator ^ (const Vector &rhs) const;
	Vector operator * (const T &rhs) const;
	Vector operator / (const T &rhs) const;
	Vector& operator += (const Vector &rhs);
	
	Vector& operator -= (const Vector &rhs);
	Vector& operator *= (const T &rhs);
	Vector& operator /= (const T &rhs);
	Vector& operator - ();
	Vector& operator ~ ();
	float length() const;
	float length2() const;

	void scale(float newLength);
	Vector scaled(float newLength) const;

	Vector normalize() const;
	void normalize();

	Vector perpendicular() const;

	Matrix<T, 1, 2>& asTMatrix();
	const Matrix<T, 1, 2>& asTMatrix() const;
	Matrix<T, 2, 1>& asMatrix();
	const Matrix<T, 2, 1>& asMatrix() const;
	bool hasNan() const;
	bool hasInf() const;

	IMPLEMENT_POINT_ACCESSOR2(x,x); IMPLEMENT_POINT_ACCESSOR2(x,y);
	IMPLEMENT_POINT_ACCESSOR2(y,x); IMPLEMENT_POINT_ACCESSOR2(y,y);

	IMPLEMENT_POINT_ACCESSOR3(x,x,x); IMPLEMENT_POINT_ACCESSOR3(x,x,y);
	IMPLEMENT_POINT_ACCESSOR3(x,y,x); IMPLEMENT_POINT_ACCESSOR3(x,y,y);
	IMPLEMENT_POINT_ACCESSOR3(y,x,x); IMPLEMENT_POINT_ACCESSOR3(y,x,y);
	IMPLEMENT_POINT_ACCESSOR3(y,y,x); IMPLEMENT_POINT_ACCESSOR3(y,y,y);

	IMPLEMENT_POINT_ACCESSOR4(x,x,x,x); IMPLEMENT_POINT_ACCESSOR4(x,x,x,y);
	IMPLEMENT_POINT_ACCESSOR4(x,x,y,x); IMPLEMENT_POINT_ACCESSOR4(x,x,y,y);
	IMPLEMENT_POINT_ACCESSOR4(x,y,x,x); IMPLEMENT_POINT_ACCESSOR4(x,y,x,y);
	IMPLEMENT_POINT_ACCESSOR4(x,y,y,x); IMPLEMENT_POINT_ACCESSOR4(x,y,y,y);

	IMPLEMENT_POINT_ACCESSOR4(y,x,x,x); IMPLEMENT_POINT_ACCESSOR4(y,x,x,y);
	IMPLEMENT_POINT_ACCESSOR4(y,x,y,x); IMPLEMENT_POINT_ACCESSOR4(y,x,y,y);
	IMPLEMENT_POINT_ACCESSOR4(y,y,x,x); IMPLEMENT_POINT_ACCESSOR4(y,y,x,y);
	IMPLEMENT_POINT_ACCESSOR4(y,y,y,x); IMPLEMENT_POINT_ACCESSOR4(y,y,y,y);

public:
	T x;
	T y;
};

template<class U, class T>
static inline Vector<T, 2> operator * (const U &lhs, const Vector<T, 2> &rhs);

//==============================================================================
//	TYPE DECLARATION
//==============================================================================
typedef Vector<float, 2> 	Vector2f;
typedef Vector<int, 2> 		Vector2i;
typedef Vector<double, 2>	Vector2d;

//==============================================================================
//	INLINED CODE
//==============================================================================
#include "Vector2.inline.h"

