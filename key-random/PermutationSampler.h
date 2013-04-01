#pragma once

#include <key-common/types.h>
#include <key-math/Vector.h>

namespace key 
{
	namespace random 
	{	
		namespace sampler {
			template<class T, int SAMPLE_SIZE>
			class PermutationSampler
			{
			public:
				int16_t permutations[SAMPLE_SIZE * 2];

				PermutationSampler(uint64_t seed);
			};
		}
	}
}

#include <key-random/PermutationSampler.inline.h>