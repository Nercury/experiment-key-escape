#pragma once

#include "Missing.h"

template<class T, int W, int H> class Matrix;

template<class T, int SIZE>
class Vector
{
public:
	Vector();
	Vector(const T *ptData);

	Vector(const Matrix<T, 1, SIZE> &rhs);
	Vector(const Vector &rhs);
	
	Vector& operator = (const Matrix<T, 1, SIZE> &rhs);
	Vector& operator = (const Vector &rhs);
	
	bool operator == (const Vector &rhs) const;
	bool operator != (const Vector &rhs) const;
	bool operator < (const Vector &rhs) const;
	bool operator <= (const Vector &rhs) const;
	bool operator > (const Vector &rhs) const;
	bool operator >= (const Vector &rhs) const;
	int compare(const Vector& other) const;

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

	Matrix<T, 1, SIZE>& asMatrix();
	const Matrix<T, 1, SIZE>& asMatrix() const;
	const Matrix<T, SIZE, 1>& asTMatrix() const;
	Matrix<T, SIZE, 1>& asTMatrix();

public:
	static int size();
	T coords[SIZE];
};

#define IMPLEMENT_POINT_ACCESSOR2(a,b)\
Vector<T, 2> a##b() const\
{\
	return Vector<T, 2>(a, b);\
}

#define IMPLEMENT_POINT_ACCESSOR3(a, b, c)\
Vector<T, 3> a##b##c() const\
{\
	return Vector<T, 3>(a, b, c);\
}


#define IMPLEMENT_POINT_ACCESSOR4(a, b, c, d)\
Vector<T, 4> a##b##c##d() const\
{\
	return Vector<T, 4>(a, b, c, d);\
}

#include "Vector1.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Vector.inline.h"

