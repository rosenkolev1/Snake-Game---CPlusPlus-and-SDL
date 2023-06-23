#pragma once
#include "SDL.h"
#include <memory>

struct Color
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;

    std::shared_ptr<SDL_Color> sdlColor = std::make_shared<SDL_Color>(SDL_Color
        {
            .r = r,
            .g = g,
            .b = b,
            .a = a
        });

public:

    bool operator==(const Color& other) const;
    operator SDL_Color() const;
    operator SDL_Color* () const;
};

