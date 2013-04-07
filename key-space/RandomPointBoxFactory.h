#pragma once

#include <vector>

#include <key-math/Vector3.h>
#include <key-math/Matrix.h>

#include <key-random/SimplexNoise.h>

namespace key {
	namespace space {

		class PointBox;

		class RandomPointBoxFactory {
		public:
			key::random::SimplexNoise<float, 3, 256> noise;
			Matrix4f noiseTransform;
			int32_t subdivisionCount;

			RandomPointBoxFactory(uint64_t seed, int32_t subdivisionCount, float scale);
			void addRandomPointsToBox(PointBox & box, Vector3f boxPosition, float boxSize);
		};

	}
}