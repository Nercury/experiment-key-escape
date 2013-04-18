#pragma once

#include <memory>
#include <vector>

#include <key-common/types.h>
#include <key-math/Vector3.h>

#include <key-space/PointBox.h>

namespace key {
	namespace space {
		
		// [2013.03.24 15:20:06] Nerijus: I will try to randomly generate some cubes to make myself happy

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