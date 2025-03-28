/// \file
/// main.cpp

#include "UI.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include "pacman.hpp"
#include "Game.hpp"
#include <iostream>
#include "Ghosts.hpp"

/// Callback function to update the game state.
///
/// This function is called by an SDL timer at regular intervals.
/// Note that this callback may happen on a different thread than the main thread.
/// You therefore have to be careful in avoiding data races. For example, you
/// should use mutexes to access shared data.
/// Read the documentation of SDL_AddTimer for more information and for tips
/// regarding multithreading issues.
Uint32 gameUpdate(Uint32 interval, void *param)
{

    Game *state = static_cast<Game *>(param);
    state->update();
    // std::cout << "Number of objects:" << (state->getObjectList()).size() << std::endl;
    // state->printMap();
    // std::cout << "--------------------------------------------------------------------------------" << std::endl;
    // std::cout << "--------------------------------------------------------------------------------" << std::endl;
    return interval;
}

/// Program entry point.
int main(int /*argc*/, char ** /*argv*/)
{
    std::vector<std::vector<int>> map = {{
#include "board.def"
    }};

    std::vector<std::vector<int>> ghostMap = {{
#include "board.def"
    }};

    // Create a new ui object
    Game game(map);
    UI ui(game.getMap()); // <-- use map from your game objects.

    // Start timer for game update, call this function every 100 ms.
    SDL_TimerID timer_id =
        SDL_AddTimer(200, gameUpdate, static_cast<void *>(&game));

    // Example object, this can be removed later
    game.addDots();

    Pacman *pacman = game.getPacman();

    // SOME TESTING

    // Call game init code here

    bool quit = false;

    while (!quit)
    {
        // set timeout to limit frame rate
        Uint32 timeout = SDL_GetTicks() + 20;

        // Handle the input
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            // Quit button.
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            // All keydown events
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_LEFT: // YOUR CODE HERE
                    pacman->setDir(LEFT);

                    break;
                case SDLK_RIGHT: // YOUR CODE HERE
                    pacman->setDir(RIGHT);

                    break;
                case SDLK_UP: // YOUR CODE HERE
                    pacman->setDir(UP);

                    break;
                case SDLK_DOWN: // YOUR CODE HERE
                    pacman->setDir(DOWN);

                    break;
                case SDLK_ESCAPE:
                    game.setQuit(true);
                    break;
                }
            }
        }

        // Set the score
        // <-- Pass correct value to the setter

        // Set the amount of lives
        ui.setLives(game.getLives()); // <-- Pass correct value to the setter
        quit = game.getQuit();
        // Render the scene
        // std::vector<GameObjectStruct&> objects = {*pacman};
        // std::vector<GameObjectStruct *> objects = game.getObjectList();
        //  ^-- Your code should provide this vector somehow (e.g.
        //  game->getStructs())

        std::vector<GameObjectStruct> objects;
        for (auto *obj : game.getObjectList())
        {
            if (obj)
            {
                // Check for null pointers

                objects.push_back(*obj); // Dereference pointer and copy object
            }
        }
        ui.setScore(game.getScore());
        ui.update(objects);

        while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout))
        {
            // ... do work until timeout has elapsed
        }
    }

    SDL_RemoveTimer(timer_id);

    return 0;
}
