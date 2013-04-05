#pragma once

#include <cmath>

#include <key-random/util.h>
#include <key-random/SimplexNoise.h>

template<class T>
key::random::SimplexNoise<T, 3, 256>::SimplexNoise(int64_t seed) : permSampler(seed) {
	for (int i = 0; i < 256 * 2; i++) {
		mod12permutations[i] = permSampler.permutations[i] % 12;
	}
}

template<class T>
const int32_t key::random::SimplexNoise<T, 3, 256>::grad3[12][3] = {
	{1,1,0}, {-1,1,0}, {1,-1,0}, {-1,-1,0},
	{1,0,1}, {-1,0,1}, {1,0,-1}, {-1,0,-1},
	{0,1,1}, {0,-1,1}, {0,1,-1}, {0,-1,-1}
};

template<class T>
T key::random::SimplexNoise<T, 3, 256>::get(const Vector<T, 3> & position) const {
	T n0, n1, n2, n3; // Noise contributions from the four corners

    // Skew the input space to determine which simplex cell we're in
    T F3 = 1.0f/3.0f;
    T s = (position[0]+position[1]+position[2])*F3; // Very nice and simple skew factor for 3D
	int32_t i = util::floor(position[0]+s);
    int32_t j = util::floor(position[1]+s);
    int32_t k = util::floor(position[2]+s);

    T G3 = 1.0f/6.0f; // Very nice and simple unskew factor, too
    T t = (i+j+k)*G3;
    T X0 = i-t; // Unskew the cell origin back to (x,y,z) space
    T Y0 = j-t;
    T Z0 = k-t;
    T x0 = position[0]-X0; // The x,y,z distances from the cell origin
    T y0 = position[1]-Y0;
    T z0 = position[2]-Z0;

    // For the 3D case, the simplex shape is a slightly irregular tetrahedron.
    // Determine which simplex we are in.
    int32_t i1, j1, k1; // Offsets for second corner of simplex in (i,j,k) coords
    int32_t i2, j2, k2; // Offsets for third corner of simplex in (i,j,k) coords

    if(x0>=y0) {
        if(y0>=z0) { i1=1; j1=0; k1=0; i2=1; j2=1; k2=0; } // X Y Z order
        else if(x0>=z0) { i1=1; j1=0; k1=0; i2=1; j2=0; k2=1; } // X Z Y order
        else { i1=0; j1=0; k1=1; i2=1; j2=0; k2=1; } // Z X Y order
    }
    else { // x0<y0
        if(y0<z0) { i1=0; j1=0; k1=1; i2=0; j2=1; k2=1; } // Z Y X order
        else if(x0<z0) { i1=0; j1=1; k1=0; i2=0; j2=1; k2=1; } // Y Z X order
        else { i1=0; j1=1; k1=0; i2=1; j2=1; k2=0; } // Y X Z order
    }

    // A step of (1,0,0) in (i,j,k) means a step of (1-c,-c,-c) in (x,y,z),
    // a step of (0,1,0) in (i,j,k) means a step of (-c,1-c,-c) in (x,y,z), and
    // a step of (0,0,1) in (i,j,k) means a step of (-c,-c,1-c) in (x,y,z), where
    // c = 1/6.
    T x1 = x0 - i1 + G3; // Offsets for second corner in (x,y,z) coords
    T y1 = y0 - j1 + G3;
    T z1 = z0 - k1 + G3;
    T x2 = x0 - i2 + 2.0f*G3; // Offsets for third corner in (x,y,z) coords
    T y2 = y0 - j2 + 2.0f*G3;
    T z2 = z0 - k2 + 2.0f*G3;
    T x3 = x0 - 1.0f + 3.0f*G3; // Offsets for last corner in (x,y,z) coords
    T y3 = y0 - 1.0f + 3.0f*G3;
    T z3 = z0 - 1.0f + 3.0f*G3;

    // Work out the hashed gradient indices of the four simplex corners
    int32_t ii = i & 255;
    int32_t jj = j & 255;
    int32_t kk = k & 255;
	int32_t gi0 = mod12permutations[
		ii+permSampler.permutations[
			jj+permSampler.permutations[kk]
		]
	];
    int32_t gi1 = mod12permutations[
		ii+i1+permSampler.permutations[
			jj+j1+permSampler.permutations[kk+k1]
		]
	];
    int32_t gi2 = mod12permutations[
		ii+i2+permSampler.permutations[
			jj+j2+permSampler.permutations[kk+k2]
		]
	];
    int32_t gi3 = mod12permutations[
		ii+1+permSampler.permutations[
			jj+1+permSampler.permutations[kk+1]
		]
	];

    // Calculate the contribution from the four corners
    T t0 = 0.6f - x0*x0 - y0*y0 - z0*z0;
    if(t0<0) n0 = 0.0;
    else {
        t0 *= t0;
		n0 = t0 * t0 * util::vdot3<T>(grad3[gi0], x0, y0, z0);
    }

    T t1 = 0.6f - x1*x1 - y1*y1 - z1*z1;
    if(t1<0) n1 = 0.0f;
    else {
        t1 *= t1;
        n1 = t1 * t1 * util::vdot3<T>(grad3[gi1], x1, y1, z1);
    }

    T t2 = 0.6f - x2*x2 - y2*y2 - z2*z2;
    if(t2<0) n2 = 0.0f;
    else {
        t2 *= t2;
        n2 = t2 * t2 * util::vdot3<T>(grad3[gi2], x2, y2, z2);
    }

    T t3 = 0.6f - x3*x3 - y3*y3 - z3*z3;
    if(t3<0) n3 = 0.0f;
    else {
        t3 *= t3;
        n3 = t3 * t3 * util::vdot3<T>(grad3[gi3], x3, y3, z3);
    }

    // Add contributions from each corner to get the final noise value.
    // The result is scaled to stay just inside [-1,1]
    return 32.0f*(n0 + n1 + n2 + n3);
}

