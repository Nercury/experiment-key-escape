#pragma once

#include <key-random/GradientVectorSampler.h>

// HELPER CODE TO GENERATE GRADIENT VECTORS FOR ALL DIMENSIONS

template<class T, int AXIS>
void key::random::gradient::generateGradientVectors(int excludeAxis, std::list<std::vector<T>> & genList, std::vector<T> & direction) {
	if (excludeAxis == AXIS) {
		direction[AXIS] = 0;
		key::random::gradient::generateGradientVectors<T, AXIS - 1>(excludeAxis, genList, direction);
	} else {
		direction[AXIS] = 1;
		key::random::gradient::generateGradientVectors<T, AXIS - 1>(excludeAxis, genList, direction);
		direction[AXIS] = -1;
		key::random::gradient::generateGradientVectors<T, AXIS - 1>(excludeAxis, genList, direction);
	}
}

template<>
inline void key::random::gradient::generateGradientVectors<float, 0>(int excludeAxis, std::list<std::vector<float>> & genList, std::vector<float> & direction) {
	if (excludeAxis == 0) {
		direction[0] = 0;
		genList.push_back(direction);
	} else {
		direction[0] = 1;
		genList.push_back(direction);
		direction[0] = -1;
		genList.push_back(direction);
	}
}

// GENERAL CASE (EXCEPT 1 dimension)

template<class T, int DIMENSIONS, int SAMPLE_SIZE>
key::random::gradient::GradientVectorSampler<T, DIMENSIONS, SAMPLE_SIZE>::GradientVectorSampler() {
	std::list<std::vector<T>> genList;
	std::vector<T> direction;

	for (int d = 0; d < DIMENSIONS; d++) {
		direction.push_back(0);
	}

	for (int planeDim = 0; planeDim < DIMENSIONS; planeDim++) {
		generateGradientVectors<T, DIMENSIONS - 1>(planeDim, genList, direction);
	}

	Vector<T, DIMENSIONS> vec;
	for (auto it = genList.cbegin(); it != genList.cend(); ++it) {
		for (int d = 0; d < DIMENSIONS; d++) {
			vec[d] = (*it)[d];
		}
		gradients.push_back(vec);
	}

	sampleToGradientRatio =  gradients.size() / (float)SAMPLE_SIZE;
}

template<class T, int DIMENSIONS, int SAMPLE_SIZE>
T key::random::gradient::GradientVectorSampler<T, DIMENSIONS, SAMPLE_SIZE>::grad(const int16_t hash, const T point[]) const {
	size_t gradientNum = (int)(hash * sampleToGradientRatio);
	auto gradient = gradients.at(gradientNum);
	T sum = 0;
	for (int i = 0; i < DIMENSIONS; i++) {
		sum += gradient[i] * point[i];
	}
	return sum;
}

// SPECIALIZE for 1 DIMENSION

template<class T, int SAMPLE_SIZE>
T key::random::gradient::GradientVectorSampler<T, 1, SAMPLE_SIZE>::grad(const int16_t hash, const T point[]) const {
	return (hash / (float)(SAMPLE_SIZE / 2)) - 1;
}

// SPECIALIZE for 3 DIMENSIONS

template<class T, int SAMPLE_SIZE>
key::random::gradient::GradientVectorSampler<T, 3, SAMPLE_SIZE>::GradientVectorSampler() {
	T vectors[4][4][3] = {
		{{1,1,0},    {-1,1,0},    {1,-1,0},    {-1,-1,0}},
		{{1,0,1},    {-1,0,1},    {1,0,-1},    {-1,0,-1}},
		{{0,1,1},    {0,-1,1},    {0,1,-1},    {0,-1,-1}},
		{{1,1,0},    {0,-1,1},    {-1,1,0},    {0,-1,-1}},
	};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			gradients.push_back(Vector<T, 3>(vectors[i][j][0], vectors[i][j][1], vectors[i][j][2]));
		}
	}

	sampleToGradientRatio =  gradients.size() / (float)SAMPLE_SIZE;
}

template<class T, int SAMPLE_SIZE>
T key::random::gradient::GradientVectorSampler<T, 3, SAMPLE_SIZE>::grad(const int16_t hash, const T point[]) const {
	size_t gradientNum = (int)(hash * sampleToGradientRatio);
	return gradients.at(gradientNum) * Vector<T, 3>(point[0], point[1], point[2]);
}

// SPECIALIZE for 3 DIMENSIONS AND 256 SAMPLE SIZE (original perlin implementation)

template<class T>
T key::random::gradient::GradientVectorSampler<T, 3, 256>::grad(const int16_t hash, const T point[]) const {
	int h = hash & 15;                    // CONVERT LO 4 BITS OF HASH CODE
    double u = h<8 ? point[0] : point[1],                 // INTO 12 GRADIENT DIRECTIONS.
            v = h<4 ? point[1] : h==12||h==14 ? point[0] : point[2];
    return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}