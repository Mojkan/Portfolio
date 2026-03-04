#include "Texture.h"
#include "Engine.h"
#include <unordered_map>
#include <string>
#include <iostream>

SDL_Texture* Texture::loadTexture(const char* filename)
{
    std::string key(filename);

    auto it = textureCache.find(key);
    if (it != textureCache.end())
    {
        return it->second;
    }

    SDL_Surface* tempSurface = IMG_Load(filename);
    if (!tempSurface) 
    {
        std::cerr << "Failed to load image " << filename << ": " << std::endl;
        return nullptr;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(Engine::instance().getRenderer().renderer, tempSurface);
    SDL_DestroySurface(tempSurface);

    if (!tex) 
    {
        std::cerr << "Failed to create texture from " << filename << ": " << SDL_GetError() << std::endl;
        return nullptr;
    }

    textureCache[key] = tex;
    return tex;
}

void Texture::draw(SDL_Texture* tex, SDL_FRect& src, SDL_FRect& dest, SDL_FlipMode flip, double angle)
{
    SDL_RenderTextureRotated(Engine::instance().getRenderer().renderer, tex, &src, &dest, angle, nullptr, flip);
}

void Texture::clear()
{
    for (auto& [_, tex] : textureCache)
    {
        SDL_DestroyTexture(tex);
    }
    textureCache.clear();
}

Texture::~Texture()
{
    clear();
}