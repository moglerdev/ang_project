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

    void setup();

    void startGame();
    void stopGame();
    void addScore();

signals:
    void returnCords(QPointF pos);

public slots:
private:
    void setupGenerator();

    Player *player;
    HUD *hud;
    QTimer * pillarGeneratorTimer;

    int highscore = 0;
    bool isPlaying;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void keyPressEvent(QKeyEvent *eve);
    void mousePressEvent(QGraphicsSceneMouseEvent *eve);
};

#endif // SCENE_H
