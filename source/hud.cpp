#include "hud.h"
#include <string>

HUD::HUD(QGraphicsScene* scene) :
    scoreboard(new QGraphicsTextItem("Score: 0")),
    gameOverMenu(new Menu(scene, "Game Over")),
    startMenu(new Menu(scene, "Clamsy Bird"))
{
    addToGroup(scoreboard);
    addToGroup(startMenu);
    addToGroup(gameOverMenu);

    gameOverMenu->setVisible(false);
    gameOverMenu->setEnabled(false);

    startMenu->setEnabled(true);

    scoreboard->setPos(0, 0);
    scoreboard->setDefaultTextColor(Qt::red);

    
    auto closeF = [=]() {
        gameOverMenu->setVisible(false);
        startMenu->setVisible(false);
        gameOverMenu->setEnabled(false);
        emit closeGame();
    };
    auto startF = [=]() {
        gameOverMenu->setVisible(false);
        startMenu->setVisible(false);
        gameOverMenu->setEnabled(false);
        emit startGame();
    };
    
    connect(startMenu->addBtn("Starten"), &Button::btnClicked, startF);

    connect(startMenu->addBtn("Beenden"), &Button::btnClicked, closeF);

    connect(gameOverMenu->addBtn("Restart"), &Button::btnClicked, startF);

    connect(gameOverMenu->addBtn("Beenden"), &Button::btnClicked, closeF);
}

void HUD::setGameOver(){
    gameOverMenu->setVisible(true);
    gameOverMenu->setEnabled(true);
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

// Wird von Qt aufgerufen, wenn eine Taste gedrückt wird.
void HUD::mouseMoveEvent(QGraphicsSceneMouseEvent* eve)
{
    QGraphicsItemGroup::mousePressEvent(eve);
}

// Wird von Qt aufgerufen, wenn eine Taste gedrückt wird.
void HUD::keyPressEvent(QKeyEvent* eve)
{
    if (startMenu->isVisible()) {
        
    }
    if (gameOverMenu->isVisible()) {

    }
}

// Wird von Qt aufgerufen, wenn eine Maustaste gedrückt wird.
void HUD::mousePressEvent(QGraphicsSceneMouseEvent* eve)
{
    if (startMenu->isVisible()) {
        startMenu->mousePressed(eve);
    }
    if (gameOverMenu->isVisible()) {
        startMenu->mousePressed(eve);
    }
}
