#pragma once

#include <map>
#include <memory>

#include <key-common/types.h>
#include <key-math/Vector3.h>

namespace key
{
	namespace space
	{
		struct BbVectorCompare
		{
			inline bool operator() (const Vector<int32_t, 3> & a, const Vector<int32_t, 3> & b)
			{
				return a.x != b.x ? a.x > b.x : (
					a.y != b.y ? a.y > b.y : (
						a.z != b.z ? a.z > b.z : 0
					)
				);
			}
		};

		class PointBox;
		class RandomPointBoxFactory;

		typedef std::map<Vector<int32_t, 3>, std::shared_ptr<PointBox>, BbVectorCompare> RandomBoxMap;
		typedef std::pair<Vector<int32_t, 3>, std::shared_ptr<PointBox>> RandomBoxMapPair;

		class BbLayer
		{
		private:
			std::shared_ptr<RandomPointBoxFactory> randomPointBoxFactory;

			void update();
		public:
			RandomBoxMap randomPointBoxes;
			RandomBoxMap obsoletePointBoxes;

			Vector3f realRelevanceCenter;
			float realRelevanceRadius;
			float realBoxSize;
			Vector<int32_t, 3> unrealRelevanceCenter;
			int32_t unrealRelevanceSize;
			int32_t unrealRelevanceSizeSquared;
			int32_t obsoleteBoxLimit;

			BbLayer(std::shared_ptr<RandomPointBoxFactory> randomPointBoxFactory, Vector3f realRelevanceCenter, float realRelevanceRadius, float realBoxSize);
			virtual ~BbLayer();

			// using these causes colosal precision loss (FYI)
			Vector3f unrealToReal(Vector<int32_t, 3> boxCoordinates);
			Vector<int32_t, 3> realToUnreal(Vector3f boxCoordinates);

			void changeRelevanceCenter(Vector3f newCenter);
		};
	}
}