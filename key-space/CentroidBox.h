#pragma once

#include <vector>
#include <key-math/Vector3.h>

#include <key-space/PointBox.h>

namespace key {
	namespace space {

		class CentroidBox {
		public:
			PointBox noisePoints;
			PointBox cornerCentroids[8];
			bool cornerCalculated[8];
			PointBox centroids;
			bool centroidsCalculated;

			CentroidBox();
		};

	}
}