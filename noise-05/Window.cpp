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
	offsetY = -250.0f;
	mouseX = 0;
	mouseY = 0;
	zoom = 0.004f;

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
		SDL_GetMouseState(&mouseX, &mouseY);

		auto zoomChange = event.wheel.y > 0 ? 1.1f : 1/1.1f;
		zoom *= zoomChange;
		auto mouseWouldChangeX = mouseX * zoomChange * 8;
		//auto mouseWouldChangeY = mouseY * zoomChange;
		auto offsetWouldChangeX = offsetX * zoomChange;
		//auto offsetWouldChangeY = offsetY * zoomChange;
		offsetX = offsetWouldChangeX / 8 + mouseWouldChangeX / 8 / 8 - mouseX;
		//offsetY = offsetWouldChangeY + mouseWouldChangeY - mouseY;

		//cout << "zoom "<< zoom<<endl;
	}
}

void Window::update(const float delta) {

}

void Window::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport( 0, 0, this->width, this->height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	key::opengl::gldPerspective( 90, this->width / (float)this->height, 1.0f, 64000.0f );

	// enter world
	glMatrixMode( GL_MODELVIEW );

	glPointSize(1.0f);

	auto ticks = SDL_GetTicks();

	glColor3f(1.0f, 0.9f, 0.9f);

	glEnable( GL_POINT_SMOOTH );
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
	glEnable(GL_BLEND);

	


}

void Window::postResize(const int16_t width, const int16_t height) {
	this->width = width; 
	this->height = height;

	glShadeModel( GL_SMOOTH );

    /* Set the background black */
    glClearColor( 0, 0, 0, 1 );

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}