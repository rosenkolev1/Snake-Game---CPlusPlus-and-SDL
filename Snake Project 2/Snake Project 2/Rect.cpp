#include "Rect.h"

bool Rect::sdlEquals(const SDL_Rect& first, const SDL_Rect& second) const
{
    return first.x == second.x && first.y == second.y && first.w == second.w && first.h == second.h;
}

Rect::Rect()
    :Rect(SDL_Rect{ .x = 0, .y = 0, .w = 0, .h = 0 })
{
}

Rect::Rect(const SDL_Rect& rect)
{
    this->x = rect.x;
    this->y = rect.y;
    this->w = rect.w;
    this->h = rect.h;
}

Rect::operator SDL_Rect() const
{
    return SDL_Rect
    {
            .x = x,
            .y = y,
            .w = w,
            .h = h
    };
}
