#pragma once
#include "SDL.h"
#include <memory>
#include <stack>
#include "SdlWrapper.h"

struct Color : public SdlWrapper<SDL_Color>
{
protected:
    bool sdlEquals(const SDL_Color& first, const SDL_Color& second) const override;

public:

    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;

    Color();
    Color(const SDL_Color& color);

    operator SDL_Color() const override;
};

