#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <key-common/types.h>
#include <noise-03/Window.h>

using namespace std;
using namespace noise03;

int main(int argc, char* argv[])
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Failed to initialize SDL: " << SDL_GetError() << endl;
		return 0;
	}

	cout << "Using SDL " << SDL_MAJOR_VERSION << "." << SDL_MINOR_VERSION << "." << SDL_PATCHLEVEL << endl;

	auto sdlWindow = SDL_CreateWindow(
		"Noise 03",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800, 600,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (sdlWindow == 0) {
		cout << "Failed to create a window. " << SDL_GetError() << endl;
		return 0;
	}

	// avoid weird SDL2 bug on resize
	SDL_SetWindowMinimumSize(sdlWindow, 320, 200);
	SDL_SetWindowMaximumSize(sdlWindow, 100000, 100000);
	SDL_SetWindowSize(sdlWindow, 800, 600);

	auto sdlWindowID = SDL_GetWindowID(sdlWindow);
	auto glContext = SDL_GL_CreateContext(sdlWindow);

	Window window;

	window.postResize(800, 600);

	auto err = glewInit();
	if (GLEW_OK != err)
	{
		cout << "Error: " << glewGetErrorString(err) << endl;
		return 0;
	}
	cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << endl;
	
	SDL_Event event;

	uint32_t old_time, current_time;
	current_time = SDL_GetTicks();
	float delta;

	bool quit = false;

	while (!quit)
	{
		old_time = current_time;
	    current_time = SDL_GetTicks();
	    delta = (float)(current_time - old_time);

		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_WINDOWEVENT:
				if (sdlWindowID == event.window.windowID) {
					switch (event.window.event)
					{
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							SDL_GL_MakeCurrent(sdlWindow, glContext);
							window.postResize((int32_t)event.window.data1, (int32_t)event.window.data2);
							break;
						case SDL_WINDOWEVENT_CLOSE:
							fprintf(stderr, "Window %d closed\n", event.window.windowID);
							quit = true;
							break;
					default:
						break;
					}
					break;
				}
				break;
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_KEYUP:
			case SDL_KEYDOWN:
			case SDL_MOUSEWHEEL:
				if (sdlWindowID == event.window.windowID) {
					window.handleInput(event);
				}
				break;
			default:
				break;
			}
		}

		window.update(delta);

		SDL_GL_MakeCurrent(sdlWindow, glContext);

		window.render();

		SDL_GL_SwapWindow(sdlWindow);
	}

	SDL_GL_DeleteContext(glContext);
	SDL_Quit();

	return 0;
}
