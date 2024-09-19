#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include "math.h"

class KeyBoardController : public Component
{
public:
     TransformComponent *transform;
     SpriteComponent *sprite;

     void init() override
     {
          transform = &entity->getComponent<TransformComponent>();
          sprite = &entity->getComponent<SpriteComponent>();
     }

     void update() override
     {
          if (Game::event.type == SDL_KEYDOWN)
          {
               int key = Game::event.key.keysym.sym;
               switch (key)
               {
               case SDLK_w:
                    transform->velocity.y = -1;
                    sprite->Play("Walk");
                    break;
               case SDLK_a:
                    transform->velocity.x = -1;
                    sprite->Play("Walk");
                    sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                    break;
               case SDLK_d:
                    transform->velocity.x = 1;
                    sprite->Play("Walk");
                    break;
               case SDLK_s:
                    transform->velocity.y = 1;
                    sprite->Play("Walk");
                    break;

               default:
                    break;
               }
          }

          if (Game::event.type == SDL_KEYUP)
          {
               int key = Game::event.key.keysym.sym;
               switch (key)
               {
               case SDLK_w:
                    transform->velocity.y = 0;
                    sprite->Play("Idle");
                    break;
               case SDLK_a:
                    transform->velocity.x = 0;
                    sprite->Play("Idle");
                    sprite->spriteFlip = SDL_FLIP_NONE;
                    break;
               case SDLK_d:
                    transform->velocity.x = 0;
                    sprite->Play("Idle");
                    break;
               case SDLK_s:
                    sprite->Play("Idle");
                    transform->velocity.y = 0;
                    break;

               default:
                    break;
               }
          }
     }
};