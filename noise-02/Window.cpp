#include "Window.h"

#include <memory>
#include <cmath>
#include <iostream>

#include <key-opengl/gl.h>

#include <key-math/Vector3.h>
#include <key-math/Matrix.h>

using namespace std;
using namespace key::random;
using namespace noise02;

Window::Window()
	: noise(15)
{
	cout << "==========================================" << endl;
	cout << endl;
	cout << "This is a noise without interpolation." << endl;
	cout << "Distribution is controlled by randomized" << endl;
	cout << "permutation array and this is the base for" << endl;
	cout << "the all other controlled noise types." << endl;
	cout << endl;
	cout << "The important point here is that given the" << endl;
	cout << "x, y, z and initial SEED you will always" << endl;
	cout << "receive the same value for that point." << endl;
	cout << endl;
	cout << "==========================================" << endl;
}

Window::~Window() {
	
}

void Window::handleInput(const SDL_Event &event) {
	
}

void Window::update(const float delta) {

}

void Window::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// GUI
	glViewport( 0, 0, this->width, this->height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho(0, this->width, this->height, 0, 1, -1);
	glMatrixMode( GL_MODELVIEW );

	glEnable( GL_POINT_SMOOTH );
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);

	glPointSize(2.0f);

	auto ticks = SDL_GetTicks();

	glBegin(GL_POINTS);
	for (int x = 0; x <= this->width; x+=2) {
		for (int y = 0; y <= this->height; y+=2) {
			auto sample = noise.get(Vector<float, 3>(x, y, ticks / 50.0f) / 30);
			glColor3f(sample, sample, sample);
			glVertex3i(x, y, 0.0f);
		}
	}
	glEnd();
}

void Window::postResize(const int16_t width, const int16_t height) {
	this->width = width; 
	this->height = height; 

	glShadeModel( GL_SMOOTH );

    /* Set the background black */
    glClearColor( 0.1f, 0.2f, 0.3f, 1.0f );

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}