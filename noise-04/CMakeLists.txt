add_executable(noise-04
	Window.h
	Window.cpp
	main.cpp)

### SDL
if(WIN32)
	if (MSVC)
		# set up for MSVC
		set(SDL_LIBRARY "${KEYLIB_LIBRARIES}/sdl-2/SDL.lib")
		set(SDLMAIN_LIBRARY "${KEYLIB_LIBRARIES}/sdl-2/SDLmain.lib")
		
		# copy SDL.dll to output dir after linking
		set(VS_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR})
		add_custom_command(TARGET noise-04 POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${KEYLIB_LIBRARIES}/sdl-2/SDL.dll" ${VS_OUTPUT_DIR}/SDL.dll)
	else()
		# todo: set up for other compiler
	endif()
else()
	# todo: set up for your platform
endif()
	
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

### GLEW
add_definitions(-DGLEW_STATIC)
if(WIN32)
	if (MSVC)
		set(GLEW_LIBRARY "${KEYLIB_LIBRARIES}/glew/glew32.lib")
	else()
		# todo: set up for other compiler
	endif()
else()
	# todo: set up for your platform
endif()
	
# link executable components-example1 with other libraries
target_link_libraries(noise-04
	key-space
    ${SDL_LIBRARY} # link sdl
	${SDLMAIN_LIBRARY} # link SDL main
	${OPENGL_LIBRARY} # OpenGL
	${GLEW_LIBRARY} # GLEW
)