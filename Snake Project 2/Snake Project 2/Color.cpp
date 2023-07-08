#include "Color.h"

Color::Color(const SDL_Color& color)
{
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
    this->a = color.a;
}

bool Color::operator==(const Color& other) const
{
    return this->r == other.r && this->g == other.g && this->b == other.b && this->a == other.a;
}

bool Color::sdlEquals(const SDL_Color& other) const
{
    return this->r == other.r && this->g == other.g && this->b == other.b && this->a == other.a;
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

Color::operator SDL_Color* ()
{
    if (!this->sdlColors.empty())
    {
        auto& mostRecent = this->sdlColors.top();

        if (this->sdlEquals(*mostRecent)) return mostRecent.get();
    }

    auto newColor = std::make_shared<SDL_Color>(SDL_Color
        {
            .r = r,
            .g = g,
            .b = b,
            .a = a
        });

    this->sdlColors.push(newColor);

    return newColor.get();
}
