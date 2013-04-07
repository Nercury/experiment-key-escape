#include "CentroidBox.h"

using namespace std;
using namespace key::space;

CentroidBox::CentroidBox() : centroidsCalculated(false) {
	for (int i = 0; i < 8; i++) {
		cornerCalculated[i] = false;
	}
}