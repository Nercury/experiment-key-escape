#include "Window.h"

#include <memory>
#include <iostream>
#include <cmath>

#include <key-opengl/gl.h>
#include <key-opengl/util.h>

#include <key-math/Vector3.h>
#include <key-math/Matrix.h>

#include <key-space/RandomPointBoxFactory.h>

using namespace std;
using namespace key::space;
using namespace voronoi01;

Window::Window()
	: keyW(false), keyA(false), keyS(false), keyD(false), keySpace(false), keyCtrl(false), previousTicks(0)
{
	mouseLeftClicked = false;
	offsetX = 0.0f;
	offsetY = 0.0f;
	mouseX = 0;
	mouseY = 0;
	zoom = 1.0f;

	centerPos = Vector3f(0,0,0);
	moveSpeed = 0.1f; // per tick

	cout << "==========================================" << endl;
	cout << endl;
	cout << "Example of relevant bounding box calculation." << endl;
	cout << endl;
	cout << "==========================================" << endl;
	cout << endl;
	cout << "Use MOUSE to move view." << endl;
	cout << "Use MOUSEWHEEL to zoom." << endl;
	cout << endl;
	cout << "==========================================" << endl;

	auto pointBoxFactory = make_shared<RandomPointBoxFactory>(15);

	bb = shared_ptr<BbLayer>(new BbLayer(pointBoxFactory, Vector3f(0, 0, 0), 500, 90));
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

	if (event.type == SDL_KEYDOWN && !event.key.repeat) {
		if (event.key.keysym.sym == SDLK_w) {
			keyW = true;
		} else if (event.key.keysym.sym == SDLK_a) {
			keyA = true;
		} else if (event.key.keysym.sym == SDLK_s) {
			keyS = true;
		} else if (event.key.keysym.sym == SDLK_d) {
			keyD = true;
		} else if (event.key.keysym.sym == SDLK_SPACE) {
			keySpace = true;
		} else if (event.key.keysym.sym == SDLK_LCTRL) {
			keyCtrl = true;
		}
	}

	if (event.type == SDL_KEYUP && !event.key.repeat) {
		if (event.key.keysym.sym == SDLK_w) {
			keyW = false;
		} else if (event.key.keysym.sym == SDLK_a) {
			keyA = false;
		} else if (event.key.keysym.sym == SDLK_s) {
			keyS = false;
		} else if (event.key.keysym.sym == SDLK_d) {
			keyD = false;
		} else if (event.key.keysym.sym == SDLK_SPACE) {
			keySpace = false;
		} else if (event.key.keysym.sym == SDLK_LCTRL) {
			keyCtrl = false;
		}
	}
}

void Window::update(const float delta) {

}

void Window::drawArrow(const Vector3f& D, float length, const Vector3f color)
{
	glPushMatrix();
	glScalef(length, length, length);

	glColor3f(color.x, color.y, color.z);

	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(D.x, D.y, D.z);
	glEnd();

	glPopMatrix();
}

void Window::drawXYZ(Vector3f position) {
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);

	// x
	this->drawArrow(Vector3f(1, 0, 0), 200, Vector3f(1,0,0));
	// y
	this->drawArrow(Vector3f(0, 1, 0), 200, Vector3f(0,1,0));
	// z
	this->drawArrow(Vector3f(0, 0, 1), 200, Vector3f(0,0,1));

	glPopMatrix();
}

void Window::drawWireframeBox() {
	glBegin(GL_LINE_STRIP);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 1, 0);
	glVertex3i(1, 1, 0);
	glVertex3i(1, 0, 0);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 1);
	glVertex3i(0, 1, 1);
	glVertex3i(1, 1, 1);
	glVertex3i(1, 0, 1);
	glVertex3i(0, 0, 1);
	glEnd();
	glBegin(GL_LINES);
	glVertex3i(0, 1, 0);
	glVertex3i(0, 1, 1);
	glVertex3i(1, 1, 0);
	glVertex3i(1, 1, 1);
	glVertex3i(1, 0, 0);
	glVertex3i(1, 0, 1);
	glEnd();
}

void Window::render() {
	auto ticks = SDL_GetTicks();
	auto tickChange = ticks - previousTicks;

	// update
	if (keyW || keyA || keyS || keyD || keySpace || keyCtrl) {
		Vector3f change(0);

		if (keyW) {
			change.z -= moveSpeed * tickChange;
		}
		if (keyS) {
			change.z += moveSpeed * tickChange;
		}
		if (keyD) {
			change.x += moveSpeed * tickChange;
		}
		if (keyA) {
			change.x -= moveSpeed * tickChange;
		}
		if (keySpace) {
			change.y += moveSpeed * tickChange;
		}
		if (keyCtrl) {
			change.y -= moveSpeed * tickChange;
		}

		centerPos += change;
		bb->changeRelevanceCenter(centerPos);
	}


	// render

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport( 0, 0, this->width, this->height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	gluPerspective( 90, this->width / (float)this->height, 1.0f, 64000.0f );

	// enter world
	glMatrixMode( GL_MODELVIEW );

	glPointSize(2.0f);

	//glLoadIdentity();
	glPushMatrix();
	
	glTranslatef(0, 0, -1000.0f);
	glRotatef(offsetX / 5.0f, 0, 1, 0);
	glRotatef(offsetY / 5.0f, 1, 0, 0);
	glScalef(zoom, zoom, zoom);

	this->drawXYZ(Vector3f(0,0,0));

	glPushMatrix();
	glTranslatef(-centerPos.x, -centerPos.y, -centerPos.z);
	this->drawXYZ(Vector3f(0,0,0));
	
	//glEnable( GL_POINT_SMOOTH );
	//glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
	glEnable(GL_BLEND);
	
	glColor4f(1, 0, 0, 0.5f);

	// draw boxes
	for (auto it = bb->randomPointBoxes.cbegin(); it != bb->randomPointBoxes.cend(); ++it) {
		glPushMatrix();

		// box position
		auto boxPosition = bb->unrealToReal(it->first);
		glTranslated(boxPosition.x, boxPosition.y, boxPosition.z);
		// box size
		glScalef(bb->realBoxSize, bb->realBoxSize, bb->realBoxSize);
		this->drawWireframeBox();

		glPopMatrix();
	}

	glColor4f(0.8f, 0.8f, 0.8f, 0.3f);

	// draw boxes
	for (auto it = bb->obsoletePointBoxes.cbegin(); it != bb->obsoletePointBoxes.cend(); ++it) {
		glPushMatrix();

		// box position
		auto boxPosition = bb->unrealToReal(it->first);
		glTranslated(boxPosition.x, boxPosition.y, boxPosition.z);
		// box size
		glScalef(bb->realBoxSize, bb->realBoxSize, bb->realBoxSize);
		this->drawWireframeBox();

		glPopMatrix();
	}

	glPopMatrix();
	

	glPopMatrix();

	previousTicks = ticks;
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