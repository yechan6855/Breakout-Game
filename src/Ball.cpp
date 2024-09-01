#include "Ball.h"

Ball::Ball() {
    shape.setRadius(Constants::BALL_RADIUS);
    shape.setPosition(Constants::WIDTH / 2, Constants::HEIGHT / 2);
    shape.setFillColor(sf::Color::Red);
}

void Ball::move() {
    shape.move(velocity);
    if (shape.getPosition().x <= 0 || shape.getPosition().x + shape.getRadius() * 2 >= Constants::WIDTH)
        velocity.x = -velocity.x;
    if (shape.getPosition().y <= 0)
        velocity.y = -velocity.y;
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Ball::getGlobalBounds() const {
    return shape.getGlobalBounds();
}

void Ball::reverseXVelocity() {
    velocity.x = -velocity.x;
}

void Ball::reverseYVelocity() {
    velocity.y = -velocity.y;
}

bool Ball::isOutOfBounds() const {
    return shape.getPosition().y + shape.getRadius() * 2 > Constants::HEIGHT;
}

void Ball::keepInBounds(float minX, float minY, float maxX, float maxY) {
    sf::Vector2f position = shape.getPosition();

    if (position.x < minX) {
        position.x = minX;
        reverseXVelocity();
    } else if (position.x + 2 * Constants::BALL_RADIUS > maxX) {
        position.x = maxX - 2 * Constants::BALL_RADIUS;
        reverseXVelocity();
    }

    if (position.y < minY) {
        position.y = minY;
        reverseYVelocity();
    }
    // 공이 화면 아래로 나가는 것은 허용 (게임 오버 조건)

    shape.setPosition(position);
}