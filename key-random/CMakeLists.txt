project(key-random)

add_library(key-random STATIC 
	DimPow.h
	FlatNoise.h
	FlatNoise.inline.h
	PerlinNoise.h
	PerlinNoise.inline.h
	PerlinUtils.h
	PerlinUtils.inline.h
	PermutationSampler.h
	PermutationSampler.inline.h
	GradientVectorSampler.h
	GradientVectorSampler.inline.h
	)
	
set_target_properties(key-random PROPERTIES LINKER_LANGUAGE CXX)