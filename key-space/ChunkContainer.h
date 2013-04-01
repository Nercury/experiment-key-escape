#pragma once

#include <key-math/Vector3.h>

namespace key
{
	namespace space
	{
		class ChunkContainer
		{
		public:
			Vector3f playerPos;
			float relevanceRadius;

			ChunkContainer();
			virtual ~ChunkContainer();

			bool isPointInsideBounds(Vector3f & point);
			void onPositionUpdate();
		};
	}
}