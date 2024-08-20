#include "../include/button.hpp"

Button::Button(int x, int y, int w, int h, SDL_Texture* bgTexture, SDL_Texture* textTexture)
    : Node(x, y, w, h), bgTexture(bgTexture), textTexture(textTexture), onClickFunction(nullptr) {}

void Button::render(SDL_Renderer* renderer) {
    SDL_FRect dstRect = { static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height) };
    if (bgTexture) {
        SDL_RenderTexture(renderer, bgTexture, nullptr, &dstRect);
    }
    if (textTexture) {
        SDL_RenderTexture(renderer, textTexture, nullptr, &dstRect);
    }
}

void Button::update() {
}

void Button::setOnClick(std::function<void()> onClick) {
    onClickFunction = onClick;
}

bool Button::handleEvent(const SDL_Event& event) {
    int mouseX = event.button.x;
    int mouseY = event.button.y;

    if (mouseX > x && mouseX < (x + width) &&
        mouseY > y && mouseY < (y + height)) {
        click();
        return true;
    }
    return false;
}

void Button::click() {
    if (onClickFunction) {
        onClickFunction();
    }
}

void Button::setText(SDL_Texture* newTextTexture) {
    textTexture = newTextTexture;
}

void Button::setBackground(SDL_Texture* newBgTexture) {
    bgTexture = newBgTexture;
}
