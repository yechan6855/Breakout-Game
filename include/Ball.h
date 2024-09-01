#pragma once
#include "GameObject.h"
#include "Constants.h"

class Ball : public GameObject {
public:
    Ball();
    void move();
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getGlobalBounds() const;
    void reverseXVelocity();
    void reverseYVelocity();
    bool isOutOfBounds() const;
    sf::Vector2f getPosition() const { return shape.getPosition(); }
    void setVelocity(float x, float y) { velocity = sf::Vector2f(x, y); }
    void keepInBounds(float minX, float minY, float maxX, float maxY);

private:
    sf::CircleShape shape;
    sf::Vector2f velocity{-5.0f, -5.0f};
};