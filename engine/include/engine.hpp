#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <string>
#include <vector>
#include <memory>
#include <SDL3/SDL.h>
#include "game_loader.hpp"
#include "asset_manager.hpp"
#include "data.hpp"
#include "events.hpp"
#include "container.hpp"

class Engine {
public:
    Engine(int width, int height);
    ~Engine();

    void loadStructure(const std::string& structureFile, const std::string& buttonsFile);
    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    AssetManager assetManager;
    EventManager eventManager;
    Data data;
    std::shared_ptr<Container> rootNode;
};

#endif
