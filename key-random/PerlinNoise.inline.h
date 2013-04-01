#pragma once

#include <key-random/PerlinNoise.h>
#include <key-random/DimPow.h>
#include <key-random/PerlinUtils.h>

#include <iostream>

template<class T, class GradSamplerT, int DIMENSIONS, int AXIS>
T key::random::util::PerlinNoiseDims<T, GradSamplerT, DIMENSIONS, AXIS>::finalLerp(const GradSamplerT & gradSampler, T point[], const int16_t hashes[]) const {
	point[AXIS] -= 1;
	auto b = previousDim.finalLerp(gradSampler, point, &hashes[util::DimPow<2, AXIS>::result]);
	point[AXIS] += 1;
	return util::lerp(
		util::cossinePolynomialFade(point[AXIS]), 
		previousDim.finalLerp(gradSampler, point, hashes), 
		b
	);
}

template<class T, class GradSamplerT, int DIMENSIONS>
inline T key::random::util::PerlinNoiseDims<T, GradSamplerT, DIMENSIONS, 0>::finalLerp(const GradSamplerT & gradSampler, T point[], const int16_t hashes[]) const {
	point[0] -= 1;
	auto b = gradSampler.grad(hashes[1], point);
	point[0] += 1;
	return util::lerp(
		util::cossinePolynomialFade(point[0]),
		gradSampler.grad(hashes[0], point),
		b
	);
}

template<class T, class GradSamplerT, int DIMENSIONS, int AXIS>
void key::random::util::PerlinNoiseDims<T, GradSamplerT, DIMENSIONS, AXIS>::floorAtoB(const T a[], T b[]) const {
	previousDim.floorAtoB(a, b);
	b[AXIS] = util::floor(a[AXIS]);
}

template<class T, class GradSamplerT, int DIMENSIONS>
void key::random::util::PerlinNoiseDims<T, GradSamplerT, DIMENSIONS, 0>::floorAtoB(const T a[], T b[]) const {
	b[0] = util::floor(a[0]);
}

template<class T, class GradSamplerT, int DIMENSIONS, int AXIS>
void key::random::util::PerlinNoiseDims<T, GradSamplerT, DIMENSIONS, AXIS>::setWrapPoint(const T p[], int16_t sampleWrapPoint[], const int16_t sampleSize) const {
	previousDim.setWrapPoint(p, sampleWrapPoint, sampleSize);
	sampleWrapPoint[AXIS] = (int32_t)p[AXIS] & (sampleSize - 1);
}

template<class T, class GradSamplerT, int DIMENSIONS>
void key::random::util::PerlinNoiseDims<T, GradSamplerT, DIMENSIONS, 0>::setWrapPoint(const T p[], int16_t sampleWrapPoint[], const int16_t sampleSize) const {
	sampleWrapPoint[0] = (int32_t)p[0] & (sampleSize - 1);
}

template<class T, class GradSamplerT, int DIMENSIONS, int AXIS>
void key::random::util::PerlinNoiseDims<T, GradSamplerT, DIMENSIONS, AXIS>::setPtoPositionMinusP(T p[], const T position[]) const {
	previousDim.setPtoPositionMinusP(p, position);
	p[AXIS] = position[AXIS] - p[AXIS];
}

template<class T, class GradSamplerT, int DIMENSIONS>
void key::random::util::PerlinNoiseDims<T, GradSamplerT, DIMENSIONS, 0>::setPtoPositionMinusP(T p[], const T position[]) const {
	p[0] = position[0] - p[0];
}

template<class T, int DIMENSIONS, int SAMPLE_SIZE>
key::random::PerlinNoise<T, DIMENSIONS, SAMPLE_SIZE>::PerlinNoise(uint64_t seed)
	: permSampler(seed)
{

}

static double grad(int hash, double x, double y, double z) {
    int h = hash & 15;                      // CONVERT LO 4 BITS OF HASH CODE
    double u = h<8 ? x : y,                 // INTO 12 GRADIENT DIRECTIONS.
            v = h<4 ? y : h==12||h==14 ? x : z;
    return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}

template<class T, int DIMENSIONS, int SAMPLE_SIZE>
T key::random::PerlinNoise<T, DIMENSIONS, SAMPLE_SIZE>::get(const Vector<T, DIMENSIONS> & position) const
{
	/*int X = (int)floorf(position[0]) & 255;                  // FIND UNIT CUBE THAT
    int Y = (int)floorf(position[1]) & 255;                  // CONTAINS POINT.
    int Z = (int)floorf(position[2]) & 255;
      float x = position[0] - floorf(position[0]);                                // FIND RELATIVE X,Y,Z
      float y = position[1] - floorf(position[1]);                                // OF POINT IN CUBE.
      float z = position[2] - floorf(position[2]);
	  float u = util::cossinePolynomialFade(x),                                // COMPUTE FADE CURVES
             v = util::cossinePolynomialFade(y),                                // FOR EACH OF X,Y,Z.
             w = util::cossinePolynomialFade(z);
	  int16_t A = permSampler.permutations[X  ]+Y, AA = permSampler.permutations[A]+Z, AB = permSampler.permutations[A+1]+Z,      // HASH COORDINATES OF
          B = permSampler.permutations[X+1]+Y, BA = permSampler.permutations[B]+Z, BB = permSampler.permutations[B+1]+Z;      // THE 8 CUBE CORNERS,

	  return util::lerp<T>(w, util::lerp<T>(v, util::lerp<T>(u, grad(permSampler.permutations[AA  ], x  , y  , z   ),  // AND ADD
                                     grad(permSampler.permutations[BA  ], x-1, y  , z   )), // BLENDED
                             util::lerp<T>(u, grad(permSampler.permutations[AB  ], x  , y-1, z   ),  // RESULTS
                                     grad(permSampler.permutations[BB  ], x-1, y-1, z   ))),// FROM  8
                     util::lerp<T>(v, util::lerp<T>(u, grad(permSampler.permutations[AA+1], x  , y  , z-1 ),  // CORNERS
                                     grad(permSampler.permutations[BA+1], x-1, y  , z-1 )), // OF CUBE
                             util::lerp<T>(u, grad(permSampler.permutations[AB+1], x  , y-1, z-1 ),
                                     grad(permSampler.permutations[BB+1], x-1, y-1, z-1 ))));*/
	
	// p stores floored point of our position
	T p[DIMENSIONS];
	dims.floorAtoB(position.ptr(), p);
	
	// sample point is a point in our cube which is the size of our SAMPLE_SIZE
	int16_t sampleWrapPoint[DIMENSIONS];
	dims.setWrapPoint(p, sampleWrapPoint, SAMPLE_SIZE);

	// generate hash values (A, B, AA, BA ... etc) for dimensions - 1
	int16_t hashes[util::DimPow<2, DIMENSIONS>::result];
	util::recursive_hash_gen<DIMENSIONS - 1>(hashes, sampleWrapPoint, permSampler.permutations);

	// now p can be used as source for fade curves
	dims.setPtoPositionMinusP(p, position.ptr());

	// use some template metaprogramming to recursivelly return blended positions for any dimensions
	return dims.finalLerp(gradSampler, p, hashes);
}