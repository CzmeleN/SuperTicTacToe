#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>
#include <memory>
#include "node.hpp"

class Container : public Node {
public:
    Container();
    void addNode(std::shared_ptr<Node> node);
    void removeNode(std::shared_ptr<Node> node);
    void render(SDL_Renderer* renderer) override;
    void update() override;
    void setVisible(bool visibility);
    bool isVisible() const;

    const std::vector<std::shared_ptr<Node>>& getChildren() const;

private:
    std::vector<std::shared_ptr<Node>> nodes;
    bool visible;
};

#endif
