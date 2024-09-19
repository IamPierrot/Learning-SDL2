#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(const char *texture)
{
     SDL_Surface *tempSurface = IMG_Load(texture);
     SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
     SDL_FreeSurface(tempSurface);

     return tex;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest)
{
     SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
     double angle = static_cast<double>(0);

     SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, angle, NULL, flip);
}