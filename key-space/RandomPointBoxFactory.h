#pragma once

#include <memory>
#include <vector>

#include <key-math/Vector3.h>

#include <key-random/SimplexNoise.h>

namespace key {
	namespace space {

		class PointBox;

		class RandomPointBoxFactory {
		public:
			key::random::SimplexNoise<float, 3, 256> noise;

			RandomPointBoxFactory(uint64_t seed);
			std::shared_ptr<PointBox> makeBoxWithRandomPoints(Vector3f boxPosition, float boxSize);
		};

	}
}