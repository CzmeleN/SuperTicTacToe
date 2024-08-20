#include "../include/data.hpp"

Data::Data() : width(800), height(600) {}

Data::Data(int width, int height) : width(width), height(height) {}

int Data::getWidth() const {
    return width;
}

int Data::getHeight() const {
    return height;
}

void Data::setResolution(int width, int height) {
    this->width = width;
    this->height = height;
}
