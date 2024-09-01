#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "Constants.h"

// 게임의 다양한 상태를 나타내는 열거형
enum class GameState {
    MainMenu,
    Playing,
    GameOver,
    Options,
    LevelComplete
};

class Game {
public:
    Game();
    void run();

private:
    // 게임 로직 관련 함수들
    void processEvents();
    void update();
    void render();
    void checkCollisions();
    void resetGame();

    // 메뉴 관련 함수들
    void initializeMainMenu();
    void updateMainMenu();
    void renderMainMenu();
    void initializeOptions();
    void updateOptions();
    void renderOptions();
    void processMainMenuEvents(const sf::Event& event);
    void processOptionsEvents(const sf::Event& event);
    void processPlayingEvents(const sf::Event& event);
    void processGameOverEvents(const sf::Event& event);
    void processLevelCompleteEvents(const sf::Event& event);
    void executeMenuOption(int option);
    void executeOptionsOption(int option);

    // 유틸리티 함수
    sf::String toUtf8(const std::string& str);

    // SFML 관련 객체들
    sf::RenderWindow window;
    sf::Font font;

    // 게임 객체들
    Paddle paddle;
    std::vector<Ball> balls;  // 변경: 여러 개의 공을 저장하기 위해 vector 사용
    std::vector<Brick> bricks;

    // 게임 상태 변수들
    int score = 0;
    GameState gameState;
    bool allBricksDestroyed = false;

    // 텍스트 객체들
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::Text levelCompleteText;
    sf::Text continueText;
    sf::Text finalScoreText;

    // 메뉴 관련 변수들
    std::vector<sf::Text> menuItems;
    int selectedMenuItem = 0;
    std::vector<sf::Text> optionsItems;
    int selectedOptionsItem = 0;

    // 새로 추가된 부분: 난이도 설정
    Constants::Difficulty difficulty = Constants::Difficulty::EASY;

    std::string getDifficultyString() const;
};