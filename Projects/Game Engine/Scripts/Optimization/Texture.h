#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <unordered_map>
#include <string>

class Texture {
public:
	~Texture();
	SDL_Texture* loadTexture(const char* filename);
	static void draw(SDL_Texture* tex, SDL_FRect& src, SDL_FRect& dest, SDL_FlipMode flip, double angle);
	void clear();

private:
	std::unordered_map<std::string, SDL_Texture*> textureCache;
};