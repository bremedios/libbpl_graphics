//
// Created by Bradley Remedios on 11/3/24.
//
#include <iostream>
#include <list>

#include <SDL2/SDL.h>

#include <bpl/graphics/collider/Collider.h>
#include <bpl/graphics/collider/Ladder.h>

namespace bpl::graphics::collider {
    bool Ladder::WithinLadder(const SDL_Rect& ladder, const SDL_Rect& obj) {
        //
        //  We cannot be left or right of the ladder to climb it.
        //
        if ((obj.x < ladder.x) || ((obj.x + obj.w) > (ladder.x + ladder.w)))
            return false;

        //
        //  We must overlap the ladder vertically
        //
        if (((obj.y + obj.h) < ladder.y) || (obj.y > (ladder.y + ladder.h)))
            return false;

        return true;
    } // WithinLadder

    bool Ladder::CanClimbUpLadder(const SDL_Rect& ladder, const SDL_Rect& collider) {
        //
        //  If we are within the ladder we can climb up it, not other checks are required.
        //
        if (!Ladder::WithinLadder(ladder, collider)) {
            return false;
        }

        //
        //  We cannot climb up unless there is a ladder that we are within, no other checks required.
        //

        return true;
    } // CanClimbUpLadder

    bool Ladder::CanClimbUpLadder(const std::list<SDL_Rect>& ladders, const SDL_Rect& collider) {
        for (auto it = ladders.begin(); it != ladders.end(); ++it) {
            if (CanClimbUpLadder(*it, collider)) {
                return true;
            }
        }

        return false;
    } // CanClimbUpLadder

    bool Ladder::CanClimbDownLadder(const SDL_Rect& ladder, const SDL_Rect& collider) {
        //
        //  If we are within the ladder we can climb up it, not other checks are required.
        //
        if (Ladder::WithinLadder(ladder, collider)) {
            return true;
        }

        //
        //  Final checks to see if we are not within the ladder, but touching the top (and within the left/right
        //  bounds of the ladder.
        //
        if ((collider.y + collider.h) != (ladder.y - 1))
            return false;

        if ((collider.x < ladder.x) || ((collider.x + collider.w) > (ladder.x + ladder.w)))
            return false;

        return true;
    } // CanClimbDownLadder

    bool Ladder::CanClimbDownLadder(const std::list<SDL_Rect>& ladders, const SDL_Rect& collider) {
        for (auto it = ladders.begin(); it != ladders.end(); ++it) {
            if (CanClimbDownLadder(*it, collider)) {
                return true;
            }
        }

        return false;
    } // CanClimbDownLadder

}; // bpl::graphics::collider