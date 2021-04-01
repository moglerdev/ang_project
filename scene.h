#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>

#include "pillaritem.h"
#include "player.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

signals:

public slots:

private:
    void setUpPillarTimer();

    Player * player;
    QTimer * timer;

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H
