#pragma once

#include <key-random/GradientVectorSampler.h>

template<class T, int DIMENSIONS, int SAMPLE_SIZE>
T key::random::gradient::GradientVectorSampler<T, DIMENSIONS, SAMPLE_SIZE>::grad(const int16_t hash, const T point[]) const {
	if (hash < 16) {
		return Vector<T, 3>(1, 1, 0) * Vector<T, 3>(point[0], point[1], point[2]);
	}
    return hash / (float)SAMPLE_SIZE;
}


template<class T>
T key::random::gradient::GradientVectorSampler<T, 3, 256>::grad(const int16_t hash, const T point[]) const {
	int h = hash & 15;                    // CONVERT LO 4 BITS OF HASH CODE
    double u = h<8 ? point[0] : point[1],                 // INTO 12 GRADIENT DIRECTIONS.
            v = h<4 ? point[1] : h==12||h==14 ? point[0] : point[2];
    return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}
