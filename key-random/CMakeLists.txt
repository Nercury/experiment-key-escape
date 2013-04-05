project(key-random)

add_library(key-random STATIC 
	DimPow.h
	SimplexNoise.h
	SimplexNoise.inline.h
	FlatNoise.h
	FlatNoise.inline.h
	util.h
	util.inline.h
	PermutationSampler.h
	PermutationSampler.inline.h
	)
	
set_target_properties(key-random PROPERTIES LINKER_LANGUAGE CXX)