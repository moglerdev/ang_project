#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QTimer>

#include "pillaritem.h"
#include "player.h"
#include "hud.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(QObject *parent = nullptr);

    void init();

    void startGame();
    void stopGame();
    void addScore();

signals:

public slots:
private:
    void setUpPillarTimer();

    Player *player;
    HUD *hud;
    QTimer *timer;

    int highscore = 0;
    bool isPlaying;

protected:
    void keyPressEvent(QKeyEvent *eve);
    void mousePressEvent(QGraphicsSceneMouseEvent *eve);
};

#endif // SCENE_H
