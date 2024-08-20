#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <SDL3/SDL.h>
#include <memory>

class Node;
class Button;

class EventManager {
public:
    EventManager();
    void handleEvent(const SDL_Event& event, std::shared_ptr<Node> rootNode);
    bool isQuitEvent() const;

private:
    void handleMouseButtonDown(const SDL_Event& event, std::shared_ptr<Node> node);
    bool quitEvent;
};

#endif
