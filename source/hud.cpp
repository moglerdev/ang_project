#include "hud.h"
#include <string>

HUD::HUD(QGraphicsScene* scene) :
    scoreboard(new QGraphicsTextItem("Score: 0")),
    gameOverGroup(new Menu(scene, "Game Over")),
    startMenu(new Menu(scene, "Flappy Bird"))
{

    addToGroup(scoreboard);
    addToGroup(gameOverGroup);
    addToGroup(startMenu);

    gameOverGroup->setVisible(false);

    scoreboard->setPos(0, 0);
    scoreboard->setDefaultTextColor(Qt::red);

    
    auto closeF = [=]() {
        gameOverGroup->setVisible(false);
        startMenu->setVisible(false);
        emit closeGame();
    };
    auto startF = [=]() {
        gameOverGroup->setVisible(false);
        startMenu->setVisible(false);
        emit startGame();
    };/*
    connect(gameOverGroup->addBtn("Restart"), &Button::btnClicked, startF);

    connect(gameOverGroup->addBtn("Beenden"), &Button::btnClicked, closeF);
    */
    connect(startMenu->addBtn("Starten"), &Button::btnClicked, startF);

    connect(startMenu->addBtn("Beenden"), &Button::btnClicked, closeF);
}

void HUD::setMenu(MenuType menuType){
    startMenu->setVisible(false);
    gameOverGroup->setVisible(false);

    switch (menuType) {
        case MenuType::GameOver:
            gameOverGroup->setVisible(true);
            break;
        case MenuType::Start:
            startMenu->setVisible(true);
            break;
    }
    // TODO Set Menu Screen
}

void HUD::setGameOver(){
    // TODO Set GameOver Screen
}

void HUD::addScorePoints(int add){
    scorePoints += add;
    updateScoreboard();
}

void HUD::setScorePoints(int val) {
    scorePoints = val;
    updateScoreboard();
}

void HUD::updateScoreboard() {
    scoreboard->setPlainText(("Score: " + std::to_string(scorePoints)).c_str());
}