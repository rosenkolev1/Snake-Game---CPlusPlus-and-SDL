#include "Rect.h"

bool Rect::operator==(const Rect& other) const
{
    return this->x == other.x && this->y == other.y && this->w == other.w && this->h == other.h;
}

Rect::operator SDL_Rect() const
{
    return *this->sdlRect;
}

Rect::operator SDL_Rect* () const
{
    return this->sdlRect.get();
}
