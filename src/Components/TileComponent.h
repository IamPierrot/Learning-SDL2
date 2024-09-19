#pragma once

#include "ECS.h"
#include "SDL2/SDL.h"

class TileComponent : public Component
{
public:
     SDL_Texture *texture;
     SDL_Rect srcRect, destRect;

     TileComponent() = default;

     TileComponent(int srcX, int srcY, int xpos, int ypos, const char *path)
     {
          texture = TextureManager::LoadTexture(path);

          srcRect.x = srcX;
          srcRect.y = srcY;
          srcRect.w = srcRect.h = 32;

          destRect.x = xpos;
          destRect.y = ypos;
          destRect.h = destRect.w = 32;
     }

     void draw() override
     {
          TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
     }

     ~TileComponent()
     {
          SDL_DestroyTexture(texture);
     }
};
