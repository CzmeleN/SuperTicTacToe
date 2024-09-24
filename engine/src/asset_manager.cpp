#include "../include/asset_manager.hpp"

SDL_Texture* AssetManager::createBackgroundTexture(SDL_Renderer* renderer, const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        SDL_Log("Unable to load image %s: %s", filePath.c_str(), SDL_GetError());
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    return texture;
}

SDL_Texture* AssetManager::createTextTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);
    return textTexture;
}

SDL_Texture* AssetManager::resizeTexture(SDL_Renderer* renderer, SDL_Texture* texture, int width, int height) {
    SDL_Texture* resizedTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetRenderTarget(renderer, resizedTexture);
    SDL_RenderTexture(renderer, texture, nullptr, nullptr);
    SDL_SetRenderTarget(renderer, nullptr);
    return resizedTexture;
}
