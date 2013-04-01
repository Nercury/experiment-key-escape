#pragma once

template<class T, int S> class Vector;
template<class T, int W, int H> class Matrix;

template<class T>
class Quaternion
{
public:
	Quaternion();
	Quaternion(T inW, T inX, T inY, T inZ);
	Quaternion(const Vector<T,3> &axis, T angle);
	Quaternion(const Matrix<T, 1, 4> &rhs);
	Quaternion& operator = (const Matrix<T, 1, 4> &rhs);
	Quaternion(const Quaternion &rhs);
	Quaternion& operator = (const Quaternion &rhs);
	bool operator == (const Quaternion &rhs) const;
	bool operator != (const Quaternion &rhs) const;
	bool operator < (const Quaternion &rhs) const;
	bool operator <= (const Quaternion &rhs) const;
	bool operator > (const Quaternion &rhs) const;
	bool operator >= (const Quaternion &rhs) const;
	const T& operator [] (int index) const;
	operator T*();
	operator const T*() const;
	Quaternion operator + (const Quaternion &rhs) const;
	Quaternion operator - (const Quaternion &rhs) const;
	Quaternion operator * (const Quaternion &rhs) const;
public:
	
	Quaternion operator * (const T &rhs) const;
	Quaternion operator / (const T &rhs) const;
	Quaternion& operator += (const Quaternion &rhs);
	Quaternion& operator -= (const Quaternion &rhs);
	Quaternion& operator *= (const T &rhs);
	Quaternion& operator /= (const T &rhs);
	Quaternion& operator - ();
	float length();
	float length2();
	Quaternion& scale(float newLength);
	Quaternion& normalize();
	Quaternion conjugate();
	Quaternion unitInverse();	//	assumes we have a unit quaternion
	Quaternion inverse();
	//! returns the euler angles from a rotation quaternion
	Vector<T, 3> euler_angles() const
	{
		T sqw = w*w;    
		T sqx = x*x;    
		T sqy = y*y;    
		T sqz = z*z;    

		Vector<T, 3> euler;
		euler.x = atan2f(2.f * (x*y + z*w), sqx - sqy - sqz + sqw);    		
		euler.y = asinf(-2.f * (x*z - y*w));
		euler.z = atan2f(2.f * (y*z + x*w), -sqx - sqy + sqz + sqw);    
		return euler;
	}
	//! returns the axis and angle of this unit quaternion
	void to_axis_angle(Vector<T, 3> &axis, T &angle) const
	{
		angle = acosf(w);

		// pre-compute to save time
		T sinf_theta_inv = 1.0/sinf(angle);

		// now the vector
		axis.x = x*sinf_theta_inv;
		axis.y = y*sinf_theta_inv;
		axis.z = z*sinf_theta_inv;

		// multiply by 2
		angle*=2;
	}

	//! returns the logarithm of a quaternion = v*a where q = [cos(a),v*sin(a)]
	Quaternion<T> log() const
	{
		T a = (T)acos(w);
		T sina = (T)sin(a);
		Quaternion<T> ret;

		ret.w = 0;
		if (sina > 0)
		{
			ret.x = a*x/sina;
			ret.y = a*y/sina;
			ret.z = a*z/sina;
		} else {
			ret.x= ret.y= ret.z= 0;
		}
		return ret;
	}

	//! returns e^quaternion = exp(v*a) = [cos(a),vsin(a)]
	Quaternion<T> exp() const
	{
		T a = (T)length();
		T sina = (T)sin(a);
		T cosa = (T)cos(a);
		Quaternion<T> ret;

		ret.w = cosa;
		if (a > 0)
		{
			ret.x = sina * x / a;
			ret.y = sina * y / a;
			ret.z = sina * z / a;
		} else {
			ret.x = ret.y = ret.z = 0;
		}
		return ret;
	}


	//! computes the dot product of 2 quaternions
	static inline T dot(const Quaternion<T> &q1, const Quaternion<T> &q2) 
	{ return Vector<T, 3>(q1.x, q1.y, q1.z) * Vector<T, 3>(q2.x, q2.y, q2.z) + q1.w*q2.w; }

