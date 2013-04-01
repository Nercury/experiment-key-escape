project(key-common)

add_library(key-common STATIC 
	types.h
	)
	
set_target_properties(key-common PROPERTIES LINKER_LANGUAGE CXX)