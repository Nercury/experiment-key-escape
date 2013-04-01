#pragma once

#include <key-random/FlatNoise.h>

template<class T, int DIMENSIONS, int SAMPLE_SIZE>
key::random::FlatNoise<T, DIMENSIONS, SAMPLE_SIZE>::FlatNoise(uint64_t seed)
	: permSampler(seed)
{

}

template<class T, int DIMENSIONS, int SAMPLE_SIZE>
T key::random::FlatNoise<T, DIMENSIONS, SAMPLE_SIZE>::get(const Vector<T, DIMENSIONS> & position) const
{
	T lowerWrapPoint[DIMENSIONS];
	for (int i = 0; i < DIMENSIONS; i++) {
		lowerWrapPoint[i] = floorf(position[i]);
	}
	
	int16_t sampleWrapPoint[DIMENSIONS]; // X
	for (int i = 0; i < DIMENSIONS; i++) {
		sampleWrapPoint[i] = (int32_t)lowerWrapPoint[i] % SAMPLE_SIZE;
	}

	auto hash = permSampler.permutations[sampleWrapPoint[0]];
	for (int i = 1; i < DIMENSIONS; i++) {
		hash = permSampler.permutations[hash + sampleWrapPoint[i]];
	}
	return hash / (T)SAMPLE_SIZE;
}

/*template<class T, class GradientT, int DIMENSIONS, int SAMPLE_SIZE>
T key::random::sampler::PermutationSampler<T, GradientT, DIMENSIONS, SAMPLE_SIZE>::sample(const Vector<T, DIMENSIONS> & position) const
{
	

	//auto positionInWrapCube = position - lowerWrapPoint;

	
	//Vector<T, DIMENSIONS> fadeP;
	//for (int i = 0; i < DIMENSIONS; i++) {
	//	fadeP[i] = cossinePolynomialFade(p[i]);
	//}
	
	
}*/