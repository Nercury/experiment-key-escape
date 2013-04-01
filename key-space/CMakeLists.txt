project(key-space)

# if library is SHARED, uncoment following lines:
#if(WIN32)
# 	add_definitions(-DDYNAMIC_LIB)
#endif(WIN32)

add_library(key-space STATIC 
	lib_key_space.h
	ChunkContainer.h
	ChunkContainer.cpp
	)

target_link_libraries(key-space
	)