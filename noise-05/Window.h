#pragma once

#include <memory>

#include <key-common/types.h>
#include <SDL2/SDL.h>

#include <key-random/PerlinNoise.h>

namespace noise05 {
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

		key::random::PerlinNoise<float, 2, 512> noise2D;
	public:
		Window();
		virtual ~Window();

		void handleInput(const SDL_Event &event);
		void update(const float delta);
		void render();
		void postResize(const int16_t width, const int16_t height);
	};
}