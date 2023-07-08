#pragma once
#include "SDL.h"
#include <memory>
#include <stack>

struct Color
{
private:
    std::stack<std::shared_ptr<SDL_Color>> sdlColors;

    bool sdlEquals(const SDL_Color& other) const;

public:

    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;

    Color() = default;
    Color(const SDL_Color& color);

    bool operator==(const Color& other) const;
    operator SDL_Color() const;
    operator SDL_Color*();
};

