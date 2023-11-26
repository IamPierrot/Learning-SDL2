#pragma once
#include "Game.h"

class GameObject
{
private:
     int xpos;
     int ypos;

     SDL_Texture *objTexture;
     SDL_Rect srcRect, destRect;

public:
     GameObject(const char *texturesheet, int x, int y);
     ~GameObject();

     void Update();
     void Render();


};
