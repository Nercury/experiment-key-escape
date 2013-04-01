#pragma once

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "Vector4.h"

//==============================================================================
//	CLASS Vector4
//==============================================================================
//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector()
:
	x(),
	y(),
	z(),
	w()
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(T inX, T inY, T inZ, T inW)
:
	x(inX),
	y(inY),
	z(inZ),
	w(inW)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 1> &inX, const Vector<T, 1> &inY, const Vector<T, 1> &inZ, const Vector<T, 1> &inW)
:
	x(inX.x),
	y(inY.x),
	z(inZ.x),
	w(inW.x)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 1> &inX, const Vector<T, 1> &inY, const Vector<T, 1> &inZ, const T &inW)
:
	x(inX.x),
	y(inY.x),
	z(inZ.x),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 1> &inX, const Vector<T, 1> &inY, const T &inZ, const T &inW)
:
	x(inX.x),
	y(inY.x),
	z(inZ),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 1> &inX, const T &inY, const Vector<T, 1> &inZ, const T &inW)
:
	x(inX.x),
	y(inY),
	z(inZ.x),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const T &inX, const Vector<T, 1> &inY, const Vector<T, 1> &inZ, const T &inW)
:
	x(inX),
	y(inY.x),
	z(inZ.x),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 1> &inX, const T &inY, const T &inZ, const T &inW)
:
	x(inX.x),
	y(inY),
	z(inZ),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const T &inX, const Vector<T, 1> &inY, const T &inZ, const T &inW)
:
	x(inX),
	y(inY.x),
	z(inZ),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 1> &inX, const Vector<T, 1> &inY, const T &inZ, const Vector<T, 1> &inW)
:
	x(inX.x),
	y(inY.x),
	z(inZ),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 1> &inX, const T &inY, const T &inZ, const Vector<T, 1> &inW)
:
	x(inX.x),
	y(inY),
	z(inZ),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const T &inX, const Vector<T, 1> &inY, const T &inZ, const Vector<T, 1> &inW)
:
	x(inX),
	y(inY.x),
	z(inZ),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const T &inX, const T &inY, const T &inZ, const Vector<T, 1> &inW)
:
	x(inX),
	y(inY),
	z(inZ),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 1> &inX, const T &inY, const Vector<T, 1> &inZ, const Vector<T, 1> &inW)
:
	x(inX.x),
	y(inY),
	z(inZ.x),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const T &inX, const T &inY, const Vector<T, 1> &inZ, const Vector<T, 1> &inW)
:
	x(inX),
	y(inY),
	z(inZ.x),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const T &inX, const Vector<T, 1> &inY, const Vector<T, 1> &inZ, const Vector<T, 1> &inW)
:
	x(inX),
	y(inY.x),
	z(inZ.x),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 2> &inXY, const Vector<T, 1> &inZ, const Vector<T, 1> &inW)
:
	x(inXY.x),
	y(inXY.y),
	z(inZ.x),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 2> &inXY, const Vector<T, 1> &inZ, const T &inW)
:
	x(inXY.x),
	y(inXY.y),
	z(inZ.x),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 2> &inXY, const T &inZ, const T &inW)
:
	x(inXY.x),
	y(inXY.y),
	z(inZ),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 2> &inXY, const T &inZ, const Vector<T, 1> &inW)
:
	x(inXY.x),
	y(inXY.y),
	z(inZ),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 1> &inX, const Vector<T, 2> &inYZ, const Vector<T, 1> &inW)
:
	x(inX.x),
	y(inYZ.x),
	z(inYZ.y),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 1> &inX, const Vector<T, 2> &inYZ, const T &inW)
:
	x(inX.x),
	y(inYZ.x),
	z(inYZ.y),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const T &inX, const Vector<T, 2> &inYZ, const T &inW)
:
	x(inX),
	y(inYZ.x),
	z(inYZ.y),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const T &inX, const Vector<T, 2> &inYZ, const Vector<T, 1> &inW)
:
	x(inX),
	y(inYZ.x),
	z(inYZ.y),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 1> &inX, const Vector<T, 1> &inY, const Vector<T, 2> &inZW)
:
	x(inX.x),
	y(inY.x),
	z(inZW.x),
	w(inZW.y)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 1> &inX, const T &inY, const Vector<T, 2> &inZW)
:
	x(inX.x),
	y(inY),
	z(inZW.x),
	w(inZW.y)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const T &inX, const T &inY, const Vector<T, 2> &inZW)
:
	x(inX),
	y(inY),
	z(inZW.x),
	w(inZW.y)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const T &inX, const Vector<T, 1> &inY, const Vector<T, 2> &inZW)
:
	x(inX),
	y(inY.x),
	z(inZW.x),
	w(inZW.y)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 2> &inXY, const Vector<T, 2> &inZW)
:
	x(inXY.x),
	y(inXY.y),
	z(inZW.x),
	w(inZW.y)
{}

	
//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 3> &inXYZ, const Vector<T, 1> &inW)
:
	x(inXYZ.x),
	y(inXYZ.y),
	z(inXYZ.z),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 3> &inXYZ, const T &inW)
:
	x(inXYZ.x),
	y(inXYZ.y),
	z(inXYZ.z),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 1> &inX, const Vector<T, 3> &inYZW)
:
	x(inX.x),
	y(inYZW.x),
	z(inYZW.y),
	w(inYZW.z)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const T &inX, const Vector<T, 3> &inYZW)
:
	x(inX),
	y(inYZW.x),
	z(inYZW.y),
	w(inYZW.z)
{}


