#pragma once

#include <memory>

#include <key-common/types.h>
#include <SDL2/SDL.h>

#include <key-random/SimplexNoise.h>

namespace noise03 {
	class Window 
	{
	private:
		int16_t width;
		int16_t height;

		int offsetX;
		int offsetY;
		int mouseX;
		int mouseY;
		float zoom;

		bool mouseLeftClicked;

		key::random::SimplexNoise<float, 3, 256> noise;
	public:
		Window();
		virtual ~Window();

		void handleInput(const SDL_Event &event);
		void update(const float delta);
		void render();
		void postResize(const int16_t width, const int16_t height);
	};
}