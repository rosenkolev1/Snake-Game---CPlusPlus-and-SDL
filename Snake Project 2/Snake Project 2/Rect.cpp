#include "Rect.h"

bool Rect::sdlEquals(const SDL_Rect& other) const
{
    return this->x == other.x && this->y == other.y && this->w == other.w && this->h == other.h;
}

Rect::Rect(const SDL_Rect& rect)
{
    this->x = rect.x;
    this->y = rect.y;
    this->w = rect.w;
    this->h = rect.h;
}

bool Rect::operator==(const Rect& other) const
{
    return this->x == other.x && this->y == other.y && this->w == other.w && this->h == other.h;
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

Rect::operator SDL_Rect*()
{
    if (!this->sdlRectangles.empty())
    {
        auto& mostRecent = this->sdlRectangles.top();

        if (this->sdlEquals(*mostRecent)) return mostRecent.get();
    }  

    auto newRect = std::make_shared<SDL_Rect>(SDL_Rect
        {
            .x = x,
            .y = y,
            .w = w,
            .h = h
        });

    this->sdlRectangles.push(newRect);

    return newRect.get();
}
