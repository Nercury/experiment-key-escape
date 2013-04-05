#pragma once

#include <key-common/types.h>
#include <key-math/Vector.h>

namespace key 
{
	namespace random 
	{	
		namespace util {

			template<class IntT>
			int16_t wrapInteger(IntT kX, int16_t const kUpperBound);

			template<class T, int SAMPLE_SIZE>
			int16_t wrapInRange(T number);

			template<class T>
			T cossinePolynomialFade(const T t);

			template<class T>
			T lerp(const T t, const T a, const T b);

			template<class T>
			int32_t floor(const T value);

			template<class T, int INDEX>
			void setAllArrayTo(T a[], const T value);

			template<class T, int INDEX>
			void copyArrayTo(const T a[], T b[]);

			template<class T, int INDEX>
			void floorAtoB(const T a[], int32_t b[]);

			template<class T>
			T vdot2( const int32_t g[], const T x, const T y );

			template<class T>
			T vdot3( const int32_t g[], const T x, const T y, const T z );

			template<class T>
			T vdot4( const int32_t g[], const T x, const T y, const T z, const T w );
		}
	}
}

#include <key-random/util.inline.h>