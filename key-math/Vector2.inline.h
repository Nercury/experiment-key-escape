#pragma once

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "Vector2.h"
#include <cmath>


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2>::Vector()
:
	x(),
	y()
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2>::Vector(T inX, T inY)
:
	x(inX),
	y(inY)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2>::Vector(const Vector<T, 1> &inX, const Vector<T, 1> &inY)
:
	x(inX.x),
	y(inY.x)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2>::Vector(const T &inX, const Vector<T, 1> &inY)
:
	x(inX),
	y(inY.x)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2>::Vector(const Vector<T, 1> &inX, const T &inY)
:
	x(inX.x),
	y(inY)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2>::Vector(T inVal)
:
	x(inVal),
	y(inVal)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2>::Vector(const Matrix<T, 1, 2> &rhs)
:
	x(reinterpret_cast<const T*>(&rhs)[0]),
	y(reinterpret_cast<const T*>(&rhs)[1])
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2>::Vector(const Vector &rhs)
:
	x(rhs.x),
	y(rhs.y)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2>& Vector<T, 2>::operator = (const Vector<T, 2> &rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2>& Vector<T, 2>::operator = (const Matrix<T, 1, 2> &rhs)
{
	x = reinterpret_cast<const T*>(&rhs)[0];
	y = reinterpret_cast<const T*>(&rhs)[1];
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 2>::operator == (const Vector<T, 2> &rhs) const
{
	return (rhs.x == x) && (rhs.y == y);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 2>::operator != (const Vector<T, 2> &rhs) const
{
	return (rhs.x != x) || (rhs.y != y);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 2>::operator < (const Vector<T, 2> &rhs) const
{
	return (x < rhs.x) || ((x == rhs.x) && (y < rhs.y));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 2>::operator <= (const Vector<T, 2> &rhs) const
{
	return (x < rhs.x) || ((x == rhs.x) && (y <= rhs.y));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 2>::operator > (const Vector<T, 2> &rhs) const
{
	return (x > rhs.x) || ((x == rhs.x) && (y > rhs.y));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 2>::operator >= (const Vector<T, 2> &rhs) const
{
	return (x > rhs.x) || ((x == rhs.x) && (y >= rhs.y));
}

//------------------------------------------------------------------------------
//
template<class T>
const T& Vector<T, 2>::operator [] (int index) const
{
	return reinterpret_cast<const T*>(this)[index];
}

//------------------------------------------------------------------------------
//
template<class T>
T& Vector<T, 2>::operator [] (int index)
{
	return reinterpret_cast<T*>(this)[index];
}

//------------------------------------------------------------------------------
//
template<class T>
T* Vector<T, 2>::ptr()
{
	return reinterpret_cast<T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
const T* Vector<T, 2>::ptr() const
{
	return reinterpret_cast<const T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2> Vector<T, 2>::operator + (const Vector<T, 2> &rhs) const
{
	return Vector<T, 2>(x+rhs.x, y+rhs.y);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2> Vector<T, 2>::operator - (const Vector<T, 2> &rhs) const
{
	return Vector<T, 2>(x-rhs.x, y-rhs.y);
}

//------------------------------------------------------------------------------
//
template<class T>
T Vector<T, 2>::operator * (const Vector<T, 2> &rhs) const
{
	return x*rhs.x + y*rhs.y;
}

//------------------------------------------------------------------------------
//
template<class T>
T Vector<T, 2>::operator ^ (const Vector<T, 2> &rhs) const
{
	return x*rhs.y - y*rhs.x;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2> Vector<T, 2>::operator * (const T &rhs) const
{
	return Vector<T, 2>(x*rhs, y*rhs);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2> Vector<T, 2>::operator / (const T &rhs) const
{
	return Vector<T, 2>(x/rhs, y/rhs);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2>& Vector<T, 2>::operator += (const Vector<T, 2> &rhs)
{
	x += rhs.x; y += rhs.y;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2>& Vector<T, 2>::operator -= (const Vector<T, 2> &rhs)
{
	x -= rhs.x; y -= rhs.y;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2>& Vector<T, 2>::operator *= (const T &rhs)
{
	x *= rhs; y *= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2>& Vector<T, 2>::operator /= (const T &rhs)
{
	x /= rhs; y /= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2>& Vector<T, 2>::operator - ()
{
	x = -x, y = -y;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2>& Vector<T, 2>::operator ~ ()
{
	*this = perpendicular();
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
float Vector<T, 2>::length() const
{
	return sqrt(length2());
}

//------------------------------------------------------------------------------
//
template<class T>
float Vector<T, 2>::length2() const
{
	return x*x+y*y;
}

//------------------------------------------------------------------------------
//
template<class T>
void Vector<T, 2>::scale(float newLength)
{
	*this = scaled(newLength);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2> Vector<T, 2>::scaled(float newLength) const
{
	T scale = newLength/length();
	return *this * scale;
}


//------------------------------------------------------------------------------
//
template<class T>
void Vector<T, 2>::normalize()
{
	scale(1.0f);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2> Vector<T, 2>::normalize() const
{
	return scaled(1.0f);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 2> Vector<T, 2>::perpendicular() const
{
	return Vector<T, 2>(-y, x);
}

//------------------------------------------------------------------------------
//
template<class T>
Matrix<T, 1, 2>& Vector<T, 2>::asTMatrix()
{
	return *(Matrix<T, 1, 2>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
const Matrix<T, 1, 2>& Vector<T, 2>::asTMatrix() const
{
	return *(Matrix<T, 1, 2>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
Matrix<T, 2, 1>& Vector<T, 2>::asMatrix()
{
	return *(Matrix<T, 2, 1>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
const Matrix<T, 2, 1>& Vector<T, 2>::asMatrix() const
{
	return *(Matrix<T, 2, 1>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 2>::hasNan() const
{
	return isnan(x) || isnan(y);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 2>::hasInf() const
{
	return isinf(x) || isinf(y);
}

//------------------------------------------------------------------------------
//
template<class U, class T>
static inline Vector<T, 2> operator * (const U &lhs, const Vector<T, 2> &rhs)
{
	return rhs * lhs;
}

