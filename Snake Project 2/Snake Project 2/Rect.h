#pragma once
#include "SDL.h"
#include <memory>
#include <SDL_rect.h>
#include <stack>

struct Rect
{
private:

    std::stack<std::shared_ptr<SDL_Rect>> sdlRectangles;

    bool sdlEquals(const SDL_Rect& other) const;

public:

    int x, y;
    int w, h;

public:

    Rect() = default;
    Rect(const SDL_Rect& rect);

    bool operator==(const Rect& other) const;
    operator SDL_Rect() const;
    operator SDL_Rect*();
};

