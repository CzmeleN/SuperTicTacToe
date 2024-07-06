#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "node.hpp"

// Derived from Node, for organization of game objects,
// etc. Main Node -> Menu -> Buttons -> button_start | button_exit
class Container : public Node {
public:
    Container(const std::string& name) : Node(name) {}
    ~Container() override = default;

    void update() override {
        for (auto& child : children) {
            child->update();
        }
    }

    void addElement(std::shared_ptr<Node> element) {
        addChild(element);
    }
};

#endif
