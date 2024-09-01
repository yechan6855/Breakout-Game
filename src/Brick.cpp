#include "Brick.h"

Brick::Brick(float x, float y) {
    shape.setSize(sf::Vector2f(Constants::BRICK_WIDTH, Constants::BRICK_HEIGHT));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Green);
}

void Brick::draw(sf::RenderWindow& window) {
    if (!destroyed) {
        window.draw(shape);
    }
}

sf::FloatRect Brick::getGlobalBounds() const {
    return shape.getGlobalBounds();
}

bool Brick::isDestroyed() const {
    return destroyed;
}

void Brick::destroy() {
    destroyed = true;
}