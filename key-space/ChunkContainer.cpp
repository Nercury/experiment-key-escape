#include "ChunkContainer.h"

using namespace key::space;
using namespace std;

ChunkContainer::ChunkContainer()
	: playerPos(0, 0, 0), relevanceRadius(50) {

}

ChunkContainer::~ChunkContainer() {

}

bool ChunkContainer::isPointInsideBounds(Vector3f & point) {
	return false;
}

void ChunkContainer::onPositionUpdate() {

}