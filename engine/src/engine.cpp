#include "../include/engine.hpp"
#include <stdexcept>
#include <iostream>

Engine::Engine(int width, int height) : data(width, height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Failed to initialize SDL");
    }

    window = SDL_CreateWindow("Super TicTacToe", width, height, SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Failed to create SDL Window");
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Failed to create SDL Renderer");
    }

    rootNode = std::make_shared<Container>();
}

Engine::~Engine() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Engine::loadStructure(const std::string& structureFile, const std::string& buttonsFile) {
    GameLoader loader(renderer, assetManager);
    auto nodes = loader.loadGameStructure(structureFile);
    for (const auto& node : nodes) {
        rootNode->addNode(node);
    }
}

void Engine::run() {
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            eventManager.handleEvent(event, rootNode);
            if (eventManager.isQuitEvent()) {
                running = false;
            }
        }

        rootNode->update();

        SDL_RenderClear(renderer);
        rootNode->render(renderer);
        SDL_RenderPresent(renderer);
    }
}
