#ifndef DATA_HPP
#define DATA_HPP

#include "node.hpp"
#include <string>

class DataNode : public Node {
public:
    DataNode(const std::string& name) : Node(name) {}
    ~DataNode() override = default;

    void update() override {
        // TODO
    }

    void setResolution(int width, int height) {
        resolution = {width, height};
    }

    void setFullscreen(bool isFullscreen) {
        fullscreen = isFullscreen;
    }

    std::pair<int, int> getResolution() const {
        return resolution;
    }

    bool isFullscreen() const {
        return fullscreen;
    }

private:
    std::pair<int, int> resolution = {1920, 1080};
    bool fullscreen = false;
};

#endif
