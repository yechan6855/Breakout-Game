#include "Paddle.h"

Paddle::Paddle() {
    shape.setSize(sf::Vector2f(Constants::PADDLE_WIDTH, Constants::PADDLE_HEIGHT));
    shape.setPosition(Constants::WIDTH / 2 - Constants::PADDLE_WIDTH / 2, Constants::HEIGHT - 50);
    shape.setFillColor(sf::Color::White);
}

void Paddle::move(float dx) {
    shape.move(dx * speed, 0);
    if (shape.getPosition().x < 0) shape.setPosition(0, shape.getPosition().y);
    if (shape.getPosition().x + shape.getSize().x > Constants::WIDTH)
        shape.setPosition(Constants::WIDTH - shape.getSize().x, shape.getPosition().y);
}

void Paddle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Paddle::getGlobalBounds() const {
    return shape.getGlobalBounds();
}