#include "hud.h"

HUD::HUD() :
    scoreboard(new QGraphicsTextItem("Score: 0"))
{
    addToGroup(scoreboard);

    scoreboard->setPos(100, 100);
    scoreboard->setScale(100);
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
}
