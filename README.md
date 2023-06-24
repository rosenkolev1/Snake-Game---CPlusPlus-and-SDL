# Snake Game - CPlusPlus and SDL
 The typical snake game created in c++ with SDL library

# Snake Game - Release

You can find the latest release [here](https://github.com/rosenkolev1/Snake-Game---CPlusPlus-and-SDL/releases).

The release should be compilable and runnable right out of the box from within Visual Studio. You can open the Visual Studio project and run the app from there.  

# Some Notes

1) Microsoft Visual Studio doesn't easily give you the option to create a new folder in your c++ project. Instead, they use [filters](https://learn.microsoft.com/en-us/cpp/build/reference/vcxproj-filters-files?view=msvc-170). So I decided to use filters as well, hence all of the non-external library files are technically inside a single folder.

2) Visual Studio c++ is also really annoying when it comes to separating the source code into different projects inside the same solution. It requires you to constantly configure the project settings to tell the compiler where to search for compiled obj files and for which obj files to search. It is annoying and not worth the effort, so I just used VS filters instead.

3) The repo does not contain the SDL libraries' include headers that are used and needed for the linker during compilation. It does contain the ```doctest.h``` header for the Doctest library, however, and also .lib and .dll files for the SDL libraries.

4) The full release contains the whole Visual Studio project and the SDL libraries in full, with their include headers.

# Libraries Used

1) SDL 2.0
2) SDL Image 2.0 - extension library for SDL 2.0, allows easier work with images of various formats and types. Used only once inside the whole project, but nevertheless, it was worth it.
3) SDL TTF 2.0 - extension library for SDL 2.0, gives you rich options for rendering text on the screen.
4) Doctest - Unit Tests

# Project Structure

1) App 'folder' - Contains only these files which need not be referenced in the UI 'folder'. I.e. they are not required for rendering, only for managing the overall game logic.

2) Common 'folder' - Contains files which are needed in both the App and UI 'folders'. They are used to manage and change the game state in App, after which the game state is then sent to UI where it is rendered accordingly on the screen.

3) UI 'folder' - Contains only these files which manage what is rendered on the screen. They do not affect the game state directly.

4) Test 'folder' - Contains the unit testing files. Only the game logic is tested, the UI is not (because testing the UI function would make these tests UI tests instead of unit tests, and also testing the UI would be very cumbersome).

# Functionality - In-Game

1) You can move the snake along the grid with the arrow keys or with WASD.
2) When you collect an apple, your snake grows from its tail.
3) You cannot go out of bounds. If you try to, you get a game over.
4) You cannot crash into yourself. If you do, you get a game over.
5) Once in a game over, you can either press ```r``` to reset the room, or wait 5 seconds for the application to auto exit.
6) There are ```Time Elapsed``` and ```Apples Collected``` at the top of the screen. They get updated accordingly.
7) Upon a game reset, time elapsed and apples collected texts also get reset.
8) When the snake collects an apple, a new apple spawns on the grid randomly. The apple cannot spawn right in front of the snake's head, unless it has no other legal positions.
9) When the snake collects an apple, it starts moving slightly faster each time, up to a certain threshold.
10) Upon a game reset, the speed of the snake is reset back to its default speed.
11) If the snake, after devouring an apple, takes up the entire grid, then the game is won.
12) Once you have won a game, you can either press r to reset the room, or wait 5 seconds for the application to auto exit.

# Functionality - Outside-Game

1) The ```GlobalParams``` class controls many important game parameters. You can change these parameters by changing the default constructor or modifying the ```GlobalParams``` class after it has been created with the many setter functions. It uses the option/builder pattern, i.e. all the setters return the object itself, so they can be chained. The ```GlobalParams``` object is passed to the ```GameApp``` object, which controls/starts the whole game. Changing the ```GlobalParams``` object inside the ```Snake Project 2.cpp``` file inside the ```startMainApp()``` function will change the game.

2) For example, there are 2 lines ```params.disableAutoPlay()``` and ```params.enableAutoPlay()```. They control a flag inside ```GlobalParams``` called ```autoPlay```. If ```autoPlay``` is true, then the game plays itself until it is beaten.

3) The way the game auto plays itself depends on the dimensions of the grid. If the grid contains an even number of rows, then it uses a predetermined Hamiltonian Cycle to play through the game without dying and get all apples. If the grid contains an odd number of rows, but an even number of cols, it uses a different predetermined Hamiltonian Cycle. If neither the rows, nor the cols are even, then the game prints an error on the console and exits.

4) If the game is auto playing, then there is no increase in the speed of the snake upon devouring an apple. The speed of the snake is constant throughout and it can be set from ```GlobalParams```.

5) If the auto play wins the game, then you can restart the game with the ```r``` button. This will cause auto play to start again. If you want to disable auto play, then you have to quit the game entirely and disable auto play before starting again.  

6) The aforementioned grid dimensions can also be changed from ```GlobalParams```. Changing the dimensions of the grid affects the sizes of the cells and the sprites of the game. You can also change how far the grid is offset on the screen from the left, right, top and bottom borders. You can change the screen title and dimensions as well. You can change how fast the snake moves by default, how much quicker it gets per eating a single apple, what the speed cap is. You can change the default spawn positions of the apple and the snake, you can change the default length of the snake (as long as it is within the grid boundaries). You can change the different UI text, like the game over text or the ```Time Elapsed``` text. And in general, there are many things inside ```GlobalParams```.
  
7) More info in the ```GlobalParams``` header file for what the different parameters do.

