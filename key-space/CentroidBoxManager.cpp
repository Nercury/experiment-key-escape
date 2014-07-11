#include "CentroidBoxManager.h"

#include <key-math/Quaternion.h>
#include "PointBox.h"

using namespace std;
using namespace key::space;

CentroidBoxManager::CentroidBoxManager(uint64_t seed, int32_t subdivisionCount, float scale) : noise(seed), subdivisionCount(subdivisionCount) {
	Quaternionf qHeading(Vector3f(0.71f, 0.31f, 0.11f).normalized(), 0.1f);
	qHeading.to4x4Matrix(&this->noiseTransform);
	this->noiseTransform *= scale;
}

void CentroidBoxManager::addRandomPointsToBox(PointBox & box, Vector3f boxPosition, float boxSize) {
	
	float subdivisionHalf = boxSize / (float)(subdivisionCount * 2);
	float subdivisionSize = subdivisionHalf * 2;

	Vector3f subPosition;
	Vector3f samplePoint;
	float sample;

	int32_t x, y, z;

	for (x = 0; x < subdivisionCount; x++) {
		subPosition.x = subdivisionHalf + subdivisionSize * x;
		for (y = 0; y < subdivisionCount; y++) {
			subPosition.y = subdivisionHalf + subdivisionSize * y;
			for (z = 0; z < subdivisionCount; z++) {
				subPosition.z = subdivisionHalf + subdivisionSize * z;

				samplePoint = (boxPosition + subPosition).transform(noiseTransform);
				sample = noise.get(samplePoint);
				if (sample > 0.9f) {
					box.add(subPosition);
				}
			}
		}
	}
}