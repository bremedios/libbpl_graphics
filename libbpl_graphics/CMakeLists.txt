cmake_minimum_required(VERSION 3.25)

project(bpl_graphics)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2_ttf REQUIRED CONFIG REQUIRED COMPONENTS SDL2_TTF)
find_package(SDL2_IMAGE REQUIRED CONFIG COMPONENTS SDL2_image)

include_directories(include ../../libbpl_sys/libbpl_sys/include ../../libbpl_storage/libbpl_storage/include)

set(PUBLIC_HEADER include/bpl/graphics/Window.h
        include/bpl/graphics/Renderer.h
        include/bpl/graphics/EventLoop.h
        include/bpl/graphics/Surface.h
        include/bpl/graphics/Texture.h
        include/bpl/graphics/Font.h
        include/bpl/graphics/FontCache.h
        include/bpl/graphics/Image.h
        include/bpl/graphics/ImageCache.h
        include/bpl/graphics/RenderObject.h
        include/bpl/graphics/LogicObject.h
        include/bpl/graphics/ui/Window.h
        include/bpl/graphics/draw/ops/Fill.h
        include/bpl/graphics/draw/ops/Image.h
        include/bpl/graphics/draw/ops/Text.h
        include/bpl/graphics/draw/ops/JsonLoader.h
        include/bpl/graphics/collider/Collider.h
        include/bpl/graphics/collider/Floor.h
        include/bpl/graphics/collider/Ladder.h)
set(SOURCE_FILES src/Window.cpp
        src/Renderer.cpp
        src/EventLoop.cpp
        src/Surface.cpp
        src/Texture.cpp
        src/Font.cpp
        src/FontCache.cpp
        src/Image.cpp
        src/Sprite.cpp
        src/ImageCache.cpp
        src/ui/Window.cpp
        src/draw/ops/Op.cpp
        src/draw/ops/Fill.cpp
        src/draw/ops/Image.cpp
        src/draw/ops/Text.cpp
        src/draw/ops/Sprite.cpp
        src/draw/ops/JsonLoader.cpp
        src/collider/Floor.cpp
        src/collider/Ladder.cpp
        src/collider/Collider.cpp)

add_library(bpl_graphics SHARED ${SOURCE_FILES} ${PUBLIC_HEADER} )
target_link_libraries(bpl_graphics PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image bpl_sys bpl_storage)

install(TARGETS bpl_graphics DESTINATION lib)
install(FILES include/bpl/graphics/Window.h DESTINATION include/bpl/graphics)
install(FILES include/bpl/graphics/Renderer.h DESTINATION include/bpl/graphics)
install(FILES include/bpl/graphics/EventLoop.h DESTINATION include/bpl/graphics)
install(FILES include/bpl/graphics/Surface.h DESTINATION include/bpl/graphics)
install(FILES include/bpl/graphics/Texture.h DESTINATION include/bpl/graphics)
install(FILES include/bpl/graphics/Font.h DESTINATION include/bpl/graphics)
install(FILES include/bpl/graphics/Image.h DESTINATION include/bpl/graphics)
install(FILES include/bpl/graphics/Sprite.h DESTINATION include/bpl/graphics)
install(FILES include/bpl/graphics/FontCache.h DESTINATION include/bpl/graphics)
install(FILES include/bpl/graphics/RenderObject.h DESTINATION include/bpl/graphics)
install(FILES include/bpl/graphics/LogicObject.h DESTINATION include/bpl/graphics)
install(FILES include/bpl/graphics/ui/Window.h DESTINATION include/bpl/graphics/ui)
install(FILES include/bpl/graphics/draw/ops/Fill.h DESTINATION include/bpl/graphics/draw/ops)
install(FILES include/bpl/graphics/draw/ops/Op.h DESTINATION include/bpl/graphics/draw/ops)
install(FILES include/bpl/graphics/draw/ops/Image.h DESTINATION include/bpl/graphics/draw/ops)
install(FILES include/bpl/graphics/draw/ops/Text.h DESTINATION include/bpl/graphics/draw/ops)
install(FILES include/bpl/graphics/draw/ops/Sprite.h DESTINATION include/bpl/graphics/draw/ops)
install(FILES include/bpl/graphics/draw/ops/JsonLoader.h DESTINATION include/bpl/graphics/draw/ops)
install(FILES include/bpl/graphics/collider/Collider.h DESTINATION include/bpl/graphics/collider)
install(FILES include/bpl/graphics/collider/Floor.h DESTINATION include/bpl/graphics/collider)
install(FILES include/bpl/graphics/collider/Ladder.h DESTINATION include/bpl/graphics/collider)
