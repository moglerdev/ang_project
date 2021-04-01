#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QTimer>

#include "pillaritem.h"
#include "player.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void init(qreal w, qreal h);
signals:

public slots:
private:
    void setUpPillarTimer();

    Player * player;
    QTimer * timer;

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *eve);
    void mousePressEvent(QGraphicsSceneMouseEvent *eve);
};

#endif // SCENE_H
