#pragma once

#include <memory>

#include <key-common/types.h>
#include <SDL2/SDL.h>

#include <key-random/SimplexNoise.h>

namespace noise04 {
	class Window 
	{
	private:
		int16_t width;
		int16_t height;

		float offsetX;
		int offsetY;
		int mouseX;
		int mouseY;
		float zoom;

		bool mouseLeftClicked;

		key::random::SimplexNoise<float, 2, 256> noise2D;
	public:
		Window();
		virtual ~Window();

		void handleInput(const SDL_Event &event);
		void update(const float delta);
		void render();
		void postResize(const int16_t width, const int16_t height);
	};
}