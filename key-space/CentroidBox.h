#pragma once

#include <memory>
#include <vector>

#include <key-common/types.h>
#include <key-math/Vector3.h>

#include <key-space/PointBox.h>

namespace key {
	namespace space {

		class CentroidBox {
		public:
			PointBox noisePoints;
			std::shared_ptr<PointBox> cornerCentroids[8];
			bool cornerCalculated[8];
			PointBox centroids;
			bool centroidsCalculated;

			static const int32_t cornerOffsets[8][3];
			static const int32_t reverseCornerOffsets[8][3];
			static const int32_t centroidCornerPointOffsets[8][3];
			static const int32_t reverseMap[8];

			CentroidBox();
		};

	}
}