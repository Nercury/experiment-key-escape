#pragma once

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "Vector.h"
#include <string>

//==============================================================================
//	CLASS Vector
//==============================================================================

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
int Vector<T, SIZE>::size()
{
	return SIZE;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Vector<T, SIZE>::Vector()
{}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Vector<T, SIZE>::Vector(const T *ptData)
{
	memcpy(coords, ptData, sizeof(T)*SIZE);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Vector<T, SIZE>::Vector(const Matrix<T, 1, SIZE> &rhs)
{
	memcpy(coords, &rhs, sizeof(T)*SIZE);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Vector<T, SIZE>::Vector(const Vector<T, SIZE> &rhs)
{
	memcpy(coords, rhs.coords, sizeof(T)*SIZE);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Vector<T, SIZE>& Vector<T, SIZE>::operator = (const Matrix<T, 1, SIZE> &rhs)
{
	memcpy(coords, &rhs, sizeof(T)*SIZE);
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Vector<T, SIZE>& Vector<T, SIZE>::operator = (const Vector<T, SIZE> &rhs)
{
	memcpy(coords, rhs.coords, sizeof(T)*SIZE);
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
bool Vector<T, SIZE>::operator == (const Vector<T, SIZE> &rhs) const
{
	return memcmp(coords, rhs.coords, sizeof(T)*SIZE) == 0;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
bool Vector<T, SIZE>::operator != (const Vector<T, SIZE> &rhs) const
{
	return memcmp(coords, rhs.coords, sizeof(T)*SIZE) != 0;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
bool Vector<T, SIZE>::operator < (const Vector<T, SIZE> &rhs) const
{
	for (int i = 0; i < SIZE; ++i)
	{
		if ((*this)[i] < rhs[i])		return true;
		else if ((*this)[i] > rhs[i])	return false;
	}
	return false;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
bool Vector<T, SIZE>::operator <= (const Vector<T, SIZE> &rhs) const
{
	for (int i = 0; i < SIZE; ++i)
	{
		if ((*this)[i] < rhs[i])		return true;
		else if ((*this)[i] > rhs[i])	return false;
	}
	return true;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
bool Vector<T, SIZE>::operator > (const Vector<T, SIZE> &rhs) const
{
	for (int i = 0; i < SIZE; ++i)
	{
		if ((*this)[i] > rhs[i])		return true;
		else if ((*this)[i] < rhs[i])	return false;
	}
	return false;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
bool Vector<T, SIZE>::operator >= (const Vector<T, SIZE> &rhs) const
{
	for (int i = 0; i < SIZE; ++i)
	{
		if ((*this)[i] > rhs[i])		return true;
		else if ((*this)[i] < rhs[i])	return false;
	}
	return true;
}

template<class T, int SIZE>
int Vector<T, SIZE>::compare(const Vector<T, SIZE>& other) const
{
	for (int i = 0; i < SIZE; ++i)
	{
		if ((*this)[i] < other[i])
			return -1;
		else if ((*this)[i] > other[i])
			return 1;
	}
	return 0;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
const T& Vector<T, SIZE>::operator [] (int index) const
{
	return coords[index];
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
T& Vector<T, SIZE>::operator [] (int index)
{
	return coords[index];
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
T* Vector<T, SIZE>::ptr()
{
	return reinterpret_cast<T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
const T* Vector<T, SIZE>::ptr() const
{
	return reinterpret_cast<const T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Vector<T, SIZE> Vector<T, SIZE>::operator + (const Vector<T, SIZE> &rhs) const
{
	Vector<T, SIZE> pt;
	for (int i = 0; i < SIZE; ++i) pt[i] = coords[i] + rhs.coords[i];
	return pt;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Vector<T, SIZE> Vector<T, SIZE>::operator - (const Vector<T, SIZE> &rhs) const
{
	Vector<T, SIZE> pt;
	for (int i = 0; i < SIZE; ++i) pt[i] = coords[i] - rhs.coords[i];
	return pt;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Matrix<T, 1, SIZE>& Vector<T, SIZE>::asMatrix()
{
	return *reinterpret_cast<Matrix<T, 1, SIZE>*>(this);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
const Matrix<T, 1, SIZE>& Vector<T, SIZE>::asMatrix() const
{
	return *reinterpret_cast<const Matrix<T, 1, SIZE>*>(this);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
const Matrix<T, SIZE, 1>& Vector<T, SIZE>::asTMatrix() const
{
	return *reinterpret_cast<const Matrix<T, SIZE, 1>*>(this);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Matrix<T, SIZE, 1>& Vector<T, SIZE>::asTMatrix()
{
	return *reinterpret_cast<Matrix<T, SIZE, 1>*>(this);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
T Vector<T, SIZE>::operator * (const Vector &rhs) const
{
	T v = 0;
	for (int i = 0; i < SIZE; ++i)
		v += (*this)[i]*rhs[i];

	return v;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Vector<T, SIZE> Vector<T, SIZE>::operator * (const T &rhs) const
{
	Vector<T, SIZE> pt;
	for (int i = 0; i < SIZE; ++i) pt[i] = coords[i] * rhs;
	return pt;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Vector<T, SIZE> Vector<T, SIZE>::operator / (const T &rhs) const
{
	Vector<T, SIZE> pt;
	for (int i = 0; i < SIZE; ++i) pt[i] = coords[i] / rhs;
	return pt;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Vector<T, SIZE>& Vector<T, SIZE>::operator += (const Vector &rhs)
{
	for (int i = 0; i < SIZE; ++i) coords[i] += rhs.coords[i];
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Vector<T, SIZE>& Vector<T, SIZE>::operator -= (const Vector &rhs)
{
	for (int i = 0; i < SIZE; ++i) coords[i] -= rhs.coords[i];
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Vector<T, SIZE>& Vector<T, SIZE>::operator *= (const T &rhs)
{
	for (int i = 0; i < SIZE; ++i) coords[i] -= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Vector<T, SIZE>& Vector<T, SIZE>::operator /= (const T &rhs)
{
	for (int i = 0; i < SIZE; ++i) coords[i] /= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Vector<T, SIZE>& Vector<T, SIZE>::operator - ()
{
	for (int i = 0; i < SIZE; ++i) coords[i] = -coords[i];
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
T Vector<T, SIZE>::length() const
{
	return sqrt(length2());
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
T Vector<T, SIZE>::length2() const
{
	T len2 = 0;
	for (int i = 0; i < SIZE; ++i)
		len2 += (*this)[i]*(*this)[i];
	
	return len2;
}