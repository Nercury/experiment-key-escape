#include "util.h"

#include <cmath>

#include <key-opengl/gl.h>

void key::opengl::gldPerspective(const double fovx, const double aspect, const double zNear, const double zFar)
{
	// This code is based off the MESA source for gluPerspective
	// *NOTE* This assumes GL_PROJECTION is the current matrix
   
	double xmin, xmax, ymin, ymax;
	double m[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	xmax = zNear * tan(fovx * 3.141592 / 360.0);
	xmin = -xmax;
   
	ymin = xmin / aspect;
	ymax = xmax / aspect;

	// Set up the projection matrix
	m[0,0] = (2.0 * zNear) / (xmax - xmin);
	m[1,1] = (2.0 * zNear) / (ymax - ymin);
	m[2,2] = -(zFar + zNear) / (zFar - zNear);

	m[0,2] = (xmax + xmin) / (xmax - xmin);
	m[1,2] = (ymax + ymin) / (ymax - ymin);
	m[3,2] = -1.0;

	m[2,3] = -(2.0 * zFar * zNear) / (zFar - zNear);
   
	// Add to current matrix
	glMultMatrixd(m);
}