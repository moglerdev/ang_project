#include "hud.h"
#include <string>

HUD::HUD() :
    scoreboard(new QGraphicsTextItem("Score: 0"))
{
    addToGroup(scoreboard);

    scoreboard->setPos(0, 0);
    scoreboard->setDefaultTextColor(Qt::red);
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
    gameOverGroup = new QGraphicsItemGroup();
    
    QGraphicsTextItem* gameOverText = new QGraphicsTextItem("Game Over");
    gameOverGroup->addToGroup(gameOverText);
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