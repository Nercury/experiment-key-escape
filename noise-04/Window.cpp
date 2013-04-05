#include "Window.h"

#include <memory>
#include <iostream>
#include <cmath>

#include <key-opengl/gl.h>

#include <key-math/Vector3.h>
#include <key-math/Matrix.h>

using namespace std;
using namespace key::random;
using namespace noise04;

Window::Window()
	: noise2D(18)
{
	mouseLeftClicked = false;
	offsetX = 0.0f;
	offsetY = -250.0f;
	mouseX = 0;
	mouseY = 0;
	zoom = 0.004f;

	cout << "==========================================" << endl;
	cout << endl;
	cout << "2D noise example. Y dimension is time" << endl;
	cout << "which makes the line move." << endl;
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

	// GUI
	glViewport( 0, 0, this->width, this->height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho(0, this->width, this->height, 0, 1, -1);
	glMatrixMode( GL_MODELVIEW );

	glPointSize(1.0f);

	auto ticks = SDL_GetTicks();

	glColor3f(1.0f, 0.9f, 0.9f);

	glEnable( GL_POINT_SMOOTH );
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
	glEnable(GL_BLEND);

	glBegin(GL_POINTS);
	for (int x = 0; x <= this->width; x+=2) {
		for (int y = 0; y <= 300; y+=2) {
			auto sample = noise2D.get(Vector<float, 2>((x + offsetX) * zoom * 8, (ticks / 500.0f) - y / 25.0));
			glColor4f(sample, sample, sample, 1 - y / 300.0f);
			glVertex3i(x, y - offsetY, 0.0f);
		}
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (int x = 0; x <= this->width * 8; x+=1) {
		// a lot of this * / + () code is just to get graph look nice and be movable/zoomable in the window
		auto sample = noise2D.get(Vector<float, 2>((x + offsetX * 8) * zoom, ticks / 500.0f));
		glColor4f(sample, sample, sample, 0.9f);
		glVertex3f(x / 8.0f, -sample * 150.0f - offsetY, 0.0f);
	}
	glEnd();


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