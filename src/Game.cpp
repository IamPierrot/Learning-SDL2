#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

Manager manager;
SDL_Event Game::event;

SDL_Renderer *Game::renderer = nullptr;

vector<ColliderComponent *> Game::colliders;

auto &player(manager.addEntity());
auto &wall(manager.addEntity());

const char *mapFile = "";

enum groupLabels : std::size_t
{
     groupMap,
     groupPlayers,
     groupEnemies,
     groupColliders
};

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
          cout << "System Initialized!..." << endl;

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

     // esc implementation
     Map::LoadMap("assets/pxm16x16.map", 16, 16);

     player.addComponent<TransformComponent>(3);
     player.addComponent<SpriteComponent>("assets/player_anims.png", true);
     player.addComponent<KeyBoardController>();
     player.addComponent<ColliderComponent>("player");
     player.addGroup(groupPlayers);

     wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
     wall.addComponent<SpriteComponent>("assets/dirt.jpg");
     wall.addComponent<ColliderComponent>("wall");
     wall.addGroup(groupMap);
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
}

auto &tiles(manager.getGroup(groupMap));
auto &players(manager.getGroup(groupPlayers));
auto &enemies(manager.getGroup(groupEnemies));

void Game::render()
{
     #define DrawAll(list)           \
          for (auto &element : list) \
          {                          \
               element->draw();      \
          }
     // need to add renderer stuff between Clear and Present
     SDL_RenderClear(renderer);
     //////

     DrawAll(players);
     DrawAll(enemies);

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

void Game::AddTile(int srcX, int srcY, int xpos, int ypos)
{
     auto &tile(manager.addEntity());
     tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, mapFile);
     tile.addGroup(groupMap);
}