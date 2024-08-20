#include "../include/container.hpp"
#include <algorithm>

Container::Container() : visible(true) {}

void Container::addNode(std::shared_ptr<Node> node) {
    nodes.push_back(node);
}

void Container::removeNode(std::shared_ptr<Node> node) {
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [&](const std::shared_ptr<Node>& n) { return n == node; }),
                nodes.end());
}

void Container::render(SDL_Renderer* renderer) {
    if (visible) {
        for (const auto& node : nodes) {
            node->render(renderer);
        }
    }
}

void Container::update() {
    if (visible) {
        for (const auto& node : nodes) {
            node->update();
        }
    }
}

void Container::setVisible(bool visibility) {
    visible = visibility;
}

bool Container::isVisible() const {
    return visible;
}

const std::vector<std::shared_ptr<Node>>& Container::getChildren() const {
    return nodes;
}
