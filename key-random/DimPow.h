#pragma once

#include <key-common/types.h>

namespace key 
{
	namespace random 
	{	
		namespace util {

			template<int16_t X, int16_t P>
			struct DimPow
			{
				enum { result = X*DimPow<X,P-1>::result };
			};

			template<int16_t X>
			struct DimPow<X,0>
			{
				enum { result = 1 };
			};

			template<int16_t X>
			struct DimPow<X,1>
			{
				enum { result = X };
			};

		}
	}
}