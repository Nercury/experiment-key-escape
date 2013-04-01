#pragma once

#include "Vector3.h"

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>::Vector()
:
	x(),
	y(),
	z()
{}

//------------------------------------------------------------------------------
//
template<class T>
template<class U>
Vector<T, 3>::Vector(const U *array)
:
	x(array[0]),
	y(array[1]),
	z(array[2])
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>::Vector(T inX, T inY, T inZ)
:
	x(inX),
	y(inY),
	z(inZ)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>::Vector(const Vector<T, 1> &inX, const Vector<T, 1> &inY, const Vector<T, 1> &inZ)
:
	x(inX.x),
	y(inY.x),
	z(inZ.x)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>::Vector(const T &inX, const Vector<T, 1> &inY, const Vector<T, 1> &inZ)
:
	x(inX),
	y(inY.x),
	z(inZ.x)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>::Vector(const Vector<T, 1> &inX, const T &inY, const Vector<T, 1> &inZ)
:
	x(inX.x),
	y(inY),
	z(inZ.x)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>::Vector(const Vector<T, 1> &inX, const Vector<T, 1> &inY, const T &inZ)
:
	x(inX.x),
	y(inY.x),
	z(inZ)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>::Vector(const T &inX, const T &inY, const Vector<T, 1> &inZ)
:
	x(inX),
	y(inY),
	z(inZ.x)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>::Vector(const Vector<T, 1> &inX, const T &inY, const T &inZ)
:
	x(inX.x),
	y(inY),
	z(inZ)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>::Vector(const Vector<T,2> &inXY, const T &inZ)
:
	x(inXY.x),
	y(inXY.y),
	z(inZ)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>::Vector(const Vector<T,2> &inXY, const Vector<T, 1> &inZ)
:
	x(inXY.x),
	y(inXY.y),
	z(inZ.x)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>::Vector(const T &inX, const Vector<T, 2> &inYZ)
:
	x(inX),
	y(inYZ.x),
	z(inYZ.y)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>::Vector(const Vector<T, 1> &inX, const Vector<T, 2> &inYZ)
:
	x(inX.x),
	y(inYZ.x),
	z(inYZ.y)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>::Vector(T inVal)
:
	x(inVal),
	y(inVal),
	z(inVal)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>::Vector(const Matrix<T, 1, 3> &rhs)
:
	x(reinterpret_cast<const T*>(&rhs)[0]),
	y(reinterpret_cast<const T*>(&rhs)[1]),
	z(reinterpret_cast<const T*>(&rhs)[2])
{}

