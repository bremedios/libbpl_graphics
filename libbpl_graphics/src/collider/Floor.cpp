//
// Created by Bradley Remedios on 11/4/24.
//
#include <iostream>
#include <SDL2/SDL.h>

#include <bpl/graphics/collider/Collider.h>
#include <bpl/graphics/collider/Floor.h>

namespace bpl::graphics::collider {

    int Floor::DistanceToWallLeft(const SDL_Rect& floor, const SDL_Rect& objCollider) {
        int distance = INT_MAX;

        //
        //  We check for a wall collision, if we have a wall collision there is no distance to the wall to the left.
        //
        if (collider::Collider::IsColliding(floor, objCollider)) {
            return 0;
        }

        //
        //  Ignore any floor that is to the right of the token.
        if (objCollider.x < floor.x) {
            return distance;
        }

        if (collider::Collider::InHorizontalSpace(floor, objCollider)) {
            int distanceToLeft = objCollider.x - (floor.x + floor.w);

            if (distanceToLeft >= 0) {
                distance = std::min(distance, distanceToLeft);
            }
        }

        return distance;
    } // DistanceToWallLeft

    int Floor::DistanceToWallLeft(const graphics::SpritePtr floor, const SDL_Rect& objCollider) {
        return DistanceToWallLeft(floor->GetCollider(), objCollider);
    } // DistanceToWallLeft

    int Floor::DistanceToWallLeft(const graphics::SpriteList &floorSprites, const SDL_Rect& objCollider) {
        int distance = INT_MAX;

        for (auto it = floorSprites.begin(); it != floorSprites.end(); it++) {
            distance = std::min(distance, DistanceToWallLeft(*it, objCollider));
        }

        return distance;
    } // DistanceToWallLeft

    int Floor::DistanceToWallRight(const SDL_Rect& floor, const SDL_Rect& objCollider) {
        int distance = INT_MAX;

        //
        //  We check for a wall collision, if we have a wall collision there is no distance to the wall to the left.
        //
        if (collider::Collider::IsColliding(floor, objCollider)) {
            return 0;
        }

        //
        //  Ignore any floor that is to the left of the token.
        if ((objCollider.x  + objCollider.w) > floor.x) {
            return distance;
        }

        // If we would collide with the floor if we move to the right
        if (collider::Collider::InHorizontalSpace(floor, objCollider)) {
            int distanceToRight = floor.x - (objCollider.x + objCollider.w);

            if (distanceToRight >= 0) {
                distance = std::min(distance, distanceToRight);
            }
        }

        return distance;
    } // DistanceToWallRight

    int Floor::DistanceToWallRight(const graphics::SpritePtr floor, const SDL_Rect& objCollider) {
        return DistanceToWallRight(floor->GetCollider(), objCollider);
    } // DistanceToWallRight

    int Floor::DistanceToWallRight(const graphics::SpriteList &floorSprites, const SDL_Rect& objCollider) {
        int distance = INT_MAX;

        for (auto it = floorSprites.begin(); it != floorSprites.end(); it++) {
            distance = std::min(distance, DistanceToWallRight(*it, objCollider));
        }

        return distance;
    } // DistanceToWallRight

    int Floor::DistanceToFloorBelow(const SDL_Rect& floor, const SDL_Rect& objCollider) {
        int distance = INT_MAX;

        //
        //  We check for a floor collision, if we have a floor collision we cannot fall.
        //
        if (collider::Collider::IsColliding(floor, objCollider)) {
            return 0;
        }

        if (collider::Collider::InVerticalSpace(floor, objCollider)) {
            //int distanceToFloor = floorCollider.y - (objCollider.y + objCollider.h);
            int distanceToFloor = floor.y - ((objCollider.y + objCollider.h));

            if (distanceToFloor >= 0) {
                distance = std::min(distance, distanceToFloor);
            }
        }

        return distance;
    } // DistanceToFloorBelow

    int Floor::DistanceToFloorBelow(const graphics::SpritePtr floor, const SDL_Rect& objCollider) {
        return DistanceToFloorBelow(floor->GetCollider(), objCollider);
    } // DistanceToFloorBelow

    int Floor::DistanceToFloorBelow(const graphics::SpriteList &floorSprites, const SDL_Rect& objCollider) {
        int distance = INT_MAX;

        for (auto it = floorSprites.begin(); it != floorSprites.end(); it++) {
            distance = std::min(distance, DistanceToFloorBelow(*it, objCollider));
        }

        return distance;
    } // DistanceToFloorBelow

}; // bpl::graphics::collider