//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Matrix<T, 1, 4> &rhs)
:
	x(reinterpret_cast<const T*>(&rhs)[0]),
	y(reinterpret_cast<const T*>(&rhs)[1]),
	z(reinterpret_cast<const T*>(&rhs)[2]),
	w(reinterpret_cast<const T*>(&rhs)[3])
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>::Vector(const Vector<T, 4> &rhs)
:
	x(rhs.x),
	y(rhs.y),
	z(rhs.z),
	w(rhs.w)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>& Vector<T, 4>::operator = (const Matrix<T, 1, 4> &rhs)
{
	x = reinterpret_cast<const T*>(&rhs)[0];
	y = reinterpret_cast<const T*>(&rhs)[1];
	z = reinterpret_cast<const T*>(&rhs)[2];
	w = reinterpret_cast<const T*>(&rhs)[3];
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>& Vector<T, 4>::operator = (const Vector<T, 4> &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 4>::operator == (const Vector<T, 4> &rhs) const
{
	return (rhs.x == x) && (rhs.y == y) && (rhs.z == z) && (rhs.w == w);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 4>::operator != (const Vector<T, 4> &rhs) const
{
	return (rhs.x != x) || (rhs.y != y) || (rhs.z != z) || (rhs.w != w);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 4>::operator < (const Vector<T, 4> &rhs) const
{
	return (x < rhs.x) || ((x == rhs.x) && ((y < rhs.y) || ((y == rhs.y) && ((z < rhs.z) || ((z == rhs.z) && (w < rhs.w))))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 4>::operator <= (const Vector<T, 4> &rhs) const
{
	return (x < rhs.x) || ((x == rhs.x) && ((y < rhs.y) || ((y == rhs.y) && ((z < rhs.z) || ((z == rhs.z) && (w <= rhs.w))))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 4>::operator > (const Vector<T, 4> &rhs) const
{
	return (x > rhs.x) || ((x == rhs.x) && ((y > rhs.y) || ((y == rhs.y) && ((z > rhs.z) || ((z == rhs.z) && (w > rhs.w))))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 4>::operator >= (const Vector<T, 4> &rhs) const
{
	return (x > rhs.x) || ((x == rhs.x) && ((y > rhs.y) || ((y == rhs.y) && ((z > rhs.z) || ((z == rhs.z) && (w >= rhs.w))))));
}

//------------------------------------------------------------------------------
//
template<class T>
const T& Vector<T, 4>::operator [] (int index) const
{
	return reinterpret_cast<const T*>(this)[index];
}

//------------------------------------------------------------------------------
//
template<class T>
T& Vector<T, 4>::operator [] (int index)
{
	return reinterpret_cast<T*>(this)[index];
}

//------------------------------------------------------------------------------
//
template<class T>
T* Vector<T, 4>::ptr()
{
	return reinterpret_cast<T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
const T* Vector<T, 4>::ptr() const
{
	return reinterpret_cast<const T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4> Vector<T, 4>::operator + (const Vector<T, 4> &rhs) const
{
	return Vector<T, 4>(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4> Vector<T, 4>::operator - (const Vector<T, 4> &rhs) const
{
	return Vector<T, 4>(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w);
}

//------------------------------------------------------------------------------
//
template<class T>
T Vector<T, 4>::operator * (const Vector<T, 4> &rhs) const
{
	return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4> Vector<T, 4>::operator * (const T &rhs) const
{
	return Vector<T, 4>(x*rhs, y*rhs, z*rhs, w*rhs);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4> Vector<T, 4>::operator / (const T &rhs) const
{
	return Vector<T, 4>(x/rhs, y/rhs, z/rhs, w/rhs);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>& Vector<T, 4>::operator += (const Vector<T, 4> &rhs)
{
	x += rhs.x; y += rhs.y; z += rhs.z; w+= rhs.w;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>& Vector<T, 4>::operator -= (const Vector<T, 4> &rhs)
{
	x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>& Vector<T, 4>::operator *= (const T &rhs)
{
	x *= rhs; y *= rhs; z *= rhs; w *= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>& Vector<T, 4>::operator /= (const T &rhs)
{
	x /= rhs; y /= rhs; z /= rhs; w /= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4>& Vector<T, 4>::operator - ()
{
	x = -x, y = -y; z = -z; w = -w;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
float Vector<T, 4>::length() const
{
	return sqrt(length2());
}

//------------------------------------------------------------------------------
//
template<class T>
float Vector<T, 4>::length2() const
{
	return x*x+y*y+z*z+w*w;
}

//------------------------------------------------------------------------------
//
template<class T>
void Vector<T, 4>::scale(float newLength)
{
	*this = scaled(newLength);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4> Vector<T, 4>::scaled(float newLength) const
{
	float scale = newLength/length();
	return *this * scale;
}

//------------------------------------------------------------------------------
//
template<class T>
void Vector<T, 4>::normalize()
{
	scale(1.0f);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 4> Vector<T, 4>::normalize() const
{
	return scaled(1.0);
}

//------------------------------------------------------------------------------
//
template<class T>
Matrix<T, 4, 1>& Vector<T, 4>::asMatrix()
{
	return *(Matrix<T, 4, 1>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
Matrix<T, 1, 4>& Vector<T, 4>::asTMatrix()
{
	return *(Matrix<T, 1, 4>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
const Matrix<T, 4, 1>& Vector<T, 4>::asMatrix() const
{
	return *(Matrix<T, 4, 1>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
const Matrix<T, 1, 4>& Vector<T, 4>::asTMatrix() const
{
	return *(Matrix<T, 1, 4>*)this;
}

template<class T>
static inline Vector<T,4> operator * (const T &lhs, const Vector<T,4> &rhs)
{
	return rhs * lhs;
}

template<class T, class U>
static inline Vector<U,4> operator * (const Matrix<T, 4, 4> &lhs, const Vector<U,4> &rhs)
{
	return lhs * rhs.asTMatrix();
}
