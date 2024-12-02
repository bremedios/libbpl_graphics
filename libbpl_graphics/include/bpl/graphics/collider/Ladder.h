//
// Created by bradr on 11/3/24.
//

#ifndef BPL_GRAPHICS_COLLIDER_LADDER_H
#define BPL_GRAPHICS_COLLIDER_LADDER_H

#include <list>
#include <SDL2/SDL.h>

namespace bpl::graphics::collider {
    class Ladder {
    public:
        //
        //  Check to see that we are within our ladders climable area
        //      - We must be within the the ladder bounds left and right
        //      - We only need to overlap the ladder vertically
        //
        static bool WithinLadder(const SDL_Rect& ladder, const SDL_Rect& obj);

        //
        //  Check to see that we can move up or down the ladder
        //
        //  NOTE:
        //      This does not check for any other restrictions or collision, only if a ladder would enable movement.
        //
        static bool CanClimbUpLadder(const SDL_Rect& ladder, const SDL_Rect& collider);
        static bool CanClimbUpLadder(const std::list<SDL_Rect>& ladders, const SDL_Rect& collider);
        static bool CanClimbDownLadder(const SDL_Rect& ladder, const SDL_Rect& collider);
        static bool CanClimbDownLadder(const std::list<SDL_Rect>& ladders, const SDL_Rect& collider);
    }; // class Ladder
}; // namespace bpl::graphics::collider

#endif //BPL_GRAPHICS_COLLIDER_LADDER_H