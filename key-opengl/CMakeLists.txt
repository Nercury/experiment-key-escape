project(key-opengl)

### OpenGL

if(APPLE)
	find_package(OpenGL REQUIRED)
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
	${SDL2_LIBRARY} # link sdl
	${OPENGL_LIBRARY} # OpenGL
	${GLEW_LIBRARY} # GLEW
	)
