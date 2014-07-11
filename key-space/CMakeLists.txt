project(key-space)

# if library is SHARED, uncoment following lines:
#if(WIN32)
# 	add_definitions(-DDYNAMIC_LIB)
#endif(WIN32)

### Voro++
if(WIN32)
	if (MSVC)
		set(VORO_LIBRARY "${KEYLIB_LIBRARIES}/voro/voro-cpp.lib")
	endif()
endif()

add_library(key-space STATIC 
	lib_key_space.h
	BbLayer.h
	BbLayer.cpp
	CentroidBox.h
	CentroidBox.cpp
	CentroidBoxManager.h
	CentroidBoxManager.cpp
	PointBox.h
	PointBox.cpp
	)

target_link_libraries(key-space
		${VORO_LIBRARY}
	)