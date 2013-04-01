#pragma once

#include <key-random/GradientVectorSampler.h>

// GENERAL CASE (EXCEPT 1 dimension)

/*template<class T, int DIMENSIONS, int SAMPLE_SIZE>
key::random::gradient::GradientVectorSampler<T, DIMENSIONS, SAMPLE_SIZE>::GradientVectorSampler() {
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

template<class T, int DIMENSIONS, int SAMPLE_SIZE>
T key::random::gradient::GradientVectorSampler<T, DIMENSIONS, SAMPLE_SIZE>::grad(const int16_t hash, const T point[]) const {
	size_t gradientNum = (int)(hash * sampleToGradientRatio);
	return gradients.at(gradientNum) * Vector<T, 3>(point[0], point[1], point[2]);
}*/

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