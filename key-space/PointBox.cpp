#include "PointBox.h"

#include "CentroidBox.h"

using namespace key::space;

PointBox::PointBox() {

}

void PointBox::add(Vector3f point) {
	this->points.push_back(point);
}

void PointBox::collectPointsInBounds(int centroidCornerPointOffset, std::vector<Vector3f> & points, const Vector3f & boundingCubeCorner, const float boundingCubeSize) {
	for (const auto p : this->points) {
		if (p.x >= boundingCubeCorner.x && p.x < boundingCubeCorner.x + boundingCubeSize
		&&	p.y >= boundingCubeCorner.y && p.y < boundingCubeCorner.y + boundingCubeSize
		&&	p.z >= boundingCubeCorner.z && p.z < boundingCubeCorner.z + boundingCubeSize
		) {
			points.push_back(p + Vector3f(
				boundingCubeSize * CentroidBox::centroidCornerPointOffsets[centroidCornerPointOffset][0], 
				boundingCubeSize * CentroidBox::centroidCornerPointOffsets[centroidCornerPointOffset][1], 
				boundingCubeSize * CentroidBox::centroidCornerPointOffsets[centroidCornerPointOffset][2]
			));
		}
	}
}

void PointBox::combineNearestPoints(float distance) {
	auto squared = distance * distance;
	std::vector<Vector3f> newPoints;
	newPoints.reserve(this->points.size());
	std::vector<bool> mergedPoints;
	mergedPoints.reserve(10);
	mergedPoints.resize(this->points.size(), false);

	for (size_t i = 0; i < this->points.size(); i++) {
		if (!mergedPoints[i]) {
			auto point = this->points[i];
			for (size_t iOther = i + 1; iOther < this->points.size(); iOther++) {
				if (!mergedPoints[iOther]) {
					if ((this->points[iOther] - point).length2() < squared) {
						point = (point + this->points[iOther]) / 2;
						mergedPoints[iOther] = true;
					}
				}
			}
			newPoints.push_back(point);
		}
	}
	this->points = newPoints;
}