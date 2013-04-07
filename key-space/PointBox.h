#pragma once

#include <vector>
#include <key-math/Vector3.h>

namespace key {
	namespace space {

		class PointBox {
		public:
			std::vector<Vector3f> points;

			PointBox();
			void add(Vector3f point);
		};

	}
}