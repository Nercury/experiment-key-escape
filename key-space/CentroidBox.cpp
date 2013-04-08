#include "CentroidBox.h"

using namespace std;
using namespace key::space;

const int32_t CentroidBox::cornerOffsets[8][3] = {
	{ 0, 0, 0 }, { 1, 0, 0 }, { 1, 1, 0 }, { 0, 1, 0 },
	{ 0, 0, 1 }, { 1, 0, 1 }, { 1, 1, 1 }, { 0, 1, 1 }
};

const int32_t CentroidBox::reverseCornerOffsets[8][3] = {
	{ 1, 1, 1 }, { 0, 1, 1 }, { 0, 0, 1 }, { 1, 0, 1 },
	{ 1, 1, 0 }, { 0, 1, 0 }, { 0, 0, 0 }, { 1, 0, 0 }
};

const int32_t CentroidBox::centroidCornerPointOffsets[8][3] = {
	{ -1, -1, -1 }, { 1, -1, -1 }, { 1, 1, -1 }, { -1, 1, -1 },
	{ -1, -1, 1 }, { 1, -1, 1 }, { 1, 1, 1 }, { -1, 1, 1 }
};

// maps what directions coresponds to reverse ones
const int32_t CentroidBox::reverseMap[8] = { // nooooo. :/
	6, 7, 4, 5, 2, 3, 0, 1
};

CentroidBox::CentroidBox() : centroidsCalculated(false) {
	for (int i = 0; i < 8; i++) {
		cornerCalculated[i] = false;
	}
}