#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>
#include "node.hpp"

class Engine {
public:
    Engine() = default;
    ~Engine() = default;

    void run() {
        if (root) {
            root->update();
        }
    }

    void setRoot(std::shared_ptr<Node> rootNode) {
        root = rootNode;
    }

private:
    std::shared_ptr<Node> root;
};

#endif
