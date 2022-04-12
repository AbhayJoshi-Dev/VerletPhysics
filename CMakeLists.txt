cmake_minimum_required(VERSION 3.21.2)

project(Ball-Simulator)

set( DEPS_DIR ${CMAKE_SOURCE_DIR}/build/external)

file(GLOB TEST_SOURCE_FILES src/*.cpp)
file(GLOB TEST_HEADER_FILES include/*.h)

add_subdirectory(external/SDL2)

add_subdirectory(external/SDL_image)

add_executable(Ball-Simulator ${TEST_SOURCE_FILES} ${TEST_HEADER_FILES})

target_include_directories(Ball-Simulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL/include/
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_image/)

target_link_libraries(Ball-Simulator SDL2 SDL2main SDL2_image)

add_custom_command(TARGET Ball-Simulator POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${DEPS_DIR}/SDL2/Debug/SDL2d.dll"
                    "${DEPS_DIR}/SDL_image/Debug/SDL2_image.dll"
                    "${DEPS_DIR}/SDL_image/external/libpng-1.6.37/Debug/libpng16d.dll"
                    "${DEPS_DIR}/SDL_image/external/zlib-1.2.11/Debug/zlibd1.dll"
                    $<TARGET_FILE_DIR:Ball-Simulator>)

add_custom_command(TARGET Ball-Simulator POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
       