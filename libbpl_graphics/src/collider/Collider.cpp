//
// Created by Bradley Remedios on 10/27/24.
//
#include <SDL2/SDL.h>

#include <bpl/graphics/collider/Collider.h>

namespace bpl::graphics::collider {
    bool Collider::IsColliding(const SDL_Rect &rect1, const SDL_Rect &rect2) {
        //  If rect1 is right of rect 2, we are not colliding.
        if ((rect1.x + rect1.w) <= rect2.x) {
            return false;
        }

        // We aren't colliding if rect 1 is right of rect 2
        if ((rect2.x + rect2.w) <= rect1.x) {
            return false;
        }

        // Rect 1 is above Rect 2
        if ((rect1.y + rect1.h) <= rect2.y) {
            return false;
        }

        // Rect 2 is above Rect 1
        if ((rect2.y + rect2.h) <= rect1.y) {
            return false;
        }

        return true;
    }

    bool Collider::IsColliding(const std::list<SDL_Rect>& rect1, const std::list<SDL_Rect>& rect2) {

        for (const auto& it1 : rect1) {
            for (const auto& it2 : rect2) {
                if (IsColliding(it1, it2)) {
                    return true;
                }
            }
        }

        return false;
    } // IsColliding

    bool Collider::IsColliding(const SDL_Rect& rect1, const std::list<SDL_Rect>& rect2) {
        for (const auto& it2 : rect2) {
            if (IsColliding(rect1, it2)) {
                return true;
            }
        }

        return false;
    } // IsColliding

    bool Collider::InVerticalSpace(const SDL_Rect &rect1, const SDL_Rect &rect2) {
        // We are to the right, we are not in the vertical space.
        if (rect2.x >= (rect1.x + rect1.w)) {
            return false;
        }

        // We are to the left, we are not in the vertical space.
        if ((rect2.x + rect2.w) <= rect1.x) {
            return false;
        }

        return true;
    } // InVerticalSpace

    bool Collider::InVerticalSpace(const std::list<SDL_Rect>& rect1, const std::list<SDL_Rect>& obj) {
        for (const auto& it1 : rect1) {
            for (const auto& it2 : obj) {
                if (InVerticalSpace(it1, it2)) {
                    return true;
                }
            }
        }

        return false;
    } // InVerticalSpace

    bool Collider::InHorizontalSpace(const SDL_Rect &rect1, const SDL_Rect &rect2) {
        // We are below, we are not in the vertical space.
        if (rect2.y >= (rect1.y + rect1.h)) {
            return false;
        }

        // We are above, we are not in the vertical space.
        if ((rect2.y + rect2.h) <= rect1.y) {
            return false;
        }

        return true;
    } // InHorizontalSpace

    bool Collider::InHorizontalSpace(const std::list<SDL_Rect>& rect1, const std::list<SDL_Rect>& obj) {
        for (const auto& it1 : rect1) {
            for (const auto& it2 : obj) {
                if (InHorizontalSpace(it1, it2)) {
                    return true;
                }
            }
        }

        return false;
    } // InHorizontalSpace

    bool Collider::IsInBounds(const SDL_Rect &bounds, const SDL_Rect &rect) {
        // We need to ensure that our starting part is within the left bounds.
        if (rect.x < bounds.x) {
            return false;
        }

        if ((rect.x + rect.w) > (bounds.x + bounds.w)) {
            return false;
        }

        if (rect.y < bounds.y) {
            return false;
        }

        if (rect.y + rect.h > (bounds.y + bounds.h)) {
            return false;
        }
        return true;
    }

    bool Collider::OnSurface(const SDL_Rect& surface, const SDL_Rect& obj) {
        //
        //  If
        //      - our y position does not allow us to be on the surface our check is done.
        //      - We are right of the surface
        //      - We are left of the surface
        //
        if ((surface.y != (obj.y + obj.h)) ||
            (surface.x >= (obj.x + obj.w)) ||
            (obj.x >= (surface.x + surface.w))){

            return false;
        }

        return true;
    } // OnSurface
} // bpl::graphics::collider