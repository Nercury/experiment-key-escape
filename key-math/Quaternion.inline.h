#pragma once


//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "Quaternion.h"
#include <cmath>

//==============================================================================
//	CLASS Quaternion
//==============================================================================
//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T>::Quaternion()
:
	w(1),
	x(0),
	y(1),
	z(0)
{}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T>::Quaternion(T inW, T inX, T inY, T inZ)
:
	w(inW),
	x(inX),
	y(inY),
	z(inZ)
{}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T>::Quaternion(const Vector<T,3> &axis, T angle)
:
	w(),
	x(),
	y(),
	z()
{
	float sinAngleOver2 = sin(angle/2);
	w = cos(angle/2);
	x = reinterpret_cast<const T*>(&axis)[0]*sinAngleOver2;
	y = reinterpret_cast<const T*>(&axis)[1]*sinAngleOver2;
	z = reinterpret_cast<const T*>(&axis)[2]*sinAngleOver2;
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T>::Quaternion(const Matrix<T, 1, 4> &rhs)
:
	w(reinterpret_cast<const T*>(&rhs)[0]),
	x(reinterpret_cast<const T*>(&rhs)[1]),
	y(reinterpret_cast<const T*>(&rhs)[2]),
	z(reinterpret_cast<const T*>(&rhs)[3])
{}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T>& Quaternion<T>::operator = (const Matrix<T, 1, 4> &rhs)
{
	w = reinterpret_cast<const T*>(&rhs)[0];
	x = reinterpret_cast<const T*>(&rhs)[1];
	y = reinterpret_cast<const T*>(&rhs)[2];
	z = reinterpret_cast<const T*>(&rhs)[3];
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T>::Quaternion(const Quaternion<T> &rhs)
:
	w(rhs.w),
	x(rhs.x),
	y(rhs.y),
	z(rhs.z)
{}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T>& Quaternion<T>::operator = (const Quaternion<T> &rhs)
{
	w = rhs.w;
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
bool Quaternion<T>::operator == (const Quaternion<T> &rhs) const
{
	return (rhs.w == w) && (rhs.x == x) && (rhs.y == y) && (rhs.z == z);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Quaternion<T>::operator != (const Quaternion<T> &rhs) const
{
	return (rhs.w != w) || (rhs.x != x) || (rhs.y != y) || (rhs.z != z);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Quaternion<T>::operator < (const Quaternion<T> &rhs) const
{
	return (w < rhs.w) || ((w == rhs.w) && ((x < rhs.x) || ((x == rhs.x) && ((y < rhs.y) || ((y == rhs.y) && (z < rhs.z))))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Quaternion<T>::operator <= (const Quaternion<T> &rhs) const
{
	return (w < rhs.w) || ((w == rhs.w) && ((x < rhs.x) || ((x == rhs.x) && ((y < rhs.y) || ((y == rhs.y) && (z <= rhs.z))))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Quaternion<T>::operator > (const Quaternion<T> &rhs) const
{
	return (w > rhs.w) || ((w == rhs.w) && ((x > rhs.x) || ((x == rhs.x) && ((y > rhs.y) || ((y == rhs.y) && (z > rhs.z))))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Quaternion<T>::operator >= (const Quaternion<T> &rhs) const
{
	return (w > rhs.w) || ((w == rhs.w) && ((x > rhs.x) || ((x == rhs.x) && ((y > rhs.y) || ((y == rhs.y) && (z >= rhs.z))))));
}

//------------------------------------------------------------------------------
//
template<class T>
const T& Quaternion<T>::operator [] (int index) const
{
	return reinterpret_cast<const T*>(this)[index];
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T>::operator T*()
{
	return reinterpret_cast<T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T>::operator const T*() const
{
	return reinterpret_cast<const T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T> Quaternion<T>::operator + (const Quaternion<T> &rhs) const
{
	return Quaternion(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T> Quaternion<T>::operator - (const Quaternion<T> &rhs) const
{
	return Quaternion(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w);
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T> Quaternion<T>::operator * (const Quaternion<T> &rhs) const
{
	return Quaternion(
		w*rhs.w - x*rhs.x - y*rhs.y - z*rhs.z,
		w*rhs.x + x*rhs.w + y*rhs.z - z*rhs.y,
		w*rhs.y + y*rhs.w + z*rhs.x - x*rhs.z,
		w*rhs.z + z*rhs.w + x*rhs.y - y*rhs.x
	);
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T> Quaternion<T>::operator * (const T &rhs) const
{
	return Quaternion(w*rhs, x*rhs, y*rhs, z*rhs);
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T> Quaternion<T>::operator / (const T &rhs) const
{
	return Quaternion(w/rhs, x/rhs, y/rhs, z/rhs);
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T>& Quaternion<T>::operator += (const Quaternion<T> &rhs)
{
	w+= rhs.w; x += rhs.x; y += rhs.y; z += rhs.z;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T>& Quaternion<T>::operator -= (const Quaternion<T> &rhs)
{
	w -= rhs.w; x -= rhs.x; y -= rhs.y; z -= rhs.z;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T>& Quaternion<T>::operator *= (const T &rhs)
{
	*this = *this * rhs;

	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T>& Quaternion<T>::operator /= (const T &rhs)
{
	w /= rhs; x /= rhs; y /= rhs; z /= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T>& Quaternion<T>::operator - ()
{
	x = -x, y = -y; z = -z; w = -w;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
float Quaternion<T>::length()
{
	return sqrt(length2());
}

//------------------------------------------------------------------------------
//
template<class T>
float Quaternion<T>::length2()
{
	return w*w+x*x+y*y+z*z;
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T>& Quaternion<T>::scale(float newLength)
{
	float s = newLength/length();
	w *= s;	x *= s, y *= s; z *= s;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T>& Quaternion<T>::normalize()
{
	return scale(1.0f);
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T> Quaternion<T>::conjugate()
{
	return Quaternion(w, -x, -y, -z);
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T> Quaternion<T>::unitInverse()	//	assumes we have a unit quaternion
{
	return conjugate();
}

//------------------------------------------------------------------------------
//
template<class T>
Quaternion<T> Quaternion<T>::inverse()
{
	return conjugate()/length2();
}

//------------------------------------------------------------------------------
//
template<class T>
void Quaternion<T>::to4x4Matrix(Matrix<T, 4, 4> *outMatrix)
{
	// avoid depending on Matrix.h
	T* m = reinterpret_cast<T*>(outMatrix);
	
	// orginalus budas
	float xx = x*x;	float xy = x*y;
	float xz = x*z;	float xw = x*w;

	float yy = y*y;	float yz = y*z;
	float yw = y*w;

	float zz = z*z;	float zw = z*w;
	
	m[0*4+0] = 1-2*(yy+zz); m[1*4+0] =   2*(xy-zw); m[2*4+0] =   2*(xz+yw); m[3*4+0] = 0;
	m[0*4+1] =   2*(xy+zw); m[1*4+1] = 1-2*(xx+zz); m[2*4+1] =   2*(yz-xw); m[3*4+1] = 0;
	m[0*4+2] =   2*(xz-yw); m[1*4+2] =   2*(yz+xw); m[2*4+2] = 1-2*(xx+yy); m[3*4+2] = 0;
	m[0*4+3] =           0; m[1*4+3] =           0; m[2*4+3] =           0; m[3*4+3] = 1;
}

//------------------------------------------------------------------------------
//
template<class T>
void Quaternion<T>::to3x3Matrix(Matrix<T, 3, 3> *outMatrix)
{
	// avoid depending on Matrix.h
	T* m = reinterpret_cast<T*>(outMatrix);

	float xx = x*x;	float xy = x*y;
	float xz = x*z;	float xw = x*w;

	float yy = y*y;	float yz = y*z;
	float yw = y*w;

	float zz = z*z;	float zw = z*w;

	m[0*3+0] = 1-2*(yy+zz); m[1*3+0] =   2*(xy-zw); m[2*3+0] =   2*(xz+yw);
	m[0*3+1] =   2*(xy+zw); m[1*3+1] = 1-2*(xx+zz); m[2*3+1] =   2*(yz-xw);
	m[0*3+2] =   2*(xz-yw); m[1*3+2] =   2*(yz+xw); m[2*3+2] = 1-2*(xx+yy);
}

//------------------------------------------------------------------------------
//
template<class T>
static inline Quaternion<T> operator * (const T &lhs, const Quaternion<T> &rhs)
{
	return rhs * lhs;
}

