cmake_minimum_required (VERSION 3.8)
project(source VERSION 1.0.0)

#Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_SUPPRESS_REGENERATION true)
set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB _root_files								LIST_DIRECTORIES false "${_src_root_path}/*.h" "${_src_root_path}/*.cpp" "${_src_root_path}/.c")

file(GLOB _application_files						LIST_DIRECTORIES false "${_src_root_path}/application/*.h" "${_src_root_path}/application/*.hpp" "${_src_root_path}/application/*.cpp")
file(GLOB _application_config_files					LIST_DIRECTORIES false "${_src_root_path}/application/config/*.h" "${_src_root_path}/application/config/*.hpp" "${_src_root_path}/application/config/*.hpp" "${_src_root_path}/application/config/*.cpp")
file(GLOB _application_input_files					LIST_DIRECTORIES false "${_src_root_path}/application/input/*.h" "${_src_root_path}/application/input/*.hpp" "${_src_root_path}/application/input/*.cpp")
file(GLOB _application_player_files					LIST_DIRECTORIES false "${_src_root_path}/application/player/*.h" "${_src_root_path}/application/player/*.hpp" "${_src_root_path}/application/player/*.cpp")

file(GLOB _application_scene_files					LIST_DIRECTORIES false "${_src_root_path}/application/scene/*.h" "${_src_root_path}/application/scene/*.hpp" "${_src_root_path}/application/scene/*.cpp")
file(GLOB _application_window_files					LIST_DIRECTORIES false "${_src_root_path}/application/window/*.h" "${_src_root_path}/application/window/*.hpp" "${_src_root_path}/application/window/*.cpp")

file(GLOB _core_algorithms_files					LIST_DIRECTORIES false "${_src_root_path}/core/algorithms/*.h" "${_src_root_path}/core/algorithms/*.hpp" "${_src_root_path}/core/algorithms/*.cpp")
file(GLOB _core_error_files							LIST_DIRECTORIES false "${_src_root_path}/core/error/*.h" "${_src_root_path}/core/error/*.hpp" "${_src_root_path}/core/error/*.cpp")
file(GLOB _core_GL_files							LIST_DIRECTORIES false "${_src_root_path}/core/GL/*.h" "${_src_root_path}/core/GL/*.hpp" "${_src_root_path}/core/GL/*.cpp")
file(GLOB _core_logging_files						LIST_DIRECTORIES false "${_src_root_path}/core/logging/*.h" "${_src_root_path}/core/logging/*.hpp" "${_src_root_path}/core/logging/*.cpp")
file(GLOB _core_math_files							LIST_DIRECTORIES false "${_src_root_path}/core/math/*.h" "${_src_root_path}/core/math/*.hpp" "${_src_root_path}/core/math/*.cpp")
file(GLOB _core_physics_files						LIST_DIRECTORIES false "${_src_root_path}/core/physics/*.h" "${_src_root_path}/core/physics/*.hpp" "${_src_root_path}/core/physics/*.cpp")
file(GLOB _core_platform_files						LIST_DIRECTORIES false "${_src_root_path}/core/platform/*.h" "${_src_root_path}/core/platform/*.hpp" "${_src_root_path}/core/platform/*.cpp")
file(GLOB _core_async_files							LIST_DIRECTORIES false "${_src_root_path}/core/async/*.h" "${_src_root_path}/core/async/*.hpp" "${_src_root_path}/core/async/*.cpp")
file(GLOB _core_types_files							LIST_DIRECTORIES false "${_src_root_path}/core/types/*.h" "${_src_root_path}/core/types/*.hpp" "${_src_root_path}/core/types/*.cpp")
file(GLOB _core_util_files							LIST_DIRECTORIES false "${_src_root_path}/core/util/*.h" "${_src_root_path}/core/util/*.hpp" "${_src_root_path}/core/util/*.cpp")

