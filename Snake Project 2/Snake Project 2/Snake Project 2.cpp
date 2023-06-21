//// Snake Project 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
////
#include <iostream>
#include <windows.h>

#include "SDL.h"
#include "SDL_image.h"
#include "sdl2.h"
#include "GameUI.h"

//Initialize the window, the renderer and the game sprites
int main(int argc, char* argv[])
{
    //Memory leak test
    /*for (int i = 0; i < 100; i++) {
        GameUI gameUI = GameUI();
    }*/

    GameUI gameUI = GameUI();

    if (!gameUI.isValid()) 
    {
        return 0;
    }

    gameUI.startGameRender();

    return 0;
}