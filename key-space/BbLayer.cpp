#include "BbLayer.h"

#include <iostream>

#include "RandomPointBoxFactory.h"
#include "PointBox.h"

using namespace key::space;
using namespace std;

BbLayer::BbLayer(std::shared_ptr<RandomPointBoxFactory> randomPointBoxFactory, Vector3f realRelevanceCenter, float realRelevanceRadius, float realBoxSize)
	: randomPointBoxFactory(randomPointBoxFactory), 
		realRelevanceCenter(realRelevanceCenter), 
		realRelevanceRadius(realRelevanceRadius), 
		realBoxSize(realBoxSize) 
{
	unrealRelevanceSize = (int32_t)ceilf(realRelevanceRadius / (float)realBoxSize);
	unrealRelevanceSizeSquared = unrealRelevanceSize * unrealRelevanceSize;
	obsoleteBoxLimit = (unrealRelevanceSize * unrealRelevanceSize) * 4 * 11;
	update();
}

BbLayer::~BbLayer() {

}

void BbLayer::changeRelevanceCenter(Vector3f newCenter) {
	if ((newCenter - realRelevanceCenter).length() >= realBoxSize) {
		realRelevanceCenter = newCenter;
		update();
	}
}

Vector3f BbLayer::unrealToReal(Vector<int32_t, 3> boxCoordinates) {
	return Vector3f((float)boxCoordinates[0] * realBoxSize, (float)boxCoordinates[1] * realBoxSize, (float)boxCoordinates[2] * realBoxSize);
}

Vector<int32_t, 3> BbLayer::realToUnreal(Vector3f boxCoordinates) {
	return Vector<int32_t, 3>((int32_t)(boxCoordinates[0] / realBoxSize), (int32_t)(boxCoordinates[1] / realBoxSize), (int32_t)(boxCoordinates[2] / realBoxSize));
}

void BbLayer::update() {
	Vector<int32_t, 3> newUnrealRelevanceCenter = realToUnreal(realRelevanceCenter);
	if (this->randomPointBoxes.size() > 0 && newUnrealRelevanceCenter == unrealRelevanceCenter) {
		return;
	}

	unrealRelevanceCenter = newUnrealRelevanceCenter;

	// remove existing cubes if out of bounds

	for (auto it = randomPointBoxes.cbegin(); it != randomPointBoxes.cend(); ) {
		auto cubePos = it->first;
		Vector3f diffFromCenter(cubePos.x + 0.5f - unrealRelevanceCenter.x, cubePos.y + 0.5f - unrealRelevanceCenter.y, cubePos.z + 0.5f - unrealRelevanceCenter.z);
		if (diffFromCenter.length2() > unrealRelevanceSizeSquared - 0.5f) {
			this->obsoletePointBoxes.insert(RandomBoxMapPair(
				cubePos, 
				it->second
			));
			randomPointBoxes.erase(it++);
		} else {
			++it;
		}
	}
	
	// create new in-bounds cubes

	cout << "update location to " << unrealRelevanceCenter.x << " " << unrealRelevanceCenter.y << " " << unrealRelevanceCenter.z << endl;

	for (int32_t x = unrealRelevanceCenter.x - unrealRelevanceSize; x < unrealRelevanceCenter.x + unrealRelevanceSize; x++) {
		for (int32_t y = unrealRelevanceCenter.y - unrealRelevanceSize; y < unrealRelevanceCenter.y + unrealRelevanceSize; y++) {
			for (int32_t z = unrealRelevanceCenter.z - unrealRelevanceSize; z < unrealRelevanceCenter.z + unrealRelevanceSize; z++) {
				Vector3f diffFromCenter(x + 0.5f - unrealRelevanceCenter.x, y + 0.5f - unrealRelevanceCenter.y, z + 0.5f - unrealRelevanceCenter.z);
				if (diffFromCenter.length2() <= unrealRelevanceSizeSquared - 0.5f) {
					Vector<int32_t, 3> cubePos(x, y, z);
					auto existingCubeIt = this->randomPointBoxes.find(cubePos);
					if (existingCubeIt == this->randomPointBoxes.end()) {
						existingCubeIt = this->obsoletePointBoxes.find(cubePos);
						if (existingCubeIt == this->obsoletePointBoxes.end()) {
							this->randomPointBoxes.insert(RandomBoxMapPair(
								cubePos, 
								this->randomPointBoxFactory->makeBoxWithRandomPoints(
									unrealToReal(cubePos), realBoxSize
								)
							));
						} else {
							this->randomPointBoxes.insert(RandomBoxMapPair(
								cubePos, 
								existingCubeIt->second
							));
							this->obsoletePointBoxes.erase(existingCubeIt);
						}
					}
				}
			}
		}
	}

	if ( obsoletePointBoxes.size() > obsoleteBoxLimit) {
		obsoletePointBoxes.clear();
	}

	cout << "obsolete cube count " << obsoletePointBoxes.size() << endl;
	cout << "bb cube count " << randomPointBoxes.size() << endl;
	
}