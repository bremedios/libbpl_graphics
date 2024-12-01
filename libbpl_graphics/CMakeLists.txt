cmake_minimum_required(VERSION 3.25)

project(bpl_graphics)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2_ttf REQUIRED CONFIG REQUIRED COMPONENTS SDL2_TTF)
find_package(SDL2_IMAGE REQUIRED CONFIG COMPONENTS SDL2_image)

include_directories(include)

set(PUBLIC_HEADER include/bpl/graphics/Window.h
        include/bpl/graphics/Renderer.h
        include/bpl/graphics/EventLoop.h
        include/bpl/graphics/Surface.h
        include/bpl/graphics/Texture.h
        include/bpl/graphics/Font.h
        include/bpl/graphics/FontCache.h
        include/bpl/graphics/RenderObject.h)
set(SOURCE_FILES src/Window.cpp
        src/Renderer.cpp
        src/EventLoop.cpp
        src/Surface.cpp
        src/Texture.cpp
        src/Font.cpp
        src/FontCache.cpp)

add_library(bpl_graphics SHARED ${SOURCE_FILES} ${PUBLIC_HEADER} )
target_link_libraries(bpl_graphics PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image bpl_sys)

install(TARGETS bpl_graphics DESTINATION lib)
install(FILES include/bpl/graphics/Window.h DESTINATION include/bpl/net)
install(FILES include/bpl/graphics/Renderer.h DESTINATION include/bpl/net)