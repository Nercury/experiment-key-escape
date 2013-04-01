#ifndef H_LIBKEYSPACE_H
#  define H_LIBKEYSPACE_H

#  ifdef WIN32
#   ifdef DYNAMIC_LIB
#    ifdef key_space_EXPORTS
#      define LIB_KEY_SPACE __declspec(dllexport)
#    else
#      define LIB_KEY_SPACE __declspec(dllimport)
#    endif
#   else
#    define LIB_KEY_SPACE
#   endif
#  else
#    define LIB_KEY_SPACE
#  endif

#endif
