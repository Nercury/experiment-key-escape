#include "RandomPointBoxFactory.h"

#include "PointBox.h"

using namespace std;
using namespace key::space;

RandomPointBoxFactory::RandomPointBoxFactory(uint64_t seed) : noise(seed) {

}

std::shared_ptr<PointBox> RandomPointBoxFactory::makeBoxWithRandomPoints(Vector3f boxPosition, float boxSize) {
	
	std::shared_ptr<PointBox> box = make_shared<PointBox>();
	box->add(Vector3f(boxSize / 2.0f, boxSize / 2.0f, boxSize / 2.0f));

	return box;
}