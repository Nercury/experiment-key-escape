#pragma once

#include <boost/function.hpp>

namespace key
{
	namespace events
	{
		template <class T>
		class Listener
		{
		public:
			Listener();
			virtual ~Listener();

			virtual void onUpdate(std::shared_ptr<T> checker);
		};
	}
}