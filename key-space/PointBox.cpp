#include "PointBox.h"

using namespace key::space;

PointBox::PointBox() : centroidsCalculated(false) {

}

void PointBox::add(Vector3f point) {
	this->points.push_back(point);
}