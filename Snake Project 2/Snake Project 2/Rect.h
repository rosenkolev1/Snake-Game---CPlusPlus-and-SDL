#pragma once
#include "SDL.h"
#include <memory>
#include <SDL_rect.h>
#include <stack>
#include "SdlWrapper.h"

struct Rect : public SdlWrapper<SDL_Rect>
{
protected:

    bool sdlEquals(const SDL_Rect& first, const SDL_Rect& second) const override;

public:

    int x, y;
    int w, h;

    Rect();
    Rect(const SDL_Rect& rect);

    operator SDL_Rect() const override;
};