template<class T>
key::random::SimplexNoise<T, 2, 256>::SimplexNoise(int64_t seed) : permSampler(seed) {
	for (int i = 0; i < 256 * 2; i++) {
		mod12permutations[i] = permSampler.permutations[i] % 12;
	}
}

template<class T>
const int32_t key::random::SimplexNoise<T, 2, 256>::grad3[12][3] = {
	{1,1,0}, {-1,1,0}, {1,-1,0}, {-1,-1,0},
	{1,0,1}, {-1,0,1}, {1,0,-1}, {-1,0,-1},
	{0,1,1}, {0,-1,1}, {0,1,-1}, {0,-1,-1}
};

template<class T>
T key::random::SimplexNoise<T, 2, 256>::get(const Vector<T, 2> & position) const {
	// Noise contributions from the three corners
    T n0, n1, n2;

    // Skew the input space to determine which simplex cell we're in
    T F2 = 0.5f * (sqrtf(3.0f) - 1.0f);
    // Hairy factor for 2D
    T s = (position[0] + position[1]) * F2;
	int32_t i = util::floor<T>( position[0] + s );
    int32_t j = util::floor<T>( position[1] + s );

    T G2 = (3.0f - sqrtf(3.0f)) / 6.0f;
    T t = (i + j) * G2;
    // Unskew the cell origin back to (x,y) space
    T X0 = i-t;
    T Y0 = j-t;
    // The x,y distances from the cell origin
    T x0 = position[0]-X0;
    T y0 = position[1]-Y0;

    // For the 2D case, the simplex shape is an equilateral triangle.
    // Determine which simplex we are in.
    int32_t i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
    if(x0>y0) {i1=1; j1=0;} // lower triangle, XY order: (0,0)->(1,0)->(1,1)
    else {i1=0; j1=1;} // upper triangle, YX order: (0,0)->(0,1)->(1,1)

    // A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
    // a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
    // c = (3-sqrt(3))/6
    T x1 = x0 - i1 + G2; // Offsets for middle corner in (x,y) unskewed coords
    T y1 = y0 - j1 + G2;
    T x2 = x0 - 1.0f + 2.0f * G2; // Offsets for last corner in (x,y) unskewed coords
    T y2 = y0 - 1.0f + 2.0f * G2;

    // Work out the hashed gradient indices of the three simplex corners
    int32_t ii = i & 255;
    int32_t jj = j & 255;
    int32_t gi0 = mod12permutations[
		ii+permSampler.permutations[jj]
	];
    int32_t gi1 = mod12permutations[
		ii+i1+permSampler.permutations[jj+j1]
	];
    int32_t gi2 = mod12permutations[
		ii+1+permSampler.permutations[jj+1]
	];

    // Calculate the contribution from the three corners
    T t0 = 0.5f - x0*x0-y0*y0;
    if(t0<0) n0 = 0.0f;
    else {
        t0 *= t0;
        n0 = t0 * t0 * util::vdot2<T>(grad3[gi0], x0, y0); // (x,y) of grad3 used for 2D gradient
    }

    T t1 = 0.5f - x1*x1-y1*y1;
    if(t1<0) n1 = 0.0f;
    else {
        t1 *= t1;
        n1 = t1 * t1 * util::vdot2<T>(grad3[gi1], x1, y1);
    }

    T t2 = 0.5f - x2*x2-y2*y2;
    if(t2<0) n2 = 0.0f;
    else {
        t2 *= t2;
        n2 = t2 * t2 * util::vdot2<T>(grad3[gi2], x2, y2);
    }

    // Add contributions from each corner to get the final noise value.
    // The result is scaled to return values in the interval [-1,1].
    return 70.0f * (n0 + n1 + n2);
}

