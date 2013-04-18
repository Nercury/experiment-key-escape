add_executable(noise-02
	Window.h
	Window.cpp
	main.cpp)

### SDL
if(WIN32)
	if (MSVC)
		# copy SDL.dll to output dir after linking
		set(VS_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR})
		add_custom_command(TARGET noise-02 POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${KEYLIB_LIBRARIES}/sdl-2/SDL.dll" ${VS_OUTPUT_DIR}/SDL.dll)
	endif()
endif()

# link executable components-example1 with other libraries
target_link_libraries(noise-02
	key-space
	key-opengl
	${SDLMAIN_LIBRARY} # link SDL main
)
