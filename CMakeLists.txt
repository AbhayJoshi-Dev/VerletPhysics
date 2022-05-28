cmake_minimum_required(VERSION 3.21.2)

project(Ball-Simulator)

set(DEPS_DIR ${CMAKE_SOURCE_DIR}/build/external)

add_subdirectory(external/SDL)

add_subdirectory(external/SDL_image)

set(IMGUI_SOURCE_FILES
external/imgui/imgui.cpp
external/imgui/imgui_demo.cpp
external/imgui/imgui_draw.cpp
external/imgui/imgui_impl_sdlrenderer.cpp
external/imgui/imgui_impl_sdl.cpp
external/imgui/imgui_tables.cpp
external/imgui/imgui_widgets.cpp)

set(IMGUI_HEADER_FILES
external/imgui/imconfig.h
external/imgui/imgui.h
external/imgui/imgui_internal.h
external/imgui/imstb_rectpack.h
external/imgui/imstb_textedit.h
external/imgui/imstb_truetype.h
external/imgui/imgui_impl_sdlrenderer.h
external/imgui/imgui_impl_sdl.h)
  
add_library(imgui STATIC ${IMGUI_SOURCE_FILES} ${IMGUI_HEADER_FILES})
target_include_directories(imgui PUBLIC external/SDL/include/)

file(GLOB BS_SOURCE_FILES src/*.cpp)
file(GLOB BS_HEADER_FILES include/*.h)
  
add_executable(Ball-Simulator ${BS_SOURCE_FILES} ${BS_HEADER_FILES})

target_include_directories(Ball-Simulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL/include/
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_image/
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/)

target_link_libraries(Ball-Simulator imgui SDL2 SDL2main SDL2_image)

add_custom_command(TARGET Ball-Simulator POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${DEPS_DIR}/SDL/Debug/SDL2d.dll"
                    "${DEPS_DIR}/SDL_image/Debug/SDL2_imaged.dll"
                    $<TARGET_FILE_DIR:Ball-Simulator>)

add_custom_command(TARGET Ball-Simulator POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:Ball-Simulator>/res)