//------------------------------------------------------------------------------
//
template<class T>
template<class U>
Vector<T, 3>::Vector(const Vector<U,3> &rhs)
:
	x(rhs.x),
	y(rhs.y),
	z(rhs.z)
{}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>& Vector<T, 3>::operator = (const Matrix<T, 1, 3> &rhs)
{
	x = reinterpret_cast<const T*>(&rhs)[0];
	y = reinterpret_cast<const T*>(&rhs)[1];
	z = reinterpret_cast<const T*>(&rhs)[2];
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>& Vector<T, 3>::operator = (const Vector &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 3>::operator == (const Vector &rhs) const
{
	return (rhs.x == x) && (rhs.y == y) && (rhs.z == z);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 3>::operator != (const Vector &rhs) const
{
	return (rhs.x != x) || (rhs.y != y) || (rhs.z != z);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 3>::operator < (const Vector &rhs) const
{
	return (x < rhs.x) || ((x == rhs.x) && ((y < rhs.y) || ((y == rhs.y) && (z < rhs.z))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 3>::operator <= (const Vector &rhs) const
{
	return (x < rhs.x) || ((x == rhs.x) && ((y < rhs.y) || ((y == rhs.y) && (z <= rhs.z))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 3>::operator > (const Vector &rhs) const
{
	return (x > rhs.x) || ((x == rhs.x) && ((y > rhs.y) || ((y == rhs.y) && (z > rhs.z))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 3>::operator >= (const Vector &rhs) const
{
	return (x > rhs.x) || ((x == rhs.x) && ((y > rhs.y) || ((y == rhs.y) && (z >= rhs.z))));
}

template<class T>
int Vector<T, 3>::compare(const Vector<T, 3>& other) const
{
	for (int i = 0; i < 3; ++i)
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
template<class T>
const T& Vector<T, 3>::operator [] (int index) const
{
	return reinterpret_cast<const T*>(this)[index];
}

//------------------------------------------------------------------------------
//
template<class T>
T& Vector<T, 3>::operator [] (int index)
{
	return reinterpret_cast<T*>(this)[index];
}


//------------------------------------------------------------------------------
//
template<class T>
T* Vector<T, 3>::ptr()
{
	return reinterpret_cast<T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
const T* Vector<T, 3>::ptr() const
{
	return reinterpret_cast<const T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3> Vector<T, 3>::operator + (const Vector<T, 3> &rhs) const
{
	return Vector<T, 3>(x+rhs.x, y+rhs.y, z+rhs.z);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3> Vector<T, 3>::operator - (const Vector<T, 3> &rhs) const
{
	return Vector<T, 3>(x-rhs.x, y-rhs.y, z-rhs.z);
}

//------------------------------------------------------------------------------
//
template<class T>
T Vector<T, 3>::operator * (const Vector<T, 3> &rhs) const
{
	return x*rhs.x + y*rhs.y + z*rhs.z;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3> Vector<T, 3>::operator ^ (const Vector<T, 3> &rhs) const
{
	return Vector<T, 3>(y*rhs.z-z*rhs.y, z*rhs.x-x*rhs.z, x*rhs.y-y*rhs.x);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3> Vector<T, 3>::operator * (const T &rhs) const
{
	return Vector<T, 3>(x*rhs, y*rhs, z*rhs);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3> Vector<T, 3>::operator / (const T &rhs) const
{
	return Vector<T, 3>(x/rhs, y/rhs, z/rhs);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3> Vector<T, 3>::operator || (const Vector<T, 3> &rhs) const
{
	return (rhs ^ *this) ^ rhs;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>& Vector<T, 3>::operator += (const Vector<T, 3> &rhs)
{
	x += rhs.x; y += rhs.y; z += rhs.z;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>& Vector<T, 3>::operator -= (const Vector<T, 3> &rhs)
{
	x -= rhs.x; y -= rhs.y; z -= rhs.z;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>& Vector<T, 3>::operator *= (const T &rhs)
{
	x *= rhs; y *= rhs; z *= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>& Vector<T, 3>::operator /= (const T &rhs)
{
	x /= rhs; y /= rhs; z /= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3>& Vector<T, 3>::operator - ()
{
	x = -x, y = -y; z = -z;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
float Vector<T, 3>::length() const
{
	return sqrt(length2());
}

//------------------------------------------------------------------------------
//
template<class T>
float Vector<T, 3>::length2() const
{
	return x*x+y*y+z*z;
}

//------------------------------------------------------------------------------
//
template<class T>
void Vector<T, 3>::scale(float newLength)
{
	*this = scaled(newLength);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3> Vector<T, 3>::transform(Matrix<T, 4, 4> matrix)
{
	Vector<T, 3> res;
	/*std::cout << matrix[0][0] << "; " << matrix[1][0] << "; " << matrix[2][0] << "; " << matrix[3][0] << std::endl;
	std::cout << matrix[0][1] << "; " << matrix[1][1] << "; " << matrix[2][1] << "; " << matrix[3][1] << std::endl;
	std::cout << matrix[0][2] << "; " << matrix[1][2] << "; " << matrix[2][2] << "; " << matrix[3][2] << std::endl;
	std::cout << matrix[0][3] << "; " << matrix[1][3] << "; " << matrix[2][3] << "; " << matrix[3][3] << std::endl;*/

	res.x = x * matrix[0][0] + y * matrix[1][0] + z * matrix[2][0] +
            matrix[3][0];

    res.y = x * matrix[0][1] + y * matrix[1][1] + z * matrix[2][1] +
            matrix[3][1];

    res.z = x * matrix[0][2] + y * matrix[1][2] + z * matrix[2][2] +
            matrix[3][2];

	return res;
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3> Vector<T, 3>::scaled(float newLength) const
{
	float scale = newLength/length();
	return *this * scale;
}

//------------------------------------------------------------------------------
//
template<class T>
void Vector<T, 3>::normalize()
{
	scale(1.0);
}

//------------------------------------------------------------------------------
//
template<class T>
Vector<T, 3> Vector<T, 3>::normalized() const
{
	return scaled(1.0f);
}

//------------------------------------------------------------------------------
//
template<class T>
Matrix<T, 1, 3>& Vector<T, 3>::asTMatrix()
{
	return *(Matrix<T, 1, 3>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
const Matrix<T, 1, 3>& Vector<T, 3>::asTMatrix() const
{
	return *(Matrix<T, 1, 3>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
Matrix<T, 3, 1>& Vector<T, 3>::asMatrix()
{
	return *(Matrix<T, 3, 1>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
const Matrix<T, 3, 1>& Vector<T, 3>::asMatrix() const
{
	return *(Matrix<T, 3, 1>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
void Vector<T, 3>::to4x4Matrix(Matrix<T, 4, 4> *outMatrix)
{
	// avoid depending on Matrix.h
	T* m = reinterpret_cast<T*>(outMatrix);
	
	m[0*4+0] =           1; m[1*4+0] =           0; m[2*4+0] =           0; m[3*4+0] = x;
	m[0*4+1] =           0; m[1*4+1] =           1; m[2*4+1] =           0; m[3*4+1] = y;
	m[0*4+2] =           0; m[1*4+2] =           0; m[2*4+2] =           1; m[3*4+2] = z;
	m[0*4+3] =           0; m[1*4+3] =           0; m[2*4+3] =           0; m[3*4+3] = 1;
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 3>::hasNan() const
{
	return isnan(x) || isnan(y) || isnan(z);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Vector<T, 3>::hasInf() const
{
	return isinf(x) || isinf(y) || isinf(z);
}


//------------------------------------------------------------------------------
//
template<class T>
static inline Vector<T,3> operator * (const T &lhs, const Vector<T,3> &rhs)
{
	return rhs * lhs;
}


//------------------------------------------------------------------------------
//
template<class T>
static inline Vector<T,3> operator * (const Matrix<T, 3, 3> &lhs, const Vector<T,3> &rhs)
{
	return lhs * rhs.asTMatrix();
}

