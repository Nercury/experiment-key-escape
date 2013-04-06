#include "PointBox.h"

using namespace key::space;

PointBox::PointBox() {

}

void PointBox::add(Vector3f point) {
	this->points.push_back(point);
}