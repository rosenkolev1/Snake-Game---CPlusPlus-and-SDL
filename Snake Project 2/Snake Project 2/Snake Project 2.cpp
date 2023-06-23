//// Snake Project 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
////
#include <iostream>
#include <windows.h>

#include "SDL.h"
#include "SDL_image.h"
#include "sdl2.h"
#include "GameUI.h"
#include "GameApp.h"

//Initialize the window, the renderer and the game sprites
int main(int argc, char* argv[])
{
    //Initialize the app with the window and the UI textures
    GameApp app = GameApp(true);

    //Start the main application/game loop
    app.startGameLoop();

    return 0;
}