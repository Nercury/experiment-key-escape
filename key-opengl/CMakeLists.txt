project(key-opengl)

### OpenGL

if(APPLE)
	INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
	FIND_LIBRARY(COCOA_LIBRARY Cocoa)
	FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
	MARK_AS_ADVANCED (COCOA_LIBRARY
		OPENGL_LIBRARY)
elseif (WIN32)
	find_package(OpenGL REQUIRED)
endif()	

# if library is SHARED, uncoment following lines:
#if(WIN32)
# 	add_definitions(-DDYNAMIC_LIB)
#endif(WIN32)

add_library(key-opengl STATIC 
	lib_key_opengl.h
	gl.h
	util.h
	util.cpp
	)

target_link_libraries(key-opengl
	${SDL_LIBRARY} # link sdl
	${OPENGL_LIBRARY} # OpenGL
	${GLEW_LIBRARY} # GLEW
	)