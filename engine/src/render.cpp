#include "../include/render.hpp"
#include "../include/node.hpp"
#include "../include/container.hpp"
#include <memory>

void renderNode(SDL_Renderer* renderer, const std::shared_ptr<Node>& node) {
    node->render(renderer);

    if (auto container = std::dynamic_pointer_cast<Container>(node)) {
        for (const auto& child : container->getChildren()) {
            renderNode(renderer, child);
        }
    }
}
