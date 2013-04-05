project(key)

cmake_minimum_required(VERSION 2.8)

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
	message("Sytem architecture detection may be incorrect for APPLE")
	set(KEYLIB_LIB_ARCH "x64")
endif()
	
# set library dir
if (MSVC)
	set(WITH_SHARED_LIBS NO)
	set(KEYLIB_LIBRARIES
		"${KEYLIB_PROJECT}/third-party-lib/windows/${KEYLIB_LIB_ARCH}-vc110/${CMAKE_CFG_INTDIR}")
else()
	if (WIN32)
		set(KEYLIB_LIBRARIES
		"${KEYLIB_PROJECT}/third-party-lib/windows/${KEYLIB_LIB_ARCH}-mgw")
	else()
		set(KEYLIB_LIBRARIES
		"${KEYLIB_PROJECT}/third-party-lib/linux/${KEYLIB_LIB_ARCH}-gcc")
	endif()
endif()

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${KEYLIB_INCLUDES})

add_subdirectory(key-events)
add_subdirectory(key-space)
add_subdirectory(key-common)
add_subdirectory(key-math)
add_subdirectory(key-random)
add_subdirectory(noise-01)
add_subdirectory(noise-02)
add_subdirectory(noise-03)
add_subdirectory(noise-04)
add_subdirectory(noise-05)
add_subdirectory(test-01)