#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map *map;
Manager manager;
SDL_Event Game::event;

SDL_Renderer *Game::renderer = nullptr;

vector<ColliderComponent *> Game::colliders;

auto &player(manager.addEntity());
auto &wall(manager.addEntity());

auto &tile0(manager.addEntity());
auto &tile1(manager.addEntity());
auto &tile2(manager.addEntity());

Game::Game()
{
}
Game::~Game()
{
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
     int flags = 0 | SDL_WINDOW_RESIZABLE;
     if (fullscreen)
          flags = SDL_WINDOW_FULLSCREEN;

     if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
     {
          cout << "System Initialized!...." << endl;

          window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
          if (window)
          {
               cout << "Window Created!..." << endl;
          }

          renderer = SDL_CreateRenderer(window, -1, 0);
          if (renderer)
          {
               SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
               cout << "Renderer Created!..." << endl;
          }

          isRunning = true;
     }
     else
          isRunning = false;

     map = new Map();

     // esc implementation

     tile0.addComponent<TileComponent>(200, 100, 32, 32, 1);
     tile0.addComponent<ColliderComponent>("grass");

     player.addComponent<TransformComponent>();
     player.addComponent<SpriteComponent>("assets/player.png");
     player.addComponent<KeyBoardController>();
     player.addComponent<ColliderComponent>("player");

     wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
     wall.addComponent<SpriteComponent>("assets/dirt.jpg");
     wall.addComponent<ColliderComponent>("wall");
}

void Game::handleEvents()
{
     SDL_PollEvent(&event);

     switch (event.type)
     {
     case SDL_QUIT:
          isRunning = false;
          break;

     default:
          break;
     }
}

void Game::update()
{
     manager.refesh();
     manager.update();
     if (Collision::AABB(player.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider))
     {
          player.getComponent<TransformComponent>().velocity * -1;
     }
}

void Game::render()
{
     // need to add renderer stuff between Clear and Present
     SDL_RenderClear(renderer);
     //////

     map->DrawMap();
     manager.draw();

     /////
     SDL_RenderPresent(renderer);
}

void Game::clean()
{
     SDL_DestroyWindow(window);
     SDL_DestroyRenderer(renderer);
     SDL_Quit();

     cout << "Game cleaned!?!" << endl;
}