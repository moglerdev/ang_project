#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    setUpPillarTimer();

    player = new Player();
    addItem(player);
}

void Scene::setUpPillarTimer()
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=](){
       PillarItem * pillar = new PillarItem();

       addItem(pillar);

    });

    timer->start(1000);
}

void Scene::keyPressEvent(QKeyEvent *event)
{

}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
}
