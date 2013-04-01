#pragma once

#include "Vector.h"

template<class T>
class Vector<T, 1>
{
public:
	Vector();
	Vector(T inX);
	Vector(const Matrix<T, 1, 1> &rhs);
	Vector(const Vector &rhs);

	Vector& operator = (const Vector &rhs);
	Vector& operator = (const Matrix<T, 1, 1> &rhs);

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
	Vector operator * (const T &rhs) const;
	Vector operator / (const T &rhs) const;
	Vector& operator += (const Vector &rhs);
	Vector& operator -= (const Vector &rhs);
	Vector& operator *= (const T &rhs);
	Vector& operator /= (const T &rhs);
	Vector& operator - ();

	T length() const;
	T length2() const;
	Matrix<T, 1, 1>& asMatrix();
	const Matrix<T, 1, 1>& asMatrix() const;
	bool hasNan() const;
	bool hasInf() const;
	
public:
	T x;

public:
	IMPLEMENT_POINT_ACCESSOR2(x,x)
	IMPLEMENT_POINT_ACCESSOR3(x, x, x)
	IMPLEMENT_POINT_ACCESSOR4(x, x, x, x)

};

template<class U, class T>
static inline Vector<T, 1> operator * (const U &lhs, const Vector<T, 1> &rhs);

//==============================================================================
//	TYPE DECLARATIONS
//==============================================================================
typedef Vector<float, 1> 	Vector1f;
typedef Vector<int, 1> 		Vector1i;
typedef Vector<double, 1>	Vector1d;

//==============================================================================
//	INLINED CODE
//==============================================================================
#include "Vector1.inline.h"

