#include "../include/game_loader.hpp"
#include <fstream>
#include <dlfcn.h>
#include <cstdlib>
#include <iostream>

GameLoader::GameLoader(SDL_Renderer* renderer, AssetManager& assetManager)
    : renderer(renderer), assetManager(assetManager) {}

std::vector<std::shared_ptr<Node>> GameLoader::loadGameStructure(const std::string& structureFile) {
    std::vector<std::shared_ptr<Node>> nodes;

    std::ifstream file(structureFile);
    Json::Value root;
    file >> root;

    compileButtons("src/buttons.cpp");

    for (const auto& nodeData : root["nodes"]) {
        if (nodeData["type"].asString() == "Button") {
            nodes.push_back(createButton(nodeData));
        }
    }

    return nodes;
}

std::shared_ptr<Button> GameLoader::createButton(const Json::Value& nodeData) {
    int x = nodeData["x"].asInt();
    int y = nodeData["y"].asInt();
    int width = nodeData["width"].asInt();
    int height = nodeData["height"].asInt();

    SDL_Texture* bgTexture = assetManager.createBackgroundTexture(renderer, nodeData["background"].asString());

    TTF_Font* font = TTF_OpenFont(nodeData["font"].asString().c_str(), nodeData["font_size"].asInt());
    if (font == nullptr) {
        std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return nullptr;
    }

    SDL_Color color = {
        static_cast<Uint8>(nodeData["text_color"][0].asInt()),
        static_cast<Uint8>(nodeData["text_color"][1].asInt()),
        static_cast<Uint8>(nodeData["text_color"][2].asInt()),
        static_cast<Uint8>(nodeData["text_color"][3].asInt())
    };

    SDL_Texture* textTexture = assetManager.createTextTexture(renderer, font, nodeData["text"].asString(), color);
    if (textTexture == nullptr) {
        std::cerr << "Failed to create text texture! SDL Error: " << SDL_GetError() << std::endl;
        TTF_CloseFont(font);
        return nullptr;
    }

    auto button = std::make_shared<Button>(x, y, width, height, bgTexture, textTexture);

    std::function<void()> onClick = getOnClickFunction(nodeData["onClick"].asString());
    button->setOnClick(onClick);

    TTF_CloseFont(font);

    return button;
}

std::function<void()> GameLoader::getOnClickFunction(const std::string& functionName) {
    typedef void (*FunctionType)();
    FunctionType func = reinterpret_cast<FunctionType>(dlsym(RTLD_DEFAULT, functionName.c_str()));
    if (!func) {
        SDL_Log("Failed to load function: %s", dlerror());
        return []() {};
    }
    return [func]() { func(); };
}

void GameLoader::compileButtons(const std::string& sourceFile) {
    std::string command = "g++ -shared -o libbuttons.so " + sourceFile + " -fPIC -lSDL3";
    int result = system(command.c_str());
    if (result != 0) {
        throw std::runtime_error("Failed to compile buttons source file.");
    }

    if (!dlopen("./libbuttons.so", RTLD_LAZY | RTLD_GLOBAL)) {
        throw std::runtime_error("Failed to load compiled buttons library.");
    }
}
