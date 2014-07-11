#include "BbLayer.h"

#include <iostream>

#include "CentroidBoxManager.h"
#include "PointBox.h"
#include "CentroidBox.h"

using namespace key::space;
using namespace std;

BbLayer::BbLayer(std::shared_ptr<CentroidBoxManager> randomPointBoxFactory, Vector3f realRelevanceCenter, float realRelevanceRadius, float realBoxSize)
	: randomPointBoxFactory(randomPointBoxFactory), 
		realRelevanceCenter(realRelevanceCenter), 
		realRelevanceRadius(realRelevanceRadius), 
		realBoxSize(realBoxSize) 
{
	this->pointCombineDistance = this->realBoxSize / 7.0f;
	this->unrealRelevanceSize = (int32_t)ceilf(this->realRelevanceRadius / (float)this->realBoxSize);
	this->unrealRelevanceSizeSquared = this->unrealRelevanceSize * this->unrealRelevanceSize;
	this->obsoleteBoxLimit = (this->unrealRelevanceSize * this->unrealRelevanceSize * this->unrealRelevanceSize) * 4 * 11;
	this->update();
}

BbLayer::~BbLayer() {

}

void BbLayer::changeRelevanceCenter(Vector3f newCenter) {
	if ((newCenter - this->realRelevanceCenter).length() >= this->realBoxSize) {
		this->realRelevanceCenter = newCenter;
		
		cout << "Update RC: " << newCenter.x << " " << newCenter.y << " " << newCenter.z << endl;

		this->update();
	}
}

Vector3f BbLayer::unrealToReal(Vector<int32_t, 3> boxCoordinates) {
	return Vector3f((float)boxCoordinates[0] * this->realBoxSize, (float)boxCoordinates[1] * this->realBoxSize, (float)boxCoordinates[2] * this->realBoxSize);
}

Vector<int32_t, 3> BbLayer::realToUnreal(Vector3f boxCoordinates) {
	return Vector<int32_t, 3>((int32_t)(boxCoordinates[0] / this->realBoxSize), (int32_t)(boxCoordinates[1] / this->realBoxSize), (int32_t)(boxCoordinates[2] / this->realBoxSize));
}

static double rnd() {return double(rand())/RAND_MAX;}

void BbLayer::makeOutOfBoundCubesObsolete() {
	// remove existing cubes if out of bounds

	Vector3f diffFromCenter;
	Vector3f half(0.5f);

	for (auto it = this->randomPointBoxes.cbegin(); it != this->randomPointBoxes.cend(); ) {
		diffFromCenter = (it->first - this->unrealRelevanceCenter);
		
		if (diffFromCenter.length2() > this->unrealRelevanceSizeSquared - 0.7) {
			this->obsoletePointBoxes.insert(RandomBoxMapPair(
				it->first,
				it->second
			));
			randomPointBoxes.erase(it++);
		} else {
			++it;
		}
	}

	// clear out obsolete cubes if too many

	if ( this->obsoletePointBoxes.size() > this->obsoleteBoxLimit) {
		this->obsoletePointBoxes.clear();
	}

	/*double x_min=-1,x_max=1;
	double y_min=-1,y_max=1;
	double z_min=-1,z_max=1;
	double cvol=(x_max-x_min)*(y_max-y_min)*(x_max-x_min);
	const int n_x=6,n_y=6,n_z=6;
	const int particles=20;
	double x,y,z;

	// Create a container with the geometry given above, and make it
    // non-periodic in each of the three coordinates. Allocate space for
    // eight particles within each computational block
    voro::container con(x_min,x_max,y_min,y_max,z_min,z_max,n_x,n_y,n_z,
                  false,false,false,8);
 
	// Randomly add particles into the container
	for(int i=0;i<particles;i++) {
		 x=x_min+rnd()*(x_max-x_min);
		 y=y_min+rnd()*(y_max-y_min);
		 z=z_min+rnd()*(z_max-z_min);
		 con.put(i,x,y,z);
	}

	double vvol=con.sum_cell_volumes();
        printf("Container volume : %g\n"
               "Voronoi volume   : %g\n"
               "Difference       : %g\n",cvol,vvol,vvol-cvol);*/

}

void BbLayer::findNewInBoundsCubes() {
		
	// create new in-bounds cubes

	Vector3f diffFromCenter;
	Vector<int32_t, 3> cubePos;
	RandomBoxMap::iterator existingCubeIt;
	Vector3f half(0.5f);

	for (cubePos.x = this->unrealRelevanceCenter.x - this->unrealRelevanceSize; cubePos.x < this->unrealRelevanceCenter.x + this->unrealRelevanceSize; cubePos.x++) {
		for (cubePos.y = this->unrealRelevanceCenter.y - this->unrealRelevanceSize; cubePos.y < this->unrealRelevanceCenter.y + this->unrealRelevanceSize; cubePos.y++) {
			for (cubePos.z = this->unrealRelevanceCenter.z - this->unrealRelevanceSize; cubePos.z < this->unrealRelevanceCenter.z + this->unrealRelevanceSize; cubePos.z++) {
				diffFromCenter = (cubePos - this->unrealRelevanceCenter);
				if (diffFromCenter.length2() <= this->unrealRelevanceSizeSquared - 0.7) {
					existingCubeIt = this->randomPointBoxes.find(cubePos);
					if (existingCubeIt == this->randomPointBoxes.end()) {
						existingCubeIt = this->obsoletePointBoxes.find(cubePos);
						if (existingCubeIt == this->obsoletePointBoxes.end()) {
							auto centroidBox = make_shared<CentroidBox>();
							this->randomPointBoxFactory->addRandomPointsToBox(
								centroidBox->noisePoints,
								this->unrealToReal(cubePos), this->realBoxSize
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
					this->unrealToReal(boxPos), this->realBoxSize
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
	float halfRealBox = this->realBoxSize / 2;

	for (auto it = this->randomPointBoxes.cbegin(); it != this->randomPointBoxes.cend(); ++it) {
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
					this->getBoxesForUnreal4BoxCorner(centroidBoxes, startCorner);
					
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

						cornerPointBox->combineNearestPoints(this->pointCombineDistance);
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
			cb->centroids.combineNearestPoints(this->pointCombineDistance);

			//cout << "NUM of centroids in a cube: " << cb->centroids.points.size() << endl;

			cb->centroidsCalculated = true;
		}
	}
}

void BbLayer::update() {
	Vector<int32_t, 3> newUnrealRelevanceCenter = this->realToUnreal(this->realRelevanceCenter);
	if (this->randomPointBoxes.size() > 0 && newUnrealRelevanceCenter == this->unrealRelevanceCenter) {
		return;
	}
	this->unrealRelevanceCenter = newUnrealRelevanceCenter;

	//cout << "Unreal C: " << newUnrealRelevanceCenter.x << " " << newUnrealRelevanceCenter.y << " " << newUnrealRelevanceCenter.z << endl;

	this->makeOutOfBoundCubesObsolete();
	this->findNewInBoundsCubes();
	this->calculateCentroids();

	//cout << "update location to " << unrealRelevanceCenter.x << " " << unrealRelevanceCenter.y << " " << unrealRelevanceCenter.z << endl;
	//cout << "obsolete cube count " << obsoletePointBoxes.size() << endl;
	//cout << "bb cube count " << randomPointBoxes.size() << endl;
	
}