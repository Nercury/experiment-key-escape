#pragma once

#define SDL_NO_COMPAT

#if defined(__sparc__)
#  include <sys/inttypes.h>
#else
#  ifdef _MSC_VER
#	 include <stddef.h>
#    if _MSC_VER < 1700
#      ifndef MSC_TYPE_REDEFINITIONS
#        define MSC_TYPE_REDEFINITIONS

typedef signed __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef signed __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef signed __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef signed __int64 int64_t;
typedef unsigned __int64 uint64_t;

#      endif
#    else

#include <stdint.h>

#    endif
#  else
#	 include <stdint.h>
#  endif
#endif

#include <sys/types.h>