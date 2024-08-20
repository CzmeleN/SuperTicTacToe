#ifndef NODE_HPP
#define NODE_HPP

#include <SDL3/SDL.h>

class Node {
public:
    Node();
    Node(int x, int y, int w, int h);
    virtual ~Node() = default;

    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void update() = 0;

    bool isVisible() const { return visible; }

protected:
    int x, y;
    int width, height;
    bool visible;
};

#endif
