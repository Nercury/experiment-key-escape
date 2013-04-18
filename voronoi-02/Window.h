#pragma once

#include <memory>

#include <key-common/types.h>
#include <SDL2/SDL.h>

#include <key-space/BbLayer.h>

namespace voronoi02 {
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

		Vector3f centerPos;
		float moveSpeed;

		bool keyW;
		bool keyA;
		bool keyS;
		bool keyD;
		bool keySpace;
		bool keyCtrl;

		bool mouseLeftClicked;

		std::shared_ptr<key::space::BbLayer> bb;

		uint32_t previousTicks;

		void drawXYZ(Vector3f position);
		void drawArrow(const Vector3f& D, float length, const Vector3f color);
		void drawWireframeBox();
	public:
		Window();
		virtual ~Window();

		void handleInput(const SDL_Event &event);
		void update(const float delta);
		void render();
		void postResize(const int16_t width, const int16_t height);
	};
}