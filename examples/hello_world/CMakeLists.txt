cmake_minimum_required(VERSION 3.25)

project(hello_world_graphics)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2_ttf REQUIRED CONFIG REQUIRED COMPONENTS SDL2_TTF)

include_directories(../../libbpl_graphics/include)

add_executable(hello_world_graphics src/main.cpp)
target_link_libraries(hello_world_graphics PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf bpl_graphics)