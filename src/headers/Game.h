#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <vector>

class ColliderComponent;

using namespace std;

class Game
{
public:
     Game();
     ~Game();

     void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

     void handleEvents();
     void update();
     void render();
     void clean();

     bool running() { return isRunning; }

     static SDL_Renderer *renderer;
     static SDL_Event event;
     static vector<ColliderComponent*> colliders;

private:
     SDL_Window *window;
     bool isRunning;
};