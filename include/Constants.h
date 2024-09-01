#pragma once
#include <SFML/Graphics.hpp>

namespace Constants {
    const int WIDTH = 800;
    const int HEIGHT = 600;
    const int PADDLE_WIDTH = 100;
    const int PADDLE_HEIGHT = 20;
    const int BALL_RADIUS = 10;
    const int BRICK_WIDTH = 60;
    const int BRICK_HEIGHT = 20;
    const int BRICK_COLUMNS = 10;
    const int BRICK_ROWS = 4;
    const sf::Color MENU_TEXT_COLOR = sf::Color::White;
    const int MENU_TEXT_SIZE = 30;
    const float MENU_ITEM_SPACING = 50.0f;
    const float MAX_BOUNCE_ANGLE = 3.14159f / 12.0f;

    // 새로 추가된 부분: 난이도 설정을 위한 열거형
    enum class Difficulty {
        EASY,
        HARD
    };
}