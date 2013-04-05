#pragma once

#include <key-common/types.h>
#include <key-math/Vector.h>

#include <key-random/PermutationSampler.h>

namespace key 
{
	namespace random 
	{	
		template<class T, int DIMENSIONS, int SAMPLE_SIZE>
		class SimplexNoise { };

		template<class T>
		class SimplexNoise<T, 3, 256>
		{
		private:
			key::random::sampler::PermutationSampler<T, 256> permSampler;
			int32_t mod12permutations[256 * 2];
			// The gradients are the midpoints of the vertices of a cube.
			static const int32_t grad3[12][3];
		public:
			SimplexNoise(int64_t seed);
			T get(const Vector<T, 3> & position) const;
		};

		template<class T>
		class SimplexNoise<T, 2, 256>
		{
		private:
			key::random::sampler::PermutationSampler<T, 256> permSampler;
			int32_t mod12permutations[256 * 2];
			// The gradients are the midpoints of the vertices of a cube.
			static const int32_t grad3[12][3];
		public:
			SimplexNoise(int64_t seed);
			T get(const Vector<T, 2> & position) const;
		};
	}
}

#include <key-random/SimplexNoise.inline.h>