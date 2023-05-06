cmake_minimum_required(VERSION 3.16)
project(Bejeweled-Diagonal)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

find_package(SDL2_ttf REQUIRED CONFIG COMPONENTS SDL2_ttf)
find_package(SDL2_image REQUIRED CONFIG COMPONENTS SDL2_image)

add_executable(${PROJECT_NAME} main.cpp Button.cpp Game.cpp Menu.cpp
    Score.cpp ScoreWindow.cpp Scoreboard.cpp Utilities.cpp)

if(TARGET SDL2::SDL2main)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image)