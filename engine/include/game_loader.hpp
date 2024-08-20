#ifndef GAME_LOADER_HPP
#define GAME_LOADER_HPP

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include <memory>
#include "button.hpp"
#include "asset_manager.hpp"
#include <json/json.h>
#include <string>

class GameLoader {
public:
    GameLoader(SDL_Renderer* renderer, AssetManager& assetManager);
    std::vector<std::shared_ptr<Node>> loadGameStructure(const std::string& structureFile);

private:
    SDL_Renderer* renderer;
    AssetManager& assetManager;

    std::shared_ptr<Button> createButton(const Json::Value& nodeData);
    std::function<void()> getOnClickFunction(const std::string& functionName);

    void compileButtons(const std::string& sourceFile);
};

#endif
