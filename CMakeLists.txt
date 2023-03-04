cmake_minimum_required (VERSION 3.8)
project (Nocturn VERSION 1.0.0)

set(NOCTURN_SRC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_SUPPRESS_REGENERATION false)

#/W4 /WX
if (WIN32)
    set(MSVC_COMPILE_DEBUG_OPTIONS "${CMAKE_CXX_FLAGS_DEBUG} /MP /Od /GR- /std:c17 /Gd /fp:fast /Ob2 /Zc:wchar_t /external:anglebrackets /wd4577 /wd4201 /wd4100 /Zc:__cplusplus")
    set(MSVC_COMPILE_RELEASE_OPTIONS "${CMAKE_CXX_FLAGS_RELEASE} /MP /O2 /Ot /Gd /std:c17 /GR- /fp:fast /Ob2 /Zc:wchar_t /external:anglebrackets /wd4577 /wd4201 /wd4100 /Zc:__cplusplus")
    
    if(SKL_LINK_TIME_OPTIMIZATION)
        set(MSVC_COMPILE_RELEASE_OPTIONS "${MSVC_COMPILE_RELEASE_OPTIONS} /GL")
        add_link_options("/LTCG")
    endif()
    
    set(CMAKE_CXX_FLAGS_DEBUG "${MSVC_COMPILE_DEBUG_OPTIONS}")
    set(CMAKE_CXX_FLAGS_RELEASE "${MSVC_COMPILE_RELEASE_OPTIONS}")
else()
    message(FATAL_ERROR "@TODO compiler flags")
endif()

add_subdirectory(libs)
add_subdirectory(source)

set_property(TARGET glm_static PROPERTY CXX_STANDARD 20)

#target_include_directories(Nocturn PUBLIC "${NOCTURN_SRC_ROOT}/")