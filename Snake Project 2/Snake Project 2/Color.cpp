#include "Color.h"

bool Color::sdlEquals(const SDL_Color& first, const SDL_Color& second) const
{
    return first.r == second.r && first.g == second.g && first.b == second.b && first.a == second.a;
}

Color::Color()
    :Color(SDL_Color {.r = 0, .g = 0, .b = 0, .a = 0})
{
}

Color::Color(const SDL_Color& color)
{
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
    this->a = color.a;
}

Color::operator SDL_Color() const
{
    return SDL_Color
    {
        .r = r,
        .g = g,
        .b = b,
        .a = a
    };
}
