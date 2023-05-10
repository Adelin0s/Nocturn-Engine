cmake_minimum_required (VERSION 3.8)
project(Nocturn VERSION 1.0.0)

#Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_SUPPRESS_REGENERATION true)
set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB _root_files								LIST_DIRECTORIES false "${_src_root_path}/*.h" "${_src_root_path}/*.cpp" "${_src_root_path}/.c")

file(GLOB _application_files						LIST_DIRECTORIES false "${_src_root_path}/Application/*.h" "${_src_root_path}/Application/*.hpp" "${_src_root_path}/Application/*.cpp")
file(GLOB _application_config_files					LIST_DIRECTORIES false "${_src_root_path}/Application/config/*.h" "${_src_root_path}/Application/config/*.hpp" "${_src_root_path}/Application/config/*.hpp" "${_src_root_path}/Application/config/*.cpp")
file(GLOB _application_input_files					LIST_DIRECTORIES false "${_src_root_path}/Application/input/*.h" "${_src_root_path}/Application/input/*.hpp" "${_src_root_path}/Application/input/*.cpp")
file(GLOB _application_window_files					LIST_DIRECTORIES false "${_src_root_path}/Application/window/*.h" "${_src_root_path}/Application/window/*.hpp" "${_src_root_path}/Application/window/*.cpp")

file(GLOB _context_files							LIST_DIRECTORIES false "${_src_root_path}/Context/*.h" "${_src_root_path}/Context/*.hpp" "${_src_root_path}/Context/*.cpp")
file(GLOB _context_componenets_files				LIST_DIRECTORIES false "${_src_root_path}/Context/Components/*.h" "${_src_root_path}/Context/Components/*.hpp" "${_src_root_path}/Context/Components/*.cpp")
file(GLOB _context_gameframework_files				LIST_DIRECTORIES false "${_src_root_path}/Context/GameFramework/*.h" "${_src_root_path}/Context/GameFramework/*.hpp" "${_src_root_path}/Context/GameFramework/*.cpp")

file(GLOB _core_async_files							LIST_DIRECTORIES false "${_src_root_path}/Core/Async/*.h" "${_src_root_path}/Core/Async/*.hpp" "${_src_root_path}/Core/Async/*.cpp")
file(GLOB _core_algorithms_files					LIST_DIRECTORIES false "${_src_root_path}/Core/Algorithms/*.h" "${_src_root_path}/Core/Algorithms/*.hpp" "${_src_root_path}/Core/Algorithms/*.cpp")
file(GLOB _core_files								LIST_DIRECTORIES false "${_src_root_path}/Core/*.h" "${_src_root_path}/Core/*.hpp" "${_src_root_path}/Core/*.cpp")
file(GLOB _core_components_files					LIST_DIRECTORIES false "${_src_root_path}/Core/Components/*.h" "${_src_root_path}/Core/Components/*.hpp" "${_src_root_path}/Core/Components/*.cpp")
file(GLOB _core_error_files							LIST_DIRECTORIES false "${_src_root_path}/Core/Error/*.h" "${_src_root_path}/Core/Error/*.hpp" "${_src_root_path}/Core/Error/*.cpp")
file(GLOB _core_GL_files							LIST_DIRECTORIES false "${_src_root_path}/Core/GL/*.h" "${_src_root_path}/Core/GL/*.hpp" "${_src_root_path}/Core/GL/*.cpp")
file(GLOB _core_math_files							LIST_DIRECTORIES false "${_src_root_path}/Core/Math/*.h" "${_src_root_path}/Core/Math/*.hpp" "${_src_root_path}/Core/Math/*.cpp")
file(GLOB _core_misc_files							LIST_DIRECTORIES false "${_src_root_path}/Core/Misc/*.h" "${_src_root_path}/Core/Misc/*.hpp" "${_src_root_path}/Core/Misc/*.cpp")
file(GLOB _core_physics_files						LIST_DIRECTORIES false "${_src_root_path}/Core/Physics/*.h" "${_src_root_path}/Core/Physics/*.hpp" "${_src_root_path}/Core/Physics/*.cpp")
file(GLOB _core_platform_files						LIST_DIRECTORIES false "${_src_root_path}/Core/Platform/*.h" "${_src_root_path}/Core/Platform/*.hpp" "${_src_root_path}/Core/Platform/*.cpp")
file(GLOB _core_scene_files							LIST_DIRECTORIES false "${_src_root_path}/Core/Scene/*.h" "${_src_root_path}/Core/Scene/*.hpp" "${_src_root_path}/Core/Scene/*.cpp")
file(GLOB _core_types_files							LIST_DIRECTORIES false "${_src_root_path}/Core/Types/*.h" "${_src_root_path}/Core/Types/*.hpp" "${_src_root_path}/Core/Types/*.cpp")
file(GLOB _core_util_files							LIST_DIRECTORIES false "${_src_root_path}/Core/Util/*.h" "${_src_root_path}/Core/Util/*.hpp" "${_src_root_path}/Core/Util/*.cpp")

file(GLOB _gui_files								LIST_DIRECTORIES false "${_src_root_path}/Gui/*.h" "${_src_root_path}/Gui/*.hpp" "${_src_root_path}/Gui/*.cpp")

