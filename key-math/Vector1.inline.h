#pragma once

#include "Vector1.h"
#include <cmath>


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 1>::Vector()
:
	x()
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 1>::Vector(T inX)
:
	x(inX)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 1>::Vector(const Matrix<T, 1, 1> &rhs)
:
	x(*reinterpret_cast<const T*>(&rhs))
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 1>::Vector(const Vector<T, 1> &rhs)
:
	x(rhs.x)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 1>& Vector<T, 1>::operator = (const Vector<T, 1> &rhs)
{
	x = rhs.x;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 1>& Vector<T, 1>::operator = (const Matrix<T, 1, 1> &rhs)
{
	x = *reinterpret_cast<const T*>(&rhs);
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 1>::operator == (const Vector<T, 1> &rhs) const
{
	return (rhs.x == x);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 1>::operator != (const Vector<T, 1> &rhs) const
{
	return (rhs.x != x);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 1>::operator < (const Vector<T, 1> &rhs) const
{
	return (x < rhs.x);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 1>::operator <= (const Vector<T, 1> &rhs) const
{
	return (x < rhs.x);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 1>::operator > (const Vector<T, 1> &rhs) const
{
	return (x > rhs.x);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 1>::operator >= (const Vector<T, 1> &rhs) const
{
	return (x > rhs.x);
}

//------------------------------------------------------------------------------
//
template<class T>
const T& Vector<T, 1>::operator [] (int index) const
{
	return reinterpret_cast<const T*>(this)[index];
}

//------------------------------------------------------------------------------
//
template<class T>
T& Vector<T, 1>::operator [] (int index)
{
	return reinterpret_cast<T*>(this)[index];
}

//------------------------------------------------------------------------------
//
template<class T>
T* Vector<T, 1>::ptr()
{
	return reinterpret_cast<T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
const T* Vector<T, 1>::ptr() const
{
	return reinterpret_cast<const T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 1> Vector<T, 1>::operator + (const Vector<T, 1> &rhs) const
{
	return Vector<T, 1>(x+rhs.x);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 1> Vector<T, 1>::operator - (const Vector<T, 1> &rhs) const
{
	return Vector<T, 1>(x-rhs.x);
}

//------------------------------------------------------------------------------
//
template<class T>
T Vector<T, 1>::operator * (const Vector<T, 1> &rhs) const
{
	return x*rhs.x;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 1> Vector<T, 1>::operator * (const T &rhs) const
{
	return Vector<T, 1>(x*rhs);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 1> Vector<T, 1>::operator / (const T &rhs) const
{
	return Vector<T, 1>(x/rhs);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 1>& Vector<T, 1>::operator += (const Vector<T, 1> &rhs)
{
	x += rhs.x;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 1>& Vector<T, 1>::operator -= (const Vector<T, 1> &rhs)
{
	x -= rhs.x;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 1>& Vector<T, 1>::operator *= (const T &rhs)
{
	x *= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 1>& Vector<T, 1>::operator /= (const T &rhs)
{
	x /= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 1>& Vector<T, 1>::operator - ()
{
	x = -x;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
T Vector<T, 1>::length() const
{
	return x;
}

//------------------------------------------------------------------------------
//
template<class T>
T Vector<T, 1>::length2() const
{
	return x*x;
}

//------------------------------------------------------------------------------
//
template<class T>
Matrix<T, 1, 1>& Vector<T, 1>::asMatrix()
{
	return *(Matrix<T, 1, 1>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
const Matrix<T, 1, 1>& Vector<T, 1>::asMatrix() const
{
	return *(Matrix<T, 1, 1>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 1>::hasNan() const
{
	return isnan(x);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 1>::hasInf() const
{
	return isinf(x);
}

//------------------------------------------------------------------------------
//
template<class U, class T>
static inline Vector<T, 1> operator * (const U &lhs, const Vector<T, 1> &rhs)
{
	return rhs * lhs;
}

