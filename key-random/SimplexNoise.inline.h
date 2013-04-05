#pragma once

#include <cmath>

#include <key-random/util.h>
#include <key-random/SimplexNoise.h>

template<class T>
key::random::SimplexNoise<T, 4, 256>::SimplexNoise(int64_t seed) : permSampler(seed) {
	for (int i = 0; i < 256 * 2; i++) {
		mod32permutations[i] = permSampler.permutations[i] % 32;
	}
}

template<class T>
const int32_t key::random::SimplexNoise<T, 4, 256>::grad4[32][4] = {
	{0,1,1,1},  {0,1,1,-1},  {0,1,-1,1},  {0,1,-1,-1},
    {0,-1,1,1}, {0,-1,1,-1}, {0,-1,-1,1}, {0,-1,-1,-1},
    {1,0,1,1},  {1,0,1,-1},  {1,0,-1,1},  {1,0,-1,-1},
    {-1,0,1,1}, {-1,0,1,-1}, {-1,0,-1,1}, {-1,0,-1,-1},
    {1,1,0,1},  {1,1,0,-1},  {1,-1,0,1},  {1,-1,0,-1},
    {-1,1,0,1}, {-1,1,0,-1}, {-1,-1,0,1}, {-1,-1,0,-1},
    {1,1,1,0},  {1,1,-1,0},  {1,-1,1,0},  {1,-1,-1,0},
    {-1,1,1,0}, {-1,1,-1,0}, {-1,-1,1,0}, {-1,-1,-1,0}
};

			
template<class T>
const int32_t key::random::SimplexNoise<T, 4, 256>::simplex[64][4] = {
    {0,1,2,3},{0,1,3,2},{0,0,0,0},{0,2,3,1},{0,0,0,0},{0,0,0,0},{0,0,0,0},{1,2,3,0},
    {0,2,1,3},{0,0,0,0},{0,3,1,2},{0,3,2,1},{0,0,0,0},{0,0,0,0},{0,0,0,0},{1,3,2,0},
    {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
    {1,2,0,3},{0,0,0,0},{1,3,0,2},{0,0,0,0},{0,0,0,0},{0,0,0,0},{2,3,0,1},{2,3,1,0},
    {1,0,2,3},{1,0,3,2},{0,0,0,0},{0,0,0,0},{0,0,0,0},{2,0,3,1},{0,0,0,0},{2,1,3,0},
    {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
    {2,0,1,3},{0,0,0,0},{0,0,0,0},{0,0,0,0},{3,0,1,2},{3,0,2,1},{0,0,0,0},{3,1,2,0},
    {2,1,0,3},{0,0,0,0},{0,0,0,0},{0,0,0,0},{3,1,0,2},{0,0,0,0},{3,2,0,1},{3,2,1,0}
};

template<class T>
T key::random::SimplexNoise<T, 4, 256>::get(const Vector<T, 4> & position) const {
	// The skewing and unskewing factors are hairy again for the 4D case
    T F4 = (sqrtf(5.0f)-1.0f)/4.0f;
    T G4 = (5.0f-sqrtf(5.0f))/20.0f;
    T n0, n1, n2, n3, n4; // Noise contributions from the five corners

    // Skew the (x,y,z,w) space to determine which cell of 24 simplices we're in
    T s = (position[0] + position[1] + position[2] + position[3]) * F4; // Factor for 4D skewing
    int32_t i = util::floor<T>(position[0] + s);
    int32_t j = util::floor<T>(position[1] + s);
    int32_t k = util::floor<T>(position[2] + s);
    int32_t l = util::floor<T>(position[3] + s);
    T t = (i + j + k + l) * G4; // Factor for 4D unskewing
    T X0 = i - t; // Unskew the cell origin back to (x,y,z,w) space
    T Y0 = j - t;
    T Z0 = k - t;
    T W0 = l - t;

    T x0 = position[0] - X0; // The x,y,z,w distances from the cell origin
    T y0 = position[1] - Y0;
    T z0 = position[2] - Z0;
    T w0 = position[3] - W0;

    // For the 4D case, the simplex is a 4D shape I won't even try to describe.
    // To find out which of the 24 possible simplices we're in, we need to
    // determine the magnitude ordering of x0, y0, z0 and w0.
    // The method below is a good way of finding the ordering of x,y,z,w and
    // then find the correct traversal order for the simplex we're in.
    // First, six pair-wise comparisons are performed between each possible pair
    // of the four coordinates, and the results are used to add up binary bits
    // for an integer index.
    int32_t c1 = (x0 > y0) ? 32 : 0;
    int32_t c2 = (x0 > z0) ? 16 : 0;
    int32_t c3 = (y0 > z0) ? 8 : 0;
    int32_t c4 = (x0 > w0) ? 4 : 0;
    int32_t c5 = (y0 > w0) ? 2 : 0;
    int32_t c6 = (z0 > w0) ? 1 : 0;
    int32_t c = c1 + c2 + c3 + c4 + c5 + c6;

    int32_t i1, j1, k1, l1; // The integer offsets for the second simplex corner
    int32_t i2, j2, k2, l2; // The integer offsets for the third simplex corner
    int32_t i3, j3, k3, l3; // The integer offsets for the fourth simplex corner

    // simplex[c] is a 4-vector with the numbers 0, 1, 2 and 3 in some order.
    // Many values of c will never occur, since e.g. x>y>z>w makes x<z, y<w and x<w
    // impossible. Only the 24 indices which have non-zero entries make any sense.
    // We use a thresholding to set the coordinates in turn from the largest magnitude.
    // The number 3 in the "simplex" array is at the position of the largest coordinate.
    i1 = simplex[c][0]>=3 ? 1 : 0;
    j1 = simplex[c][1]>=3 ? 1 : 0;
    k1 = simplex[c][2]>=3 ? 1 : 0;
    l1 = simplex[c][3]>=3 ? 1 : 0;
    // The number 2 in the "simplex" array is at the second largest coordinate.
    i2 = simplex[c][0]>=2 ? 1 : 0;
    j2 = simplex[c][1]>=2 ? 1 : 0;
    k2 = simplex[c][2]>=2 ? 1 : 0;
    l2 = simplex[c][3]>=2 ? 1 : 0;
    // The number 1 in the "simplex" array is at the second smallest coordinate.
    i3 = simplex[c][0]>=1 ? 1 : 0;
    j3 = simplex[c][1]>=1 ? 1 : 0;
    k3 = simplex[c][2]>=1 ? 1 : 0;
    l3 = simplex[c][3]>=1 ? 1 : 0;
    // The fifth corner has all coordinate offsets = 1, so no need to look that up.

    T x1 = x0 - i1 + G4; // Offsets for second corner in (x,y,z,w) coords
    T y1 = y0 - j1 + G4;
    T z1 = z0 - k1 + G4;
    T w1 = w0 - l1 + G4;
    T x2 = x0 - i2 + 2.0f*G4; // Offsets for third corner in (x,y,z,w) coords
    T y2 = y0 - j2 + 2.0f*G4;
    T z2 = z0 - k2 + 2.0f*G4;
    T w2 = w0 - l2 + 2.0f*G4;
    T x3 = x0 - i3 + 3.0f*G4; // Offsets for fourth corner in (x,y,z,w) coords
    T y3 = y0 - j3 + 3.0f*G4;
    T z3 = z0 - k3 + 3.0f*G4;
    T w3 = w0 - l3 + 3.0f*G4;
    T x4 = x0 - 1.0f + 4.0f*G4; // Offsets for last corner in (x,y,z,w) coords
    T y4 = y0 - 1.0f + 4.0f*G4;
    T z4 = z0 - 1.0f + 4.0f*G4;
    T w4 = w0 - 1.0f + 4.0f*G4;

    // Work out the hashed gradient indices of the five simplex corners
    int32_t ii = i & 255;
    int32_t jj = j & 255;
    int32_t kk = k & 255;
    int32_t ll = l & 255;
    int32_t gi0 = mod32permutations[
		ii+permSampler.permutations[
			jj+permSampler.permutations[
				kk+permSampler.permutations[ll]
			]
		]
	];
    int32_t gi1 = mod32permutations[
		ii+i1+permSampler.permutations[
			jj+j1+permSampler.permutations[
				kk+k1+permSampler.permutations[ll+l1]
			]
		]
	];
    int32_t gi2 = mod32permutations[
		ii+i2+permSampler.permutations[
			jj+j2+permSampler.permutations[
				kk+k2+permSampler.permutations[ll+l2]
			]
		]
	];
    int32_t gi3 = mod32permutations[
		ii+i3+permSampler.permutations[
			jj+j3+permSampler.permutations[
				kk+k3+permSampler.permutations[ll+l3]
			]
		]
	];
    int32_t gi4 = mod32permutations[
		ii+1+permSampler.permutations[
			jj+1+permSampler.permutations[
				kk+1+permSampler.permutations[ll+1]
			]
		]
	];

    // Calculate the contribution from the five corners
    T t0 = 0.6f - x0*x0 - y0*y0 - z0*z0 - w0*w0;
    if(t0<0) n0 = 0.0f;
    else {
        t0 *= t0;
        n0 = t0 * t0 * util::vdot4<T>(grad4[gi0], x0, y0, z0, w0);
    }

    T t1 = 0.6f - x1*x1 - y1*y1 - z1*z1 - w1*w1;
    if(t1<0) n1 = 0.0f;
    else {
        t1 *= t1;
        n1 = t1 * t1 * util::vdot4<T>(grad4[gi1], x1, y1, z1, w1);
    }

    T t2 = 0.6f - x2*x2 - y2*y2 - z2*z2 - w2*w2;
    if(t2<0) n2 = 0.0f;
    else {
        t2 *= t2;
        n2 = t2 * t2 * util::vdot4<T>(grad4[gi2], x2, y2, z2, w2);
    }

    T t3 = 0.6f - x3*x3 - y3*y3 - z3*z3 - w3*w3;
    if(t3<0) n3 = 0.0f;
    else {
        t3 *= t3;
        n3 = t3 * t3 * util::vdot4<T>(grad4[gi3], x3, y3, z3, w3);
    }

    T t4 = 0.6f - x4*x4 - y4*y4 - z4*z4 - w4*w4;
    if(t4<0) n4 = 0.0f;
    else {
        t4 *= t4;
        n4 = t4 * t4 * util::vdot4<T>(grad4[gi4], x4, y4, z4, w4);
    }

    // Sum up and scale the result to cover the range [-1,1]
    return 27.0f * (n0 + n1 + n2 + n3 + n4);
}

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