file(GLOB _rendering_components_files				LIST_DIRECTORIES false "${_src_root_path}/rendering/components/*.h" "${_src_root_path}/rendering/components/*.hpp" "${_src_root_path}/rendering/components/*.cpp")
file(GLOB _rendering_components_shaders_files		LIST_DIRECTORIES false "${_src_root_path}/rendering/components/shaders/*.h" "${_src_root_path}/rendering/components/shaders/*.hpp" "${_src_root_path}/rendering/components/shaders/*.cpp")
file(GLOB _rendering_components_textures_files		LIST_DIRECTORIES false "${_src_root_path}/rendering/components/textures/*.h" "${_src_root_path}/rendering/components/textures/*.hpp" "${_src_root_path}/rendering/components/textures/*.cpp")
file(GLOB _rendering_data_files						LIST_DIRECTORIES false "${_src_root_path}/rendering/data/*.h" "${_src_root_path}/rendering/data/*.hpp" "${_src_root_path}/rendering/data/*.cpp")
file(GLOB _rendering_renderer_files					LIST_DIRECTORIES false "${_src_root_path}/rendering/renderer/*.h" "${_src_root_path}/rendering/renderer/*.hpp" "${_src_root_path}/rendering/renderer/*.cpp")
file(GLOB _rendering_world_files					LIST_DIRECTORIES false "${_src_root_path}/rendering/world/*.h" "${_src_root_path}/rendering/world/*.hpp" "${_src_root_path}/rendering/world/*.cpp")
file(GLOB _rendering_world_block_files				LIST_DIRECTORIES false "${_src_root_path}/rendering/world/block/*.h" "${_src_root_path}/rendering/world/block/*.hpp" "${_src_root_path}/rendering/world/block/*.cpp")
file(GLOB _rendering_world_chunk_files				LIST_DIRECTORIES false "${_src_root_path}/rendering/world/chunk/*.h" "${_src_root_path}/rendering/world/chunk/*.hpp" "${_src_root_path}/rendering/world/chunk/*.cpp")
file(GLOB _rendering_world_generation_files			LIST_DIRECTORIES false "${_src_root_path}/rendering/world/generation/*.h" "${_src_root_path}/rendering/world/generation/*.hpp" "${_src_root_path}/rendering/world/generation/*.cpp")

add_executable(NocturnProject
	${_root_files}

	${_application_files}
	${_application_config_files}
	${_application_input_files}
	${_application_player_files}
	${_application_scene_files}
	${_application_window_files}
	
	${_core_algorithms_files}
	${_core_error_files}
	${_core_GL_files}
	${_core_logging_files}
	${_core_math_files}
	${_core_physics_files}
	${_core_platform_files}
	${_core_async_files}
	${_core_types_files}
	${_core_util_files}
	
	${_rendering_components_files}
	${_rendering_components_shaders_files}
	${_rendering_components_textures_files}
	${_rendering_data_files}
	${_rendering_renderer_files}
	${_rendering_world_files}
	${_rendering_world_block_files}
	${_rendering_world_chunk_files}
	${_rendering_world_generation_files}
)

include_directories(NocturnProject
	"/"
	"../libs/stb/include"
)

target_link_libraries(NocturnProject PUBLIC glfw)
target_link_libraries(NocturnProject PUBLIC glm)
target_link_libraries(NocturnProject PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(NocturnProject PUBLIC glad)
target_link_libraries(NocturnProject PUBLIC stb)

set_target_properties(NocturnProject PROPERTIES FOLDER Nocturn)

set_property(TARGET NocturnProject PROPERTY CXX_STANDARD 20)

add_definitions(-DGLFW_INCLUDE_NONE)

source_group("/" FILES ${_root_files})

source_group("application"  FILES ${_application_files})
source_group("application/config"  FILES ${_application_config_files})
source_group("application/input"  FILES ${_application_input_files})
source_group("application/player"  FILES ${_application_player_files})
source_group("application/scene"  FILES ${_application_scene_files})
source_group("application/window"  FILES ${_application_window_files})

source_group("core"  FILES ${_core_files})
source_group("core/algorithms"  FILES ${_core_algorithms_files})
source_group("core/error"  FILES ${_core_error_files})
source_group("core/GL"  FILES ${_core_GL_files})
source_group("core/logging"  FILES ${_core_logging_files})
source_group("core/math"  FILES ${_core_math_files})
source_group("core/physics"  FILES ${_core_physics_files})
source_group("core/platform"  FILES ${_core_platform_files})
source_group("core/async"  FILES ${_core_async_files})
source_group("core/types"  FILES ${_core_types_files})
source_group("core/util"  FILES ${_core_util_files})

source_group("rendering"  FILES ${_rendering_files})
source_group("rendering/components"  FILES ${_rendering_components_files})
source_group("rendering/components/shaders"  FILES ${_rendering_components_shaders_files})
source_group("rendering/components/textures"  FILES ${_rendering_components_textures_files})
source_group("rendering/data"  FILES ${_rendering_data_files})
source_group("rendering/renderer"  FILES ${_rendering_renderer_files})
source_group("rendering/world"  FILES ${_rendering_world_files})
source_group("rendering/world/block"  FILES ${_rendering_world_block_files})
source_group("rendering/world/chunk"  FILES ${_rendering_world_chunk_files})
source_group("rendering/world/generation"  FILES ${_rendering_world_generation_files})