#include <iostream>

using namespace std;

float doStuff();

int main(int argc, char* argv[])
{
	cout << doStuff() << endl;

	return 0;
}

float doStuff() {
	//PerlinNoise<3> noise(15);

	float pos[3];
	pos[0] = 1.0f;
	pos[1] = 2.0f;
	pos[2] = 1.1f;

	return 3;//noise.get(pos);
}