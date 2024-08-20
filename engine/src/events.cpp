#include "../include/events.hpp"
#include "../include/node.hpp"
#include "../include/button.hpp"
#include "../include/container.hpp"
#include <memory>

EventManager::EventManager() : quitEvent(false) {}

void EventManager::handleEvent(const SDL_Event& event, std::shared_ptr<Node> rootNode) {
    switch (event.type) {
        case SDL_EVENT_QUIT:
            quitEvent = true;
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            handleMouseButtonDown(event, rootNode);
            break;
        default:
            break;
    }
}

void EventManager::handleMouseButtonDown(const SDL_Event& event, std::shared_ptr<Node> node) {
    if (!node->isVisible()) {
        return;
    }

    int mouseX = event.button.x;
    int mouseY = event.button.y;

    if (auto button = std::dynamic_pointer_cast<Button>(node)) {
        if (mouseX > button->getX() && mouseX < (button->getX() + button->getWidth()) &&
            mouseY > button->getY() && mouseY < (button->getY() + button->getHeight())) {
            button->click();
        }
    }

    if (auto container = std::dynamic_pointer_cast<Container>(node)) {
        for (const auto& child : container->getChildren()) {
            handleMouseButtonDown(event, child);
        }
    }
}

bool EventManager::isQuitEvent() const {
    return quitEvent;
}
