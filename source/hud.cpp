#include "hud.h"
#include <string>

HUD::HUD(QGraphicsScene* scene) :
    scoreboard(new QGraphicsTextItem("Score: 0")),
    gameOverGroup(new QGraphicsItemGroup),
    startMenu(new QGraphicsItemGroup)
{

    addToGroup(scoreboard);
    //addToGroup(gameOverGroup);
    addToGroup(startMenu);

    scoreboard->setPos(0, 0);
    scoreboard->setDefaultTextColor(Qt::red);

    QGraphicsTextItem* gameOverText = new QGraphicsTextItem("Game Over");
    gameOverGroup->addToGroup(gameOverText);
    gameOverText->setFont(QFont("Arial", 25));
    int t_x = (scene->width() / 2) - gameOverText->boundingRect().width() / 2;
    gameOverText->setPos(t_x, 10);

    QPoint f(scene->width(), 50);
    Button* btnRestart = new Button(f, "Neuer versuch?", Qt::black, QBrush(Qt::green));
    gameOverGroup->addToGroup(btnRestart);
    btnRestart->setPos(0, 100);

    Button* btnClose = new Button(f, "Beenden", Qt::black, QBrush(Qt::red));
    gameOverGroup->addToGroup(btnClose);
    btnClose->setPos(0, 200);

    int g_y = 148;
    gameOverGroup->setPos(0, g_y);

    connect(btnRestart, &Button::btnClicked, [=]() {
            emit startGame();
        });
    connect(btnClose, &Button::btnClicked, [=]() {
            emit closeGame();
        });

    QGraphicsTextItem* menuText = new QGraphicsTextItem("Flappy Klasse");
    startMenu->addToGroup(menuText);
    menuText->setFont(QFont("Arial", 25));
    t_x = (scene->width() / 2) - menuText->boundingRect().width() / 2;
    menuText->setPos(t_x, 10);

    Button* btnStart = new Button(f, "Spiel starten", Qt::black, QBrush(Qt::green));
    startMenu->addToGroup(btnStart);
    btnStart->setPos(0, 100);

    //Button* btnClose = new Button(f, "Beenden", Qt::black, QBrush(Qt::red));
    //startMenu->addToGroup(btnClose);
    //btnClose->setPos(0, 200);

    startMenu->setPos(0, g_y);

    connect(btnStart, &Button::btnClicked, [=]() {
            emit startGame();
        });
    //connect(btnClose, &Button::btnClicked, [=]() {
    //    emit startGame();
    //    });
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