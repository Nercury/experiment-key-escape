#pragma once

#include <memory>

#include <key-common/types.h>
#include <SDL2/SDL.h>

#include <key-random/FlatNoise.h>

namespace noise02 {
	class Window 
	{
	private:
		int16_t width;
		int16_t height;

		key::random::FlatNoise<float, 3, 18> noise;
	public:
		Window();
		virtual ~Window();

		void handleInput(const SDL_Event &event);
		void update(const float delta);
		void render();
		void postResize(const int16_t width, const int16_t height);
	};
}