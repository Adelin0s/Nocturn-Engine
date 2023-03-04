cmake_minimum_required (VERSION 3.8)
project(glad VERSION 1.0.0)

#Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(glad STATIC
	include/glad/glad.h
	include/KHR/khrplatform.h
	src/glad.c
)

set_target_properties(glad PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

source_group("include"  FILES ${_include_files})

# project(glad VERSION 1.0.0)

# set_property(GLOBAL PROPERTY USER_FOLDERS ON)

# set(_src_root_path "${MAKE_CURRENT_SOURCE_DIR}")

# file(
	# GLOB_RECURSE _public_files
	# LIST_DIRECTORIES false
	# "${_src_root_path}/include/glad/glad.h"
	# "${_src_root_path}/include/KHR/khrplatform.h"
	# "${_src_root_path}/src/glad.c"
# )

# add_library(glad INTERFACE)

# source_group("public" FILES ${_public_files})

# target_include_directories(glad INTERFACE "${_src_root_path}/include/")