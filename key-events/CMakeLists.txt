project(key-events)

add_library(key-events STATIC 
	Tracker.h
	Tracker.inline.h
	Listener.h
	)
	
set_target_properties(key-events PROPERTIES LINKER_LANGUAGE CXX)