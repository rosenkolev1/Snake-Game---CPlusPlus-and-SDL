//// Snake Project 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
////
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include <iostream>
#include <windows.h>

#include "SDL.h"
#include "SDL_image.h"
#include "sdl2.h"
#include "GameUI.h"
#include "GameApp.h"

void startMainApp()
{
    //Initialize the global parameters for the app
    GlobalParams params = GlobalParams();

    params.disableAutoPlay();
    //params.setDefaultTickSpeed(1);
    //params.enableAutoPlay();

    //Initialize the app with the window and the UI textures
    GameApp app = GameApp(params);

    //Start the main application/game loop
    app.startGameLoop();
}

int startUnitTests(int argc, char* argv[])
{
    doctest::Context context;

    // !!! THIS IS JUST AN EXAMPLE SHOWING HOW DEFAULTS/OVERRIDES ARE SET !!!

    // defaults
    context.addFilter("test-case-exclude", "*math*"); // exclude test cases with "math" in their name
    context.setOption("abort-after", 5);              // stop test execution after 5 failed assertions
    context.setOption("order-by", "name");            // sort the test cases by their name

    context.applyCommandLine(argc, argv);

    // overrides
    context.setOption("no-breaks", true);             // don't break in the debugger when assertions fail

    int res = context.run(); // run

    if (context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
        return res;          // propagate the result of the tests
}

//Initialize the window, the renderer and the game sprites
int main(int argc, char* argv[])
{
    int testsReturn = startUnitTests(argc, argv);

    // your program - if the testing framework is integrated in your production code
    startMainApp();

    return testsReturn;
}