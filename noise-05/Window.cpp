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
using namespace noise05;

Window::Window()
	: noise4D(18)
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
		auto zoomChange = event.wheel.y > 0 ? 2.0f : 1/2.0f;
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
	glRotated(offsetX, 0, 1, 0);
	glRotated(offsetY, 1, 0, 0);
	glScalef(zoom, zoom, zoom);

	int size = 40;

	//glEnable( GL_POINT_SMOOTH );
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
	glEnable(GL_BLEND);
	
	glBegin(GL_POINTS);
	for (int z = -size; z <= size; z++) {
		for (int y = -size; y <= size; y++) {
			for (int x = -size; x <= size; x++) {
				auto sample = noise4D.get(Vector<float, 4>(x, y, z, ticks / 170.31f) / 10.38);
				if (sample > 0.2) {
					
					glColor4f(1, 1, 1, sample);
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