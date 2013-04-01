#pragma once

#include "Vector.h"

enum PLANE {
	LEFT_PLANE, RIGHT_PLANE,
	BOTTOM_PLANE, TOP_PLANE,
	NEAR_PLANE, FAR_PLANE
};

class Plane {
public:
	Plane() { };
	Plane(float _a, float _b, float _c, float _d) : a(_a), b(_b), c(_c), d(_d) { };

	void Plane::fromPoints(const Vector3f &_p0, const Vector3f &_p1, const Vector3f &_p2)
	{
		Vector3f v0(_p0 - _p1);
		Vector3f v1(_p2 - _p1);
		Vector3f n = v1 ^ v0;//v1 | v0;
		n.normalize();
		a = n.x;
		b = n.y;
		c = n.z;
		d = -(_p0.x * a + _p0.y * b + _p0.z * c);
	};

	void Plane::fromPointAndNormal(const Vector3f &_p, const Vector3f &_n)
	{
		Vector3f nn = _n;
		nn.normalize();
		a = nn.x;
		b = nn.y;
		c = nn.z;
		d = -(_p.x * a + _p.y * b + _p.z * c);
	};

	inline float dot(const Vector3f &_p) const
	{
		return a * _p.x + b * _p.y + c * _p.z;
	}

	inline float dist(const Vector3f &_p) const
	{
		return a * _p.x + b * _p.y + c * _p.z + d;
	}

	inline Vector3f reflect(const Vector3f &_vec)
	{
		float d = dist(_vec);
		return _vec + Vector3f(-a, -b, -c) * 2 * d;
	}

	inline Vector3f project(const Vector3f &_p)
	{
		float h = dist(_p);
		return Vector3f(_p.x - a * h,
					 _p.y - b * h,
					 _p.z - c * h);
	}

	inline bool isOnPlane(const Vector3f &_p, float _threshold = 0.001f)
	{
		float d = dist(_p);
		if (d < _threshold && d > -_threshold)
			return true;
		return false;
	}

	// Calcul the intersection between this plane and a line
	// If the plane and the line are parallel, OZFALSE is returned
	inline bool intersectWithLine(const Vector3f &_p0, const Vector3f &_p1, float &_t)
	{
		Vector3f dir = _p1 - _p0;
		float div = dot(dir);
		if (div == 0)
			return false;

		_t = -dist(_p0) / div;
		return true;
	}

	float a, b, c, d;
};