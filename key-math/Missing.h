#pragma once

#ifdef WIN32

#include <float.h>

#define ZERO 0.0001
#define PI 3.14159265358979f

inline bool isinf(double value)
{
	return !_finite(value);
}

inline bool isnan(double value)
{
	return value != value;
}

#endif
