#pragma once
#include "SDL.h"
#include <memory>

struct Rect
{
    int x, y;
    int w, h;

    std::shared_ptr<SDL_Rect> sdlRect = std::make_shared<SDL_Rect>( SDL_Rect
        {
            .x = x,
            .y = y,
            .w = w,
            .h = h
        });

public:

    bool operator==(const Rect& other) const;
    operator SDL_Rect() const;
    operator SDL_Rect*() const;
};

