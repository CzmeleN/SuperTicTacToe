#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>
#include <string>

// Base node class
class Node {
public:
    Node(const std::string& name) : name(name) {}
    virtual ~Node() = default;

    void addChild(std::shared_ptr<Node> child) {
        children.push_back(child);
    }

    virtual void update() = 0; // Pure virtual function

    std::string getName() const { return name; }

protected:
    std::string name;
    std::vector<std::shared_ptr<Node>> children;
};

#endif
