cmake_minimum_required(VERSION 3.25.0)

project(VerletPhysics)

set(DEPS_DIR ${CMAKE_SOURCE_DIR}/build/external)

add_subdirectory(external/SDL)

file(GLOB SOURCE_FILES src/*.cpp)
file(GLOB HEADER_FILES include/*.h)
  
add_executable(VerletPhysics ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(VerletPhysics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL/include/)

target_link_libraries(VerletPhysics SDL2 SDL2main)

add_custom_command(TARGET VerletPhysics POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${DEPS_DIR}/SDL/Debug/SDL2d.dll"
                    $<TARGET_FILE_DIR:VerletPhysics>)