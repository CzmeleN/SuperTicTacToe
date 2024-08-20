#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "node.hpp"
#include <functional>

class Button : public Node {
public:
    Button(int x, int y, int w, int h, SDL_Texture* bgTexture, SDL_Texture* textTexture);

    void render(SDL_Renderer* renderer) override;
    void update() override;
    void setOnClick(std::function<void()> onClick);
    bool handleEvent(const SDL_Event& event);

    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    bool isVisible() const { return visible; }

    void click();
    void setText(SDL_Texture* newTextTexture);
    void setBackground(SDL_Texture* newBgTexture);

private:
    SDL_Texture* bgTexture;
    SDL_Texture* textTexture;
    std::function<void()> onClickFunction;
};

#endif
