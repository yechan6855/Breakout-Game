#pragma once
#include "GameObject.h"
#include "Constants.h"

class Brick : public GameObject {
public:
    Brick(float x, float y);
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getGlobalBounds() const;
    bool isDestroyed() const;
    void destroy();

private:
    sf::RectangleShape shape;
    bool destroyed = false;
};