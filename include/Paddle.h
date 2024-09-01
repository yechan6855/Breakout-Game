#pragma once
#include "GameObject.h"
#include "Constants.h"

class Paddle : public GameObject {
public:
    Paddle();
    void move(float dx);
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const { return shape.getPosition(); }
    sf::Vector2f getSize() const { return shape.getSize(); }

private:
    sf::RectangleShape shape;
    float speed = 10.0f;
};