# More detailed look at the classes/files

1) Snake Project 2.cpp - Contains 3 functions. One is the main function. Another function starts the unit tests (the unit tests finish before the game actually starts, their result is printed to the console). The last function start the actual game. In this function, we can choose to enable or disable the autoplay feature via ```params.disableAutoPlay()``` and ```params.enableAutoPlay()```. The ```GlobalParam``` object, which gives us many important game parameters, is created there and passed to the ```GameApp``` object.

2) GameApp - Contains many functions for manipulating the game state. It can move the snake, determining if it is game over or game won, retrieve tiles based on tile coordinates, create hamiltonian cycles, reset the game state, parse user input... It also calls the ```GameUI::renderTick(GameState state)``` function, which tells the renderer to render the game based on its current state.

3) GameState - A model object which contains the current game state. It does not contain the ```GlobalParams``` directly, but has access to them. The ```GlobalParams``` are meant to not be changed once set (but ```GlobalParams``` member of ```GameState``` cannot be const because that causes big problem with trying to copy the model state and also other things...). The game state however, can be changed all we want. Of course, it is the ```GameApp``` that changes the game state as necessary. The game state is passed to the ```GameUI``` via the ```GameUI::renderTick(GameState state)``` function, where the renderer renders things on the screen based on what is inside the game state (and also based on the ```GlobalParams```, of course).

4) GameUI - It is responsible for loading all the needed textures and rendering them on the screen, using the ```GameState``` object and ```GlobalParams```.

5) Snake - A rather simple object. Contains its current moving direction and a list of the positions of all of its tiles. The first tile pos in the list is the head. The second-to-last tile pos is the tail. The last tile pos is an invisible tile that follows the tail of the snake and becomes visible when the snake devours an apple, at which point a new invisible tile pos is added at the end of the list. The invisible tile is used to determine where the new snake tile should spawn once it eats an apple. At the very beginning of the game, the invisible tile pos and the tail pos are initialized as the same. There is a special check for when that happens inside ```GameApp```, as well as special edge case check for when the snake devours an apple immediately(on its first move) right after the game has started, which determines what happens with the invisible tile and the tail.

6) Tile - object representing a tile on the grid. Each tile stores a lot of information about itself: ```isApple```, ```ìsSnake``` determine if the tile contains an apple or a snake bodypart, ```tilePos``` is the position of the tile within the grid, ```snakeSprite``` is the current snake bodypart sprite that should be rendered on top of the tile. If the tile's ```isSnake``` is false, then the bodypart is not rendered, regardless of its value. However, I've made it so that the ```isSnake``` and the ```snakeSprite``` values never differ (that is, if the ```snakeSprite``` is None, then ```isSnake``` is False and vice-versa).

7) SnakeSprite - enum representing the bodypart of the snake that should be rendered. The ```GameUI``` contains a ```SNAKE_SPRITE_TO_TEXTURE_MAP``` map, where each ```SnakeSprite``` value corresponds to a given snake sprite. The snake sprites are taken from the tileset png image in the Images folder.

8) TilePos - contains the position of a tile in grid coordinates where a single unit is the width of the grid in pixels

9) ScreenPos - contains the position of a pixel on the screen. The difference between ```TilePos``` and ```ScreenPos``` is mostly semantic.

10) Rect - contains the coordinates of the top-left corner of a tile in pixels and the width and height of the tile in pixels. Also contains some extra casting conversions to ```SDL_Rect*```, as well as a ```shared_ptr to SDL_Rect*```. The reasons for these is way too complicated to explain in text. It' also 5:13 in the morning and I am tired :). In essence, this class acts as a wrapper for ```SDL_Rect``` that can also be compared (has ```operator==``` defined).

11) Color - contains color values in rgba. Same thing as ```Rect``` in the sense that it is a comparable wrapper for ```SDL_Color```.

12) IGameUI - an interface for ```GameUI```. It is needed because I had to create a stub of ```GameUI``` in my unit tests and feed it to ```GameApp``` so I could test ```GameApp``` properly. Also, dependency injection principle is cool.

13) Tests_GameUI_Stub - a stub of ```GameUI``` for testing purposes so we can initialize ```GameApp``` without creating an actual screen or loading the library. Does nothing. Its entire purpose is to be fed to ```GameApp```.

14) Tests_Util - contains a function which creates a ```GlobalParam``` for use in tests.

15) Tests_{name of class here} - contains test cases for the different classes

16) MoveDir - enum, contains the direction in which the snake moves.

17) sdlh2.h - Originally taken from [here](https://github.com/xyproto/sdl2-examples/blob/main/include/sdl2.h). Contains various function which return unique pointers to SLD objects which are created with the appropriate SDL creating functions and parameters and destroyed with the appropriate SDL destroying function. Saves us the trouble of having to manually delete the SDL resources when the go out of scope. Of course, I refactor the file slightly and then also extended its functionality by adding support for other types like fonts etc...
   
# Some pictures
![Photo 1](https://github.com/rosenkolev1/Snake-Game---CPlusPlus-and-SDL/assets/50500415/a5bfc39c-d3e6-4bc1-af37-ca2c58086339)

![Game over photo](https://github.com/rosenkolev1/Snake-Game---CPlusPlus-and-SDL/assets/50500415/8e41345c-aa2a-47c7-a501-b0e6bad33233)

![Game won photo](https://github.com/rosenkolev1/Snake-Game---CPlusPlus-and-SDL/assets/50500415/d8fe1273-6d91-4305-9a4c-4782d263ffc3)
