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

}