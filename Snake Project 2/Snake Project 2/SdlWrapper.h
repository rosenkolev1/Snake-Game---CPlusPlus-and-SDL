#pragma once

#include <memory>
#include <stack>
#include "SDL.h"

template <typename T>
struct SdlWrapper
{
protected:
    std::stack<std::shared_ptr<T>> sdlObjects = std::stack<std::shared_ptr<T>>();

    virtual bool sdlEquals(const T& first, const T& second) const = 0;
    bool sdlEquals(const T& other) const;

public:

    bool operator==(const SdlWrapper<T>& other) const;
    virtual operator T() const = 0;
    operator T* ();
};

template <typename T>
bool SdlWrapper<T>::operator==(const SdlWrapper<T>& other) const
{
    return this->sdlEquals((T)*this, other);
}

template <typename T>
bool SdlWrapper<T>::sdlEquals(const T& other) const
{
    return this->sdlEquals((T)*this, other);
}

template <typename T>
SdlWrapper<T>::operator T* ()
{
    auto newSdlObject = (T)*this;

    auto newSdlObjectPtr = std::make_shared<T>(newSdlObject);

    this->sdlObjects.push(newSdlObjectPtr);

    return newSdlObjectPtr.get();
}

