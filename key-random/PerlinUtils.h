#pragma once

#include <key-common/types.h>
#include <key-math/Vector.h>

#include <key-random/GradientVectorSampler.h>

namespace key 
{
	namespace random 
	{	
		namespace util {

			template<class IntT>
			int16_t wrapInteger(IntT kX, int16_t const kUpperBound);

			template<class T, int SAMPLE_SIZE>
			int16_t wrapInRange(T number);

			template<int INDEX>
			void recursive_hash_gen_assign(int16_t hashesA[], int16_t hashesB[], const int16_t sampleWrapPoint, const int16_t permutations[]);

			template<int AXIS>
			void recursive_hash_gen(int16_t hashes[], const int16_t sampleWrapPoint[], const int16_t permutations[]);

			template<class T>
			T cossinePolynomialFade(const T t);

			template<class T>
			T lerp(const T t, const T a, const T b);

			template<class T>
			T floor(const T value);
		}
	}
}

#include <key-random/PerlinUtils.inline.h>