	//! linear quaternion interpolation
	static inline Quaternion<T> lerp(const Quaternion<T> &q1, const Quaternion<T> &q2, T t) 
	{ return (q1*(1-t) + q2*t).normalize(); }

	//! spherical linear interpolation
	static Quaternion<T> slerp(const Quaternion<T> &q1, const Quaternion<T> &q2, T t) 
	{
		Quaternion<T> q3;
		T dot = Quaternion<T>::dot(q1, q2);

		/*	dot = cos(theta)
			if (dot < 0), q1 and q2 are more than 90 degrees apart,
			so we can invert one to reduce spinning	*/
		if (dot < 0)
		{
			dot = -dot;
			q3 = -q2;
		} else q3 = q2;
		
		if (dot < 0.95f)
		{
			T angle = acosf(dot);
			return (q1*sinf(angle*(1-t)) + q3*sinf(angle*t))/sinf(angle);
		} else // if the angle is small, use linear interpolation								
			return lerp(q1,q3,t);
	}

	//! This version of slerp, used by squad, does not check for theta > 90.
	static Quaternion<T> slerpNoInvert(const Quaternion<T> &q1, const Quaternion<T> &q2, T t) 
	{
		T dot = Quaternion<T>::dot(q1, q2);

		if (dot > -0.95f && dot < 0.95f)
		{
			T angle = acosf(dot);			
			return (q1*sinf(angle*(1-t)) + q2*sinf(angle*t))/sinf(angle);
		} else  // if the angle is small, use linear interpolation								
			return lerp(q1,q2,t);			
	}

	//! spherical cubic interpolation
	static Quaternion<T> squad(const Quaternion<T> &q1,const Quaternion<T> &q2,const Quaternion<T> &a,const Quaternion<T> &b,T t)
	{
		Quaternion<T> c= slerpNoInvert(q1,q2,t),
			       d= slerpNoInvert(a,b,t);		
		return slerpNoInvert(c,d,2*t*(1-t));
	}

	//! Shoemake-Bezier interpolation using De Castlejau algorithm
	static Quaternion<T> bezier(const Quaternion<T> &q1,const Quaternion<T> &q2,const Quaternion<T> &a,const Quaternion<T> &b,T t)
	{
		// level 1
		Quaternion<T> q11= slerpNoInvert(q1,a,t),
				q12= slerpNoInvert(a,b,t),
				q13= slerpNoInvert(b,q2,t);		
		// level 2 and 3
		return slerpNoInvert(slerpNoInvert(q11,q12,t), slerpNoInvert(q12,q13,t), t);
	}

	//! Given 3 quaternions, qn-1,qn and qn+1, calculate a control point to be used in spline interpolation
	static Quaternion<T> spline(const Quaternion<T> &qnm1,const Quaternion<T> &qn,const Quaternion<T> &qnp1)
	{
		Quaternion<T> qni(-Vector<T, 3>(qn.x, qn.y, qn.z), qn.w);	
		return qn * (( (qni*qnm1).log()+(qni*qnp1).log() )/-4).exp();
	}

	//! converts from a normalized axis - angle pair rotation to a quaternion
	static inline Quaternion<T> from_axis_angle(const Vector<T, 3> &axis, T angle)
	{ return Quaternion<T>(cosf(angle/2), axis*sinf(angle/2)); }


	void to4x4Matrix(Matrix<T, 4, 4> *outMatrix);
	void to3x3Matrix(Matrix<T, 3, 3> *outMatrix);

public:
	T w;
	T x;
	T y;
	T z;
};


template<class T>
static inline Quaternion<T> operator * (const T &lhs, const Quaternion<T> &rhs);

typedef Quaternion<float> 	Quaternionf;
typedef Quaternion<double>	Quaterniond;

//==============================================================================
//	INLINED CODE
//==============================================================================
#include "Quaternion.inline.h"

