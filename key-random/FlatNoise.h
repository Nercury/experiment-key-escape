#pragma once

#include <key-common/types.h>
#include <key-math/Vector.h>

#include <key-random/PermutationSampler.h>

namespace key 
{
	namespace random 
	{	

		template<class T, int DIMENSIONS, int SAMPLE_SIZE>
		class FlatNoise
		{
		private:
			key::random::sampler::PermutationSampler<T, SAMPLE_SIZE> permSampler;
		public:
			FlatNoise(uint64_t seed);

			T get(const Vector<T, DIMENSIONS> & position) const;
		};

	}
}

#include <key-random/FlatNoise.inline.h>