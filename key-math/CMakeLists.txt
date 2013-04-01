project(key-math)

add_library(key-math STATIC 
	Matrix.h
	Matrix.inline.h
	Missing.h
	Plane.h
	Quaternion.h
	Quaternion.inline.h
	Vector.h
	Vector.inline.h
	Vector1.h
	Vector1.inline.h
	Vector2.h
	Vector2.inline.h
	Vector3.h
	Vector3.inline.h
	Vector4.h
	Vector4.inline.h
	)
	
set_target_properties(key-math PROPERTIES LINKER_LANGUAGE CXX)