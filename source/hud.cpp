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
    qDebug() << "Hello";
    // TODO Set Menu Screen
}

void HUD::setGameOver(){
    qDebug() << "Hello";
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