file(GLOB _rendering_components_files				LIST_DIRECTORIES false "${_src_root_path}/Rendering/Components/*.h" "${_src_root_path}/Rendering/Components/*.hpp" "${_src_root_path}/Rendering/Components/*.cpp")
file(GLOB _rendering_components_shaders_files		LIST_DIRECTORIES false "${_src_root_path}/Rendering/Components/Shaders/*.h" "${_src_root_path}/Rendering/Components/Shaders/*.hpp" "${_src_root_path}/Rendering/Components/Shaders/*.cpp")
file(GLOB _rendering_components_textures_files		LIST_DIRECTORIES false "${_src_root_path}/Rendering/Components/Textures/*.h" "${_src_root_path}/Rendering/Components/Textures/*.hpp" "${_src_root_path}/Rendering/Components/Textures/*.cpp")
file(GLOB _rendering_renderer_files					LIST_DIRECTORIES false "${_src_root_path}/Rendering/Renderer/*.h" "${_src_root_path}/Rendering/Renderer/*.hpp" "${_src_root_path}/Rendering/Renderer/*.cpp")
file(GLOB _rendering_renderer_data_files			LIST_DIRECTORIES false "${_src_root_path}/Rendering/Renderer/Data/*.h" "${_src_root_path}/Rendering/Renderer/Data/*.hpp" "${_src_root_path}/Rendering/Renderer/Data/*.cpp")
file(GLOB _rendering_world_files					LIST_DIRECTORIES false "${_src_root_path}/Rendering/World/*.h" "${_src_root_path}/Rendering/World/*.hpp" "${_src_root_path}/Rendering/World/*.cpp")
file(GLOB _rendering_world_block_files				LIST_DIRECTORIES false "${_src_root_path}/Rendering/World/Block/*.h" "${_src_root_path}/Rendering/World/Block/*.hpp" "${_src_root_path}/Rendering/World/Block/*.cpp")
file(GLOB _rendering_world_chunk_files				LIST_DIRECTORIES false "${_src_root_path}/Rendering/World/Chunk/*.h" "${_src_root_path}/Rendering/World/Chunk/*.hpp" "${_src_root_path}/Rendering/World/Chunk/*.cpp")
file(GLOB _rendering_world_generation_files			LIST_DIRECTORIES false "${_src_root_path}/Rendering/World/Generation/*.h" "${_src_root_path}/Rendering/World/Generation/*.hpp" "${_src_root_path}/Rendering/World/Generation/*.cpp")

add_executable(NocturnProject
	${_root_files}

	${_application_files}
	${_application_config_files}
	${_application_input_files}
	${_application_window_files}

	${_context_files}
	${_context_componenets_files}
	${_context_gameframework_files}
	
	${_core_files}
	${_core_algorithms_files}
	${_core_components_files}
	${_core_error_files}
	${_core_GL_files}
	${_core_math_files}
	${_core_misc_files}
	${_core_physics_files}
	${_core_platform_files}
	${_core_scene_files}
	${_core_async_files}
	${_core_types_files}
	${_core_util_files}
	
	${_gui_files}
	
	${_rendering_components_files}
	${_rendering_components_shaders_files}
	${_rendering_components_textures_files}
	${_rendering_renderer_files}
	${_rendering_renderer_data_files}
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
target_link_libraries(NocturnProject PUBLIC glm_static)
target_precompile_headers(NocturnProject REUSE_FROM glm)

#find_package(nlohmann_json)
target_link_libraries(NocturnProject PUBLIC nlohmann_json::nlohmann_json)

target_link_libraries(NocturnProject PUBLIC glad)
target_link_libraries(NocturnProject PUBLIC stb)

set_target_properties(NocturnProject PROPERTIES FOLDER Nocturn)

target_compile_options(NocturnProject PUBLIC "/Zc:__cplusplus")
set_property(TARGET NocturnProject PROPERTY CXX_STANDARD 20)

add_definitions(-DGLFW_INCLUDE_NONE)

source_group("/" FILES ${_root_files})

source_group("Application" FILES ${_application_files})
source_group("Application/Config" FILES ${_application_config_files})
source_group("Application/Input" FILES ${_application_input_files})
source_group("Application/Scene" FILES ${_application_scene_files})
source_group("Application/Window" FILES ${_application_window_files})

source_group("Context" FILES ${_context_files})
source_group("Context/Componenets" FILES ${_context_componenets_files})
source_group("Context/GameFramework" FILES ${_context_gameframework_files})

source_group("Core" FILES ${_core_files})
source_group("Core/Algorithms" FILES ${_core_algorithms_files})
source_group("Core/Components" FILES ${_core_components_files})
source_group("Core/Error" FILES ${_core_error_files})
source_group("Core/GL" FILES ${_core_GL_files})
source_group("Core/Math" FILES ${_core_math_files})
source_group("Core/Misc" FILES ${_core_misc_files})
source_group("Core/Physics" FILES ${_core_physics_files})
source_group("Core/Platform" FILES ${_core_platform_files})
source_group("Core/Scene" FILES ${_core_scene_files})
source_group("Core/Async" FILES ${_core_async_files})
source_group("Core/Types" FILES ${_core_types_files})
source_group("Core/Util" FILES ${_core_util_files})

source_group("Gui" FILES ${_gui_files})

source_group("Rendering" FILES ${_rendering_files})
source_group("Rendering/Components" FILES ${_rendering_components_files})
source_group("Rendering/Components/Shaders" FILES ${_rendering_components_shaders_files})
source_group("Rendering/Components/Textures" FILES ${_rendering_components_textures_files})
source_group("Rendering/Renderer" FILES ${_rendering_renderer_files})
source_group("Rendering/Renderer/Data" FILES ${_rendering_renderer_data_files})
source_group("Rendering/World" FILES ${_rendering_world_files})
source_group("Rendering/World/Block" FILES ${_rendering_world_block_files})
source_group("Rendering/World/Chunk" FILES ${_rendering_world_chunk_files})
source_group("Rendering/World/Generation" FILES ${_rendering_world_generation_files})