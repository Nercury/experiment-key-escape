#pragma once

#include <list>
#include <memory>

namespace key
{
	namespace events
	{
		template <class T>
		class Listener;

		template <class T>
		class Tracker
		{
		private:
			std::list<std::shared_ptr<T>> listeners;
		public:
			Tracker();
			virtual ~Tracker();

			void listenIn(std::shared_ptr<T> listener);
		};
	}
}

#include <key-events/Tracker.inline.h>