/*
float raw_noise_2d( const float x, const float y ) {
    // Noise contributions from the three corners
    float n0, n1, n2;

    // Skew the input space to determine which simplex cell we're in
    float F2 = 0.5 * (sqrtf(3.0) - 1.0);
    // Hairy factor for 2D
    float s = (x + y) * F2;
    int i = floorf( x + s );
    int j = floorf( y + s );

    float G2 = (3.0 - sqrtf(3.0)) / 6.0;
    float t = (i + j) * G2;
    // Unskew the cell origin back to (x,y) space
    float X0 = i-t;
    float Y0 = j-t;
    // The x,y distances from the cell origin
    float x0 = x-X0;
    float y0 = y-Y0;

    // For the 2D case, the simplex shape is an equilateral triangle.
    // Determine which simplex we are in.
    int i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
    if(x0>y0) {i1=1; j1=0;} // lower triangle, XY order: (0,0)->(1,0)->(1,1)
    else {i1=0; j1=1;} // upper triangle, YX order: (0,0)->(0,1)->(1,1)

    // A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
    // a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
    // c = (3-sqrt(3))/6
    float x1 = x0 - i1 + G2; // Offsets for middle corner in (x,y) unskewed coords
    float y1 = y0 - j1 + G2;
    float x2 = x0 - 1.0 + 2.0 * G2; // Offsets for last corner in (x,y) unskewed coords
    float y2 = y0 - 1.0 + 2.0 * G2;

    // Work out the hashed gradient indices of the three simplex corners
    int ii = i & 255;
    int jj = j & 255;
    int gi0 = perm[ii+perm[jj]] % 12;
    int gi1 = perm[ii+i1+perm[jj+j1]] % 12;
    int gi2 = perm[ii+1+perm[jj+1]] % 12;

    // Calculate the contribution from the three corners
    float t0 = 0.5 - x0*x0-y0*y0;
    if(t0<0) n0 = 0.0;
    else {
        t0 *= t0;
        n0 = t0 * t0 * dot(grad3[gi0], x0, y0); // (x,y) of grad3 used for 2D gradient
    }

    float t1 = 0.5 - x1*x1-y1*y1;
    if(t1<0) n1 = 0.0;
    else {
        t1 *= t1;
        n1 = t1 * t1 * dot(grad3[gi1], x1, y1);
    }

    float t2 = 0.5 - x2*x2-y2*y2;
    if(t2<0) n2 = 0.0;
    else {
        t2 *= t2;
        n2 = t2 * t2 * dot(grad3[gi2], x2, y2);
    }

    // Add contributions from each corner to get the final noise value.
    // The result is scaled to return values in the interval [-1,1].
    return 70.0 * (n0 + n1 + n2);
}*/