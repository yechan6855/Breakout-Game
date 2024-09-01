#include "Game.h"
#include <iostream>
#include <locale>
#include <codecvt>

Game::Game() : window(sf::VideoMode(Constants::WIDTH, Constants::HEIGHT), "Brick Breaker") {
    window.setFramerateLimit(60);

    // 폰트 로드
    if (!font.loadFromFile("PretendardVariable.ttf")) {
        std::cerr << "Error loading font\n";
        exit(1);
    }

    // 텍스트 객체 초기화
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString(toUtf8("게임 오버! R키를 눌러 재시작"));
    gameOverText.setPosition(Constants::WIDTH / 2 - gameOverText.getGlobalBounds().width / 2,
                             Constants::HEIGHT / 2 - gameOverText.getGlobalBounds().height / 2);

    levelCompleteText.setFont(font);
    levelCompleteText.setCharacterSize(32);
    levelCompleteText.setFillColor(sf::Color::White);
    levelCompleteText.setString(toUtf8("계속하시겠습니까?"));
    levelCompleteText.setPosition(Constants::WIDTH / 2 - levelCompleteText.getGlobalBounds().width / 2,
                                  Constants::HEIGHT / 2 - 50);

    continueText.setFont(font);
    continueText.setCharacterSize(24);
    continueText.setFillColor(sf::Color::White);
    continueText.setString(toUtf8("예(Y) / 아니오(N)"));
    continueText.setPosition(Constants::WIDTH / 2 - continueText.getGlobalBounds().width / 2,
                             Constants::HEIGHT / 2 + 20);

    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(32);
    finalScoreText.setFillColor(sf::Color::White);

    // 메뉴 초기화
    initializeMainMenu();
    initializeOptions();
    gameState = GameState::MainMenu;
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        switch (gameState) {
            case GameState::MainMenu:
                processMainMenuEvents(event);
                break;
            case GameState::Options:
                processOptionsEvents(event);
                break;
            case GameState::Playing:
                processPlayingEvents(event);
                break;
            case GameState::GameOver:
                processGameOverEvents(event);
                break;
            case GameState::LevelComplete:
                processLevelCompleteEvents(event);
                break;
        }
    }
}

void Game::processMainMenuEvents(const sf::Event& event) {
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        for (size_t i = 0; i < menuItems.size(); ++i) {
            if (menuItems[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                selectedMenuItem = i;
                break;
            }
        }
    }
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        for (size_t i = 0; i < menuItems.size(); ++i) {
            if (menuItems[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                selectedMenuItem = i;
                executeMenuOption(i);
                break;
            }
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedMenuItem = (selectedMenuItem - 1 + menuItems.size()) % menuItems.size();
        } else if (event.key.code == sf::Keyboard::Down) {
            selectedMenuItem = (selectedMenuItem + 1) % menuItems.size();
        } else if (event.key.code == sf::Keyboard::Return) {
            executeMenuOption(selectedMenuItem);
        }
    }
}

void Game::processOptionsEvents(const sf::Event& event) {
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        for (size_t i = 0; i < optionsItems.size(); ++i) {
            if (optionsItems[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                selectedOptionsItem = i;
                break;
            }
        }
    }
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        for (size_t i = 0; i < optionsItems.size(); ++i) {
            if (optionsItems[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                selectedOptionsItem = i;
                executeOptionsOption(i);
                break;
            }
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedOptionsItem = (selectedOptionsItem - 1 + optionsItems.size()) % optionsItems.size();
        } else if (event.key.code == sf::Keyboard::Down) {
            selectedOptionsItem = (selectedOptionsItem + 1) % optionsItems.size();
        } else if (event.key.code == sf::Keyboard::Return) {
            executeOptionsOption(selectedOptionsItem);
        } else if (event.key.code == sf::Keyboard::Escape) {
            gameState = GameState::MainMenu;
        }
    }
}

void Game::processPlayingEvents(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        gameState = GameState::MainMenu;
    }
}

void Game::processGameOverEvents(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
        resetGame();
        gameState = GameState::Playing;
    }
}

void Game::processLevelCompleteEvents(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Y) {
            resetGame();
            gameState = GameState::Playing;
        } else if (event.key.code == sf::Keyboard::N) {
            finalScoreText.setString(toUtf8("최종 점수: " + std::to_string(score)));
            finalScoreText.setPosition(Constants::WIDTH / 2 - finalScoreText.getGlobalBounds().width / 2,
                                       Constants::HEIGHT / 2 - finalScoreText.getGlobalBounds().height / 2);
            gameState = GameState::GameOver;
        }
    }
}

void Game::executeMenuOption(int option) {
    switch (option) {
        case 0:
            gameState = GameState::Playing;
            resetGame();
            break;
        case 1:
            gameState = GameState::Options;
            break;
        case 2:
            window.close();
            break;
    }
}

void Game::executeOptionsOption(int option) {
    if (option == 0) {
        difficulty = (difficulty == Constants::Difficulty::EASY) ?
                     Constants::Difficulty::HARD : Constants::Difficulty::EASY;
        optionsItems[0].setString(toUtf8("난이도: " + getDifficultyString()));
    } else if (option == optionsItems.size() - 1) {
        gameState = GameState::MainMenu;
    }
}

void Game::update() {
    if (gameState == GameState::Playing) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) paddle.move(-1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) paddle.move(1);

        bool allBallsOutOfBounds = true;
        for (auto& ball : balls) {
            ball.move();
            ball.keepInBounds(0, 0, Constants::WIDTH, Constants::HEIGHT);
            if (!ball.isOutOfBounds()) {
                allBallsOutOfBounds = false;
            }
        }

        if (allBallsOutOfBounds) {
            gameState = GameState::GameOver;
        }

        checkCollisions();
        scoreText.setString(toUtf8("점수: " + std::to_string(score)));

        // 모든 벽돌이 파괴되었는지 확인
        allBricksDestroyed = true;
        for (const auto& brick : bricks) {
            if (!brick.isDestroyed()) {
                allBricksDestroyed = false;
                break;
            }
        }

        if (allBricksDestroyed) {
            gameState = GameState::LevelComplete;
        }
    } else if (gameState == GameState::MainMenu) {
        updateMainMenu();
    } else if (gameState == GameState::Options) {
        updateOptions();
    }
}

void Game::render() {
    window.clear();

    if (gameState == GameState::Playing) {
        // 게임 플레이 화면 렌더링
        paddle.draw(window);
        for (auto &ball: balls) {
            ball.draw(window);
        }
        for (auto &brick: bricks) {
            brick.draw(window);
        }
        window.draw(scoreText);
    } else if (gameState == GameState::MainMenu) {
        renderMainMenu();
    } else if (gameState == GameState::Options) {
        renderOptions();
    } else if (gameState == GameState::GameOver) {
        window.draw(gameOverText);
        window.draw(finalScoreText);
    } else if (gameState == GameState::LevelComplete) {
        window.draw(levelCompleteText);
        window.draw(continueText);
    }

    window.display();
}

void Game::checkCollisions() {
    for (auto& ball : balls) {
        if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
            ball.reverseYVelocity();

            float paddleCenterX = paddle.getPosition().x + paddle.getSize().x / 2;
            float ballCenterX = ball.getPosition().x + Constants::BALL_RADIUS;
            float relativeIntersectX = ballCenterX - paddleCenterX;
            float normalizedRelativeIntersectionX = (relativeIntersectX / (paddle.getSize().x / 2));
            float bounceAngle = normalizedRelativeIntersectionX * Constants::MAX_BOUNCE_ANGLE;

            ball.setVelocity(
                    5.0f * std::sin(bounceAngle),
                    -5.0f * std::cos(bounceAngle)
            );
        }

        for (auto& brick : bricks) {
            if (!brick.isDestroyed() && ball.getGlobalBounds().intersects(brick.getGlobalBounds())) {
                brick.destroy();

                sf::FloatRect ballBounds = ball.getGlobalBounds();
                sf::FloatRect brickBounds = brick.getGlobalBounds();

                bool fromLeft = ballBounds.left + ballBounds.width >= brickBounds.left && ballBounds.left < brickBounds.left;
                bool fromRight = ballBounds.left <= brickBounds.left + brickBounds.width && ballBounds.left + ballBounds.width > brickBounds.left + brickBounds.width;
                bool fromTop = ballBounds.top + ballBounds.height >= brickBounds.top && ballBounds.top < brickBounds.top;
                bool fromBottom = ballBounds.top <= brickBounds.top + brickBounds.height && ballBounds.top + ballBounds.height > brickBounds.top + brickBounds.height;

                if ((fromLeft || fromRight) && !(fromTop || fromBottom)) {
                    ball.reverseXVelocity();
                } else if ((fromTop || fromBottom) && !(fromLeft || fromRight)) {
                    ball.reverseYVelocity();
                } else {
                    ball.reverseXVelocity();
                    ball.reverseYVelocity();
                }

                score += 10;
            }
        }

        if (ball.getPosition().x <= 0 || ball.getPosition().x + 2 * Constants::BALL_RADIUS >= Constants::WIDTH) {
            ball.reverseXVelocity();
        }
        if (ball.getPosition().y <= 0) {
            ball.reverseYVelocity();
        }
    }
}

// 게임 리셋 함수
void Game::resetGame() {
    score = 0;
    balls.clear();
    balls.push_back(Ball());  // 첫 번째 공 추가
    if (difficulty == Constants::Difficulty::HARD) {
        balls.push_back(Ball());  // 두 번째 공 추가 (어려운 난이도)
    }
    paddle = Paddle();
    bricks.clear();
    for (int i = 0; i < Constants::BRICK_COLUMNS; i++) {
        for (int j = 0; j < Constants::BRICK_ROWS; j++) {
            bricks.emplace_back(i * (Constants::BRICK_WIDTH + 10) + 45, j * (Constants::BRICK_HEIGHT + 5) + 50);
        }
    }
    allBricksDestroyed = false;
}

// 메인 메뉴 초기화 함수
void Game::initializeMainMenu() {
    std::vector<sf::String> itemStrings = {toUtf8("시작"), toUtf8("설정"), toUtf8("나가기")};
    for (const auto &item: itemStrings) {
        sf::Text menuItem;
        menuItem.setFont(font);
        menuItem.setCharacterSize(Constants::MENU_TEXT_SIZE);
        menuItem.setFillColor(Constants::MENU_TEXT_COLOR);
        menuItem.setString(item);
        menuItems.push_back(menuItem);
    }

    float totalHeight = (menuItems.size() - 1) * Constants::MENU_ITEM_SPACING;
    float startY = (Constants::HEIGHT - totalHeight) / 2;

    for (size_t i = 0; i < menuItems.size(); ++i) {
        float itemWidth = menuItems[i].getGlobalBounds().width;
        menuItems[i].setPosition((Constants::WIDTH - itemWidth) / 2, startY + i * Constants::MENU_ITEM_SPACING);
    }
}

// 메인 메뉴 업데이트 함수
void Game::updateMainMenu() {
    for (size_t i = 0; i < menuItems.size(); ++i) {
        if (i == selectedMenuItem) {
            menuItems[i].setFillColor(sf::Color::Yellow);
        } else {
            menuItems[i].setFillColor(Constants::MENU_TEXT_COLOR);
        }
    }
}

// 메인 메뉴 렌더링 함수
void Game::renderMainMenu() {
    for (const auto &item: menuItems) {
        window.draw(item);
    }
}

// 옵션 메뉴 초기화 함수
void Game::initializeOptions() {
    sf::String difficultyStr = (difficulty == Constants::Difficulty::EASY) ? toUtf8("쉬움") : toUtf8("어려움");
    std::vector<sf::String> itemStrings = {
            toUtf8("난이도: " + getDifficultyString()),
            toUtf8("돌아가기")
    };
    for (const auto &item: itemStrings) {
        sf::Text optionItem;
        optionItem.setFont(font);
        optionItem.setCharacterSize(Constants::MENU_TEXT_SIZE);
        optionItem.setFillColor(Constants::MENU_TEXT_COLOR);
        optionItem.setString(item);
        optionsItems.push_back(optionItem);
    }

    float totalHeight = (optionsItems.size() - 1) * Constants::MENU_ITEM_SPACING;
    float startY = (Constants::HEIGHT - totalHeight) / 2;

    for (size_t i = 0; i < optionsItems.size(); ++i) {
        float itemWidth = optionsItems[i].getGlobalBounds().width;
        optionsItems[i].setPosition((Constants::WIDTH - itemWidth) / 2, startY + i * Constants::MENU_ITEM_SPACING);
    }
}

// 옵션 메뉴 업데이트 함수
void Game::updateOptions() {
    for (size_t i = 0; i < optionsItems.size(); ++i) {
        if (i == selectedOptionsItem) {
            optionsItems[i].setFillColor(sf::Color::Yellow);
        } else {
            optionsItems[i].setFillColor(Constants::MENU_TEXT_COLOR);
        }
    }
}

// 옵션 메뉴 렌더링 함수
void Game::renderOptions() {
    for (const auto &item: optionsItems) {
        window.draw(item);
    }
}

// UTF-8 변환 함수
sf::String Game::toUtf8(const std::string& str) {
    return sf::String::fromUtf8(str.begin(), str.end());
}

std::string Game::getDifficultyString() const {
    return (difficulty == Constants::Difficulty::EASY) ? "쉬움" : "어려움";
}