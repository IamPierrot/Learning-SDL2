#pragma once

#include "Components.h"
#include "SDL2/SDL.h"
#include "TextureManager.h"

class SpriteComponent : public Component
{
private:
     TransformComponent *transform;
     SDL_Texture *texture;
     SDL_Rect srcRect, destRect;

public:
     SpriteComponent() = default;
     SpriteComponent(const char *path)
     {
          setTexture(path);
     }

     ~SpriteComponent()
     {
          SDL_DestroyTexture(texture);
     }

     void setTexture(const char *path)
     {
          texture = TextureManager::LoadTexture(path);
     }

     void init() override
     {
          transform = &entity->getComponent<TransformComponent>();

          srcRect.x = srcRect.y = 0;
          srcRect.w = transform->width; 
          srcRect.h = transform->height;
     }
     void update() override
     {
          destRect.y = static_cast<int>(transform->position.y);
          destRect.x = static_cast<int>(transform->position.x);
          destRect.w = transform->width * transform->scale;
          destRect.h = transform->height * transform->scale;

     }
     void draw() override
     {
          TextureManager::Draw(texture, srcRect, destRect);
     }
};