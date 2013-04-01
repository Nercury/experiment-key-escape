#pragma once

#include <key-common/types.h>
#include <key-math/Vector.h>

namespace key 
{
	namespace random 
	{	
		namespace gradient {

			template<class T, int DIMENSIONS, int SAMPLE_SIZE>
			class GradientVectorSampler
			{
			public:
				T grad(const int16_t hash, const T point[]) const;
			};

			template<class T>
			class GradientVectorSampler<T, 3, 256>
			{
			public:
				T grad(const int16_t hash, const T point[]) const;
			};

		}
	}
}

#include <key-random/GradientVectorSampler.inline.h>