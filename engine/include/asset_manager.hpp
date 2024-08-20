#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <string>

class AssetManager {
public:
    SDL_Texture* createBackgroundTexture(SDL_Renderer* renderer, const std::string& filePath);
    SDL_Texture* createTextTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color);
    SDL_Texture* resizeTexture(SDL_Renderer* renderer, SDL_Texture* texture, int width, int height);
};

#endif
