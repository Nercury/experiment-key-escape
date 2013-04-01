#pragma once

#include <key-random/PerlinUtils.h>

template<class T>
inline T key::random::util::cossinePolynomialFade(const T t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

template<class T>
inline T key::random::util::lerp(const T t, const T a, const T b) { return a + t * (b - a); }

template<>
inline float key::random::util::floor<float>(const float value) {
	return floorf(value);
}

template<>
inline double key::random::util::floor<double>(const double value) {
	return floor(value);
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

/*
int A = p[X  ]+Y, AA = p[A]+Z, AB = p[A+1]+Z,      // HASH COORDINATES OF
    B = p[X+1]+Y, BA = p[B]+Z, BB = p[B+1]+Z;      // THE 8 CUBE CORNERS,
*/

template<int INDEX>
void key::random::util::recursive_hash_gen_assign(int16_t hashesA[], int16_t hashesB[], const int16_t sampleWrapPoint, const int16_t permutations[]) {
	key::random::util::recursive_hash_gen_assign<INDEX - 1>(hashesA, hashesB, sampleWrapPoint, permutations);
	hashesA[INDEX] += sampleWrapPoint; // add new axis to all
	hashesB[INDEX] = permutations[hashesA[INDEX] + 1]; // second half has axis + 1 permutation
	hashesA[INDEX] = permutations[hashesA[INDEX]]; // first half has no + 1
}

template<>
inline void key::random::util::recursive_hash_gen_assign<0>(int16_t hashesA[], int16_t hashesB[], const int16_t sampleWrapPoint, const int16_t permutations[]) {
	hashesA[0] += sampleWrapPoint; // add new axis to all
	hashesB[0] = permutations[hashesA[0] + 1]; // second half has axis + 1 permutation
	hashesA[0] = permutations[hashesA[0]]; // first half has no + 1
}

template<int AXIS>
void key::random::util::recursive_hash_gen(int16_t hashes[], const int16_t sampleWrapPoint[], const int16_t permutations[])
{
	key::random::util::recursive_hash_gen<AXIS - 1>(hashes, sampleWrapPoint, permutations);
	key::random::util::recursive_hash_gen_assign<util::DimPow<2, AXIS>::result - 1>(hashes, &hashes[util::DimPow<2, AXIS>::result], sampleWrapPoint[AXIS], permutations);
}

template<>
inline void key::random::util::recursive_hash_gen<0>(int16_t hashes[], const int16_t sampleWrapPoint[], const int16_t permutations[])
{
	hashes[0] = sampleWrapPoint[0];
	hashes[1] = permutations[hashes[0] + 1];
	hashes[0] = permutations[hashes[0]];
}