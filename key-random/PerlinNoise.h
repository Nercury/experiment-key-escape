#pragma once

#include <key-common/types.h>
#include <key-math/Vector.h>

#include <key-random/PermutationSampler.h>
#include <key-random/GradientVectorSampler.h>

namespace key 
{
	namespace random 
	{	
		namespace util {
			template<class T, class GradSamplerT, int DIMENSIONS, int AXIS>
			class PerlinNoiseDims {
			private:
				PerlinNoiseDims<T, GradSamplerT, DIMENSIONS, AXIS - 1> previousDim;
			public:
				T finalLerp(const GradSamplerT & gradSampler, T point[], const int16_t hashes[]) const;
				void floorAtoB(const T a[], T b[]) const;
				void setWrapPoint(const T p[], int16_t sampleWrapPoint[], const int16_t sampleSize) const;
				void setPtoPositionMinusP(T p[], const T position[]) const;
			};

			template<class T, class GradSamplerT, int DIMENSIONS>
			class PerlinNoiseDims<T, GradSamplerT, DIMENSIONS, 0> {
			public:
				T finalLerp(const GradSamplerT & gradSampler, T point[], const int16_t hashes[]) const;
				void floorAtoB(const T a[], T b[]) const;
				void setWrapPoint(const T p[], int16_t sampleWrapPoint[], const int16_t sampleSize) const;
				void setPtoPositionMinusP(T p[], const T position[]) const;
			};
		}

		template<class T, int DIMENSIONS, int SAMPLE_SIZE>
		class PerlinNoise
		{
		private:
			key::random::sampler::PermutationSampler<T, SAMPLE_SIZE> permSampler;
			gradient::GradientVectorSampler<T, DIMENSIONS, SAMPLE_SIZE> gradSampler;
			util::PerlinNoiseDims<
				T, 
				gradient::GradientVectorSampler<T, DIMENSIONS, SAMPLE_SIZE>, 
				DIMENSIONS,
				DIMENSIONS - 1
			> dims;
		public:
			PerlinNoise(uint64_t seed);

			T get(const Vector<T, DIMENSIONS> & position) const;
		};

	}
}

#include <key-random/PerlinNoise.inline.h>