#pragma once

#include <key-random/PermutationSampler.h>

#include <math.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

template<class T, int SAMPLE_SIZE>
key::random::sampler::PermutationSampler<T, SAMPLE_SIZE>::PermutationSampler(uint64_t seed)
{
	boost::random::mt19937_64 rng(seed);
	boost::uniform_int<> distribution( 0, SAMPLE_SIZE - 1 );
	boost::variate_generator< boost::mt19937_64&, boost::uniform_int<> > dice(rng, distribution);
	for (int i = 0; i < SAMPLE_SIZE; i++) {
		permutations[i] = dice();
		permutations[i + SAMPLE_SIZE] = permutations[i];
	}
}

/*template<class T, class GradientT, int DIMENSIONS, int SAMPLE_SIZE>
T key::random::sampler::PermutationSampler<T, GradientT, DIMENSIONS, SAMPLE_SIZE>::cossinePolynomialFade(T t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}*/
