#pragma once

#include <memory>
#include <stack>
#include "SDL.h"

template <typename T>
struct SdlWrapper
{
protected:

    virtual bool sdlEquals(const T& first, const T& second) const = 0;
    bool sdlEquals(const T& other) const;

public:

    bool operator==(const SdlWrapper<T>& other) const;
    virtual operator T() const = 0;

    std::shared_ptr<T> sdl() const;
};

template <typename T>
bool SdlWrapper<T>::operator==(const SdlWrapper<T>& other) const
{
    return this->sdlEquals((T)*this, other);
}

template<typename T>
std::shared_ptr<T> SdlWrapper<T>::sdl() const
{
    auto newSdlObject = (T)*this;
    
    auto newSdlObjectPtr = std::make_shared<T>(newSdlObject);

    return newSdlObjectPtr;
}

template <typename T>
bool SdlWrapper<T>::sdlEquals(const T& other) const
{
    return this->sdlEquals((T)*this, other);
}

