#cmake_minimum_required(VERSION 3.27)
#project(Breakout_Game)
#
#set(CMAKE_CXX_STANDARD 17)
#
#include_directories(include)
#add_executable(Breakout_Game
#        src/main.cpp
#        src/Game.cpp
#        src/Ball.cpp
#        src/Brick.cpp
#        src/Paddle.cpp
#)
#find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)
#target_link_libraries(Breakout_Game sfml-graphics sfml-window sfml-system)

cmake_minimum_required(VERSION 3.10)
project(Breakout_Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML 라이브러리 찾기
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

# 소스 파일 목록
set(SOURCES
        src/main.cpp
        src/Game.cpp
        src/Ball.cpp
        src/Brick.cpp
        src/Paddle.cpp
)

# 헤더 파일 목록
set(HEADERS
        include/Constants.h
        include/GameObject.h
        include/Game.h
        include/Ball.h
        include/Brick.h
        include/Paddle.h
)

# 실행 파일 생성
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# 포함 디렉토리 추가
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# SFML 라이브러리 링크
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-window sfml-system)

# 폰트 파일 복사
file(COPY ${CMAKE_SOURCE_DIR}/resources/PretendardVariable.ttf DESTINATION ${CMAKE_BINARY_DIR})