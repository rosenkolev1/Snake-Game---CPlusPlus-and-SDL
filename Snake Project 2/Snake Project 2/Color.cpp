#include "Color.h"

bool Color::operator==(const Color& other) const
{
    return this->r == other.r && this->g == other.g && this->b == other.b && this->a == other.a;
}

Color::operator SDL_Color() const
{
    return *this->sdlColor;
}

Color::operator SDL_Color* () const
{
    return this->sdlColor.get();
}
