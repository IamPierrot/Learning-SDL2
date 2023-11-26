#include "Game.h"

Game *game = nullptr;
int main(int argc, char *argv[])
{
     try
     {
          const int FPS = 60;
          const int frameDelay = 1000 / FPS;

          Uint32 frameStart;
          int frameTime;

          game = new Game();
          game->init("ThuongEm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

          while (game->running())
          {
               frameStart = SDL_GetTicks();

               game->handleEvents();
               game->update();
               game->render();

               frameTime = SDL_GetTicks() - frameStart;

               if (frameDelay > frameTime)
               {
                    SDL_Delay(frameDelay - frameTime);
               }
          }

          game->clean();
     }
     catch (const exception &error)
     {
          cerr << "There was an error: " << error.what() << endl;
          cerr << "There was an error in SDL2: " << SDL_GetError() << endl;
     }

     return 0;
}