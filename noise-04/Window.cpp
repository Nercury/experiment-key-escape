#include "Window.h"

#include <memory>

#include <SDL2/SDL_opengl.h>
#include <math.h>

#include <key-math/Vector3.h>
#include <key-math/Matrix.h>

using namespace std;
using namespace key::random;
using namespace noise04;

Window::Window()
	: noise(15)
{
	mouseLeftClicked = false;
	offsetX = -300;
	offsetY = -14;
	mouseX = 0;
	mouseY = 0;
	zoom = 10;

	cout << "Use MOUSE to move view." << endl;
	cout << "Use MOUSEWHEEL to zoom." << endl;
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
		auto zoomChange = event.wheel.y > 0 ? 1.1f : 1/1.1f;
		zoom *= zoomChange;
		auto mouseWouldChangeX = mouseX * zoomChange;
		auto mouseWouldChangeY = mouseY * zoomChange;
		auto offsetWouldChangeX = offsetX * zoomChange;
		auto offsetWouldChangeY = offsetY * zoomChange;
		offsetX = offsetWouldChangeX + mouseWouldChangeX - mouseX;
		offsetY = offsetWouldChangeY + mouseWouldChangeY - mouseY;
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

	glEnable( GL_POINT_SMOOTH );
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);

	glPointSize(1.0f);

	auto ticks = SDL_GetTicks();

	glBegin(GL_POINTS);
	for (int x = 0; x <= this->width; x+=2) {
		for (int y = 0; y <= this->height; y+=2) {
			auto sample = noise.get(Vector<float, 3>(x + offsetX, y + offsetY, ticks / 900.0f * zoom) / zoom) / 2 + 0.5;
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