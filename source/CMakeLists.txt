cmake_minimum_required (VERSION 3.8)

project (Nocturn VERSION 1.0.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_SUPPRESS_REGENERATION false)

add_subdirectory ("libs")
add_subdirectory ("src")
