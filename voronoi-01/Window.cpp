#include "Window.h"

#include <memory>
#include <iostream>
#include <cmath>

#include <key-opengl/gl.h>
#include <key-opengl/util.h>

#include <key-math/Vector3.h>
#include <key-math/Matrix.h>

using namespace std;
using namespace key::random;
using namespace voronoi01;

Window::Window()
	: noise3D(18)
{
	mouseLeftClicked = false;
	offsetX = 0.0f;
	offsetY = 0.0f;
	mouseX = 0;
	mouseY = 0;
	zoom = 1.0f;

	cout << "==========================================" << endl;
	cout << endl;
	cout << "4D noise example. 4th dimension is time" << endl;
	cout << "which makes the stuff move." << endl;
	cout << endl;
	cout << "==========================================" << endl;
	cout << endl;
	cout << "Use MOUSE to move view." << endl;
	cout << "Use MOUSEWHEEL to zoom." << endl;
	cout << endl;
	cout << "==========================================" << endl;
}

Window::~Window() {
	
}

void Window::handleInput(const SDL_Event &event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		mouseLeftClicked = true;
	} else if (event.type == SDL_MOUSEBUTTONUP) {
		mouseLeftClicked = false;
	}

	
	if (event.type == SDL_MOUSEMOTION) {
		if (mouseLeftClicked) {
			offsetX -= event.motion.xrel;
			offsetY -= event.motion.yrel;
		}

		mouseX = event.motion.x;
		mouseY = event.motion.y;
	}

	if (event.type == SDL_MOUSEWHEEL) {
		auto zoomChange = event.wheel.y > 0 ? 1.2f : 1/1.2f;
		zoom *= zoomChange;

		cout << "zoom: " << zoom << endl;
	}
}

void Window::update(const float delta) {

}

void Window::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport( 0, 0, this->width, this->height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	gluPerspective( 90, this->width / (float)this->height, 1.0f, 64000.0f );

	// enter world
	glMatrixMode( GL_MODELVIEW );

	glPointSize(2.0f);

	auto ticks = SDL_GetTicks();

	//glLoadIdentity();
	glPushMatrix();

	
	glTranslatef(0, 0, -1000.0f);
	glRotatef(offsetX / 5.0f, 0, 1, 0);
	glRotatef(offsetY / 5.0f, 1, 0, 0);
	glScalef(zoom, zoom, zoom);

	int size = 50;

	//glEnable( GL_POINT_SMOOTH );
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
	glEnable(GL_BLEND);
	
	glColor3f(1, 1, 1);

	glBegin(GL_POINTS);
	for (int z = -size; z <= size; z+=1) {
		for (int y = -size; y <= size; y+=1) {
			for (int x = -size; x <= size; x+=1) {
				auto sample = noise3D.get(Vector<float, 3>(x, y, z) / 3.38);
				if (sample > 0.9) {
					glVertex3i(x * 100.0, y * 100.0, z * 100.0);
				}
			}
		}
	}	
	glEnd();

	glPopMatrix();
}

void Window::postResize(const int16_t width, const int16_t height) {
	this->width = width; 
	this->height = height;

	glShadeModel( GL_SMOOTH );

    /* Set the background black */
    glClearColor( 0, 0, 0, 1 );

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST); // has depth
	glDisable(GL_BLEND); // no blending
}