project(key)

cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(KEYLIB_PROJECT
	"${CMAKE_SOURCE_DIR}/..")
set(KEYLIB_INCLUDES
    "${KEYLIB_PROJECT}/third-party-include")

# detect architecture for windows
if (WIN32)
	if (CMAKE_CL_64 MATCHES 1)
		set(KEYLIB_LIB_ARCH "x64")
		message("64-bit Windows")
	else()
		set(KEYLIB_LIB_ARCH "x86")
		message("32-bit Windows")
	endif()
elseif(NOT APPLE)
	if(${CMAKE_SIZEOF_VOID_P} MATCHES "8")
		set(KEYLIB_LIB_ARCH "x64")
		message("64-bit Linux")
	else()
		set(KEYLIB_LIB_ARCH "x86")
		message("32-bit Linux")
	endif()
else()
	set(KEYLIB_LIB_ARCH "x64")
endif()

# set library dir
if (MSVC)
	set(WITH_SHARED_LIBS NO)
	set(KEYLIB_LIBRARIES
		"${KEYLIB_PROJECT}/third-party-lib/windows/${KEYLIB_LIB_ARCH}-vc110/${CMAKE_CFG_INTDIR}")
elseif(APPLE)
	set(KEYLIB_LIBRARIES "${KEYLIB_PROJECT}/third-party-lib/apple/${KEYLIB_LIB_ARCH}-clang")
else()
	if (WIN32)
		set(KEYLIB_LIBRARIES
		"${KEYLIB_PROJECT}/third-party-lib/windows/${KEYLIB_LIB_ARCH}-mgw")
	else()
		set(KEYLIB_LIBRARIES
		"${KEYLIB_PROJECT}/third-party-lib/linux/${KEYLIB_LIB_ARCH}-gcc")
	endif()
endif()

### SDL
if(WIN32)
	if (MSVC)
		# set up for MSVC
		set(SDL2_LIBRARY "${KEYLIB_LIBRARIES}/sdl-2/SDL.lib")
		set(SDLMAIN_LIBRARY "${KEYLIB_LIBRARIES}/sdl-2/SDLmain.lib")
	else()
		# todo: set up for other compiler
	endif()
elseif(APPLE)
	find_package(SDL2 REQUIRED)
	include_directories(${SDL2_INCLUDE_DIR})
	set(SDLMAIN_LIBRARY "${SDL2_LIBRARY}")
else()
	# todo: set up for your platform
endif()

### GLEW
add_definitions(-DGLEW_STATIC)
if(WIN32)
	if (MSVC)
		set(GLEW_LIBRARY "${KEYLIB_LIBRARIES}/glew/glew32.lib")
	else()
		# todo: set up for other compiler
	endif()
elseif(APPLE)
	find_package(GLEW REQUIRED)
	if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
		link_libraries(${GLEW_LIBRARIES})
	endif()
else()
	# todo: set up for your platform
endif()

if(APPLE)
	set(Boost_USE_STATIC_LIBS        ON)
	set(Boost_USE_MULTITHREADED      ON)
	set(Boost_USE_STATIC_RUNTIME    OFF)
	find_package(Boost 1.60.0 COMPONENTS random)
endif()

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${KEYLIB_INCLUDES})

add_subdirectory(key-events)
add_subdirectory(key-space)
add_subdirectory(key-opengl)
add_subdirectory(key-common)
add_subdirectory(key-math)
add_subdirectory(key-random)
add_subdirectory(noise-01)
add_subdirectory(noise-02)
add_subdirectory(noise-03)
add_subdirectory(noise-04)
add_subdirectory(noise-05)
add_subdirectory(voronoi-01)
add_subdirectory(voronoi-02)
add_subdirectory(test-01)
