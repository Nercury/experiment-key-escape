#pragma once

#include <key-random/util.h>

template<class T>
inline T key::random::util::cossinePolynomialFade(const T t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

template<class T>
inline T key::random::util::lerp(const T t, const T a, const T b) { return a + t * (b - a); }

template<>
inline int32_t key::random::util::floor<float>(const float value) {
	return value > 0 ? (int32_t) value : (int32_t) value - 1;
}

template<>
inline int32_t key::random::util::floor<double>(const double value) {
	return value > 0 ? (int32_t) value : (int32_t) value - 1;
}

template<class T, int SAMPLE_SIZE>
int16_t key::random::util::wrapInRange(T number) {
	return key::random::util::wrapInteger((int32_t)number, SAMPLE_SIZE);
}

template<>
inline int16_t key::random::util::wrapInRange<float, 256>(float number) {
	return (int32_t)number & 255;
}

template<>
inline int16_t key::random::util::wrapInRange<double, 256>(double number) {
	return (int64_t)number & 255;
}

template<class IntT>
int16_t key::random::util::wrapInteger(IntT kX, int16_t const kUpperBound)
{
	int16_t range_size = kUpperBound;
	if (kX < 0)
		kX += range_size * ((-kX) / range_size);
	return kX % range_size;
}

template<class T, int INDEX>
void key::random::util::setAllArrayTo(T a[], const T value) {
	key::random::util::setAllArrayTo<T, INDEX - 1>(a, value);
	a[INDEX] = value;
}

template<>
inline void key::random::util::setAllArrayTo<float, 0>(float a[], const float value) {
	a[0] = value;
}

template<class T, int INDEX>
void key::random::util::copyArrayTo(const T a[], T b[]) {
	key::random::util::copyArrayTo<T, INDEX - 1>(a, b);
	b[INDEX] = a[INDEX];
}

template<>
inline void key::random::util::copyArrayTo<float, 0>(const float a[], float b[]) {
	b[0] = a[0];
}

template<class T, int INDEX>
void key::random::util::floorAtoB(const T a[], int32_t b[]) {
	b[INDEX] = util::floor<T>(a[INDEX]);
}

template<>
inline void key::random::util::floorAtoB<float, 0>(const float a[], int32_t b[]) {
	b[0] = util::floor<float>(a[0]);
}

template<class T>
inline T key::random::util::vdot2( const int32_t g[], const T x, const T y ) 
{ 
	return g[0]*x + g[1]*y; 
}

template<class T>
inline T key::random::util::vdot3( const int32_t g[], const T x, const T y, const T z ) 
{ 
	return g[0]*x + g[1]*y + g[2]*z; 
}

template<class T>
inline T key::random::util::vdot4( const int32_t g[], const T x, const T y, const T z, const T w ) 
{ 
	return g[0]*x + g[1]*y + g[2]*z + g[3]*w; 
}