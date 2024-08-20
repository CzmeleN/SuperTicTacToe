#ifndef RENDER_HPP
#define RENDER_HPP

#include "node.hpp"
#include <SDL3/SDL.h>
#include <memory>

void renderNode(SDL_Renderer* renderer, const std::shared_ptr<Node>& node);

#endif // RENDER_HPP
