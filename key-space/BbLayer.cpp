#include "BbLayer.h"

#include <iostream>

#include "RandomPointBoxFactory.h"
#include "PointBox.h"
#include "CentroidBox.h"

using namespace key::space;
using namespace std;

BbLayer::BbLayer(std::shared_ptr<RandomPointBoxFactory> randomPointBoxFactory, Vector3f realRelevanceCenter, float realRelevanceRadius, float realBoxSize)
	: randomPointBoxFactory(randomPointBoxFactory), 
		realRelevanceCenter(realRelevanceCenter), 
		realRelevanceRadius(realRelevanceRadius), 
		realBoxSize(realBoxSize) 
{
	pointCombineDistance = realBoxSize / 3.0f;
	unrealRelevanceSize = (int32_t)ceilf(realRelevanceRadius / (float)realBoxSize);
	unrealRelevanceSizeSquared = unrealRelevanceSize * unrealRelevanceSize;
	obsoleteBoxLimit = (unrealRelevanceSize * unrealRelevanceSize * unrealRelevanceSize) * 4 * 11;
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

void BbLayer::makeOutOfBoundCubesObsolete() {
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

	// clear out obsolete cubes if too many

	if ( obsoletePointBoxes.size() > obsoleteBoxLimit) {
		obsoletePointBoxes.clear();
	}
}

void BbLayer::findNewInBoundsCubes() {
		
	// create new in-bounds cubes

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
							auto centroidBox = make_shared<CentroidBox>();
							this->randomPointBoxFactory->addRandomPointsToBox(
								centroidBox->noisePoints,
								unrealToReal(cubePos), realBoxSize
							);

							this->randomPointBoxes.insert(RandomBoxMapPair(
								cubePos, 
								centroidBox
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
}

void BbLayer::getBoxesForUnreal4BoxCorner(CentroidBox* centroidBoxes[], const Vector<int32_t, 3> & startCorner) {

	// first, get boxes!

	Vector<int32_t, 3> boxPos;
	RandomBoxMap::iterator boxIt;

	for (int i = 0; i < 8; i++) { // 8!!!!
		boxPos = startCorner + Vector<int32_t, 3>(CentroidBox::cornerOffsets[i]);
		boxIt = this->randomPointBoxes.find(boxPos);
		if (boxIt != this->randomPointBoxes.end()) {
			centroidBoxes[i] = boxIt->second.get(); // I know what the hell I am doing
		} else {
			boxIt = this->obsoletePointBoxes.find(boxPos);
			if (boxIt != this->obsoletePointBoxes.end()) {
				centroidBoxes[i] = boxIt->second.get(); // I still know what the hell I am doing
			} else {
				// make a new box!
				auto centroidBox = make_shared<CentroidBox>();
				this->randomPointBoxFactory->addRandomPointsToBox(
					centroidBox->noisePoints,
					unrealToReal(boxPos), realBoxSize
				);

				this->obsoletePointBoxes.insert(RandomBoxMapPair(
					boxPos, 
					centroidBox
				));

				centroidBoxes[i] = centroidBox.get(); // and again, I hope
			}
		}
	}
}

void BbLayer::calculateCentroids() {
	CentroidBox * cb; // local ptr for loop
	CentroidBox* centroidBoxes[8]; // boxes around the corner
	Vector<int32_t, 3> cubePos, cornerPos, startCorner;
	vector<Vector3f> points; // points! helpfull, isn't it?
	points.reserve(12);

	int iCorner, iBox, centroidIndexInOtherBox;
	float halfRealBox = realBoxSize / 2;

	for (auto it = randomPointBoxes.cbegin(); it != randomPointBoxes.cend(); ++it) {
		if (!it->second->centroidsCalculated) {
			
			cubePos = it->first;
			cb = it->second.get();
			for (iCorner = 0; iCorner < 8; iCorner++) {
				// if corner is not calculated
				if (!cb->cornerCalculated[iCorner]) {
					// the end result should be cornerPointBox != nullptr
					shared_ptr<PointBox> cornerPointBox(nullptr);

					points.clear();

					// in case of 0, it is 0, 0, 0
					// get centroid boxes around this corner
					// actually, one of those boxes will be current one, 
					// but we don't care, because this is complicated enough :/
					cornerPos = cubePos + Vector<int32_t, 3>(CentroidBox::cornerOffsets[iCorner]);
					startCorner = cornerPos - Vector<int32_t, 3>(1, 1, 1);
					getBoxesForUnreal4BoxCorner(centroidBoxes, startCorner);
					
					// search for this corner centroid calculated on any other box
					// for each box around this corner
					// should find it 7 out of 8 times
					for (iBox = 0; iBox < 8; iBox++) { // 8!!!
						centroidIndexInOtherBox = CentroidBox::reverseMap[iBox];
						// getit (we hope getBoxesForUnreal4BoxCorner did the job right)
						if (centroidBoxes[iBox]->cornerCalculated[centroidIndexInOtherBox]) {
							// if corner centroid already done, hurray!
							// no need to get points and calculate anything
							// just exit this loop... somehow
							cornerPointBox = centroidBoxes[iBox]->cornerCentroids[centroidIndexInOtherBox];
							break;
						}
					}

					// this should always give calculated centroid corner if it was not found
					if (cornerPointBox == nullptr) {

						cornerPointBox = make_shared<PointBox>();

						// collect the points
						for (iBox = 0; iBox < 8; iBox++) { // 8!!!
							centroidIndexInOtherBox = CentroidBox::reverseMap[iBox];
							auto boundingBoxOffset = CentroidBox::reverseCornerOffsets[iBox];
							Vector3f pointBoundingBoxCorner(boundingBoxOffset[0] * halfRealBox, boundingBoxOffset[1] * halfRealBox, boundingBoxOffset[2] * halfRealBox);
							centroidBoxes[iBox]->noisePoints.collectPointsInBounds(iBox, points, pointBoundingBoxCorner, halfRealBox);
							centroidBoxes[iBox]->cornerCentroids[centroidIndexInOtherBox] = cornerPointBox;
							centroidBoxes[iBox]->cornerCalculated[centroidIndexInOtherBox] = true; // SOON(TM)!
						}

						// finally we have the fucking points
						cornerPointBox->points = points;

						cornerPointBox->combineNearestPoints(pointCombineDistance);
					}

					cb->cornerCalculated[iCorner] = true;
					cb->cornerCentroids[iCorner] = cornerPointBox;
				}
			}

			// corners done, now for the real thing!
			points.clear();
			for (iCorner = 0; iCorner < 8; iCorner++) { // 8!!!
				auto boundingBoxOffset = CentroidBox::reverseCornerOffsets[iCorner];
				Vector3f pointBoundingBoxCorner(boundingBoxOffset[0] * halfRealBox, boundingBoxOffset[1] * halfRealBox, boundingBoxOffset[2] * halfRealBox);
				cb->cornerCentroids[iCorner]->collectPointsInBounds(iCorner, points, pointBoundingBoxCorner, halfRealBox);
			}
			
			cb->centroids.points = points;
			cb->centroids.combineNearestPoints(pointCombineDistance);

			cb->centroidsCalculated = true;
		}
	}
}

void BbLayer::update() {
	Vector<int32_t, 3> newUnrealRelevanceCenter = realToUnreal(realRelevanceCenter);
	if (this->randomPointBoxes.size() > 0 && newUnrealRelevanceCenter == unrealRelevanceCenter) {
		return;
	}
	unrealRelevanceCenter = newUnrealRelevanceCenter;

	makeOutOfBoundCubesObsolete();
	findNewInBoundsCubes();
	calculateCentroids();

	cout << "update location to " << unrealRelevanceCenter.x << " " << unrealRelevanceCenter.y << " " << unrealRelevanceCenter.z << endl;
	cout << "obsolete cube count " << obsoletePointBoxes.size() << endl;
	cout << "bb cube count " << randomPointBoxes.size() << endl;
	
}