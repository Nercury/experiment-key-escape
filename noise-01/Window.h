#pragma once

#include <memory>

#include <key-common/types.h>
#include <SDL2/SDL.h>

namespace noise01 {
	class Window 
	{
	private:
		int16_t width;
		int16_t height;
	public:
		Window();
		virtual ~Window();

		void handleInput(const SDL_Event &event);
		void update(const float delta);
		void render();
		void postResize(const int16_t width, const int16_t height);
	};
}