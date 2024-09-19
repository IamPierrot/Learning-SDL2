#pragma once

#include "Components.h"
#include "SDL2/SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component
{
private:
     TransformComponent *transform;
     SDL_Texture *texture;
     SDL_Rect srcRect, destRect;

     bool animated = false;
     int frames = 0;
     int delay = 100;

     std::map<const char*, Animation> animations;
     int animationIndex = 0;

public:
     SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;


     SpriteComponent() = default;
     SpriteComponent(const char *path)
     {
          setTexture(path);
     }
     SpriteComponent(const char *path,  bool isAnimated)
     {
          animated = isAnimated;

          Animation idle(0, 3, 100);
          Animation walk(1, 8, 200);

          animations.emplace("Idle", idle);
          animations.emplace("Walk", walk);
     
          Play("Idle");
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
          if (animated)
          {
               srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / delay ) % frames);
          }

          srcRect.y = animationIndex * transform->height;

          destRect.y = static_cast<int>(transform->position.y);
          destRect.x = static_cast<int>(transform->position.x);
          destRect.w = transform->width * transform->scale;
          destRect.h = transform->height * transform->scale;

     }
     void draw() override
     {
          TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
     }

     void Play(const char* animationName)
     {
          frames = animations[animationName].frames;
          animationIndex = animations[animationName].index;
          delay = animations[animationName].delay;
     }
};