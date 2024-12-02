//
// Created by bradr on 11/4/24.
//

#ifndef BPL_GRAPHICS_COLLIDER_FLOOR_H
#define BPL_GRAPHICS_COLLIDER_FLOOR_H

#include <SDL2/SDL.h>
#include <bpl/graphics/Sprite.h>

namespace bpl::graphics::collider {
    class Floor {
    public:
        //
        //  RETURNS
        //      INT_MAX if there is nothing to the left.
        //      0 if we are next to or colliding with what is to the left.
        //
        static int DistanceToWallLeft(const SDL_Rect& floor, const SDL_Rect& objCollider);
        static int DistanceToWallLeft(const bpl::graphics::SpritePtr floor, const SDL_Rect& objCollider);
        static int DistanceToWallLeft(const bpl::graphics::SpriteList &floorSprites, const SDL_Rect& objCollider);

        //
        //  RETURNS
        //      INT_MAX if there is nothing to the right.
        //      0 if we are next to or colliding with what is to the right.
        //
        static int DistanceToWallRight(const SDL_Rect& floor, const SDL_Rect& objCollider);
        static int DistanceToWallRight(const bpl::graphics::SpritePtr floor, const SDL_Rect& objCollider);
        static int DistanceToWallRight(const bpl::graphics::SpriteList &floorSprites, const SDL_Rect& objCollider);

        //
        //  RETURNS
        //      INT_MAX if there is nothing below.
        //      0 if we are next to or colliding with what is below.
        //
        static int DistanceToFloorBelow(const SDL_Rect& floor, const SDL_Rect& objCollider);
        static int DistanceToFloorBelow(const bpl::graphics::SpritePtr floor, const SDL_Rect& objCollider);
        static int DistanceToFloorBelow(const bpl::graphics::SpriteList& floorSprites, const SDL_Rect& objCollider);
    }; // class Floor

} // bpl::graphics::collider

#endif //BPL_GRAPHICS_COLLIDER_FLOOR_H