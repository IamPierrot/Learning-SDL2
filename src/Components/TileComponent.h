#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL2/SDL.h"

class TileComponent : public Component
{
public:
     TransformComponent *transform;
     SpriteComponent *sprite;

     SDL_Rect tileRect;
     int tileId;
     const char *path;

     TileComponent() = default;

     TileComponent(int x, int y, int h, int w, int id)
     {
          tileRect.x = x;
          tileRect.y = y;
          tileRect.w = w;
          tileRect.h = h;

          tileId = id;

          switch (tileId)
          {
          case 0:
               path = "assets/water.jpg";
               break;
          case 1:
               path = "assets/dirt.jpg";
               break;
          case 2:
               path = "assets/grass.png";
               break;

          default:
               break;
          }
     }

     void init() override
     {
          entity->addComponent<TransformComponent>(static_cast<float>(tileRect.x), static_cast<float>(tileRect.y), tileRect.w, tileRect.h, 1);
          transform = &entity->getComponent<TransformComponent>();

          entity->addComponent<SpriteComponent>(path);
          sprite = &entity->getComponent<SpriteComponent>();

     }

};
