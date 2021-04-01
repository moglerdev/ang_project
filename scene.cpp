#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    setUpPillarTimer();
}

void Scene::init(qreal w, qreal h)
{
    QPixmap bg = QPixmap(":/Images/background.png");
    QGraphicsPixmapItem * bgItem = new QGraphicsPixmapItem(bg.scaled(w, h));
    addItem(bgItem);

    bgItem->setPos(QPointF(0,0) -
                   QPointF( bgItem->boundingRect().width()/2,
                            bgItem->boundingRect().height()/2));
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

void Scene::keyPressEvent(QKeyEvent *eve)
{
    if(eve->key() == Qt::Key_Space){

    }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *eve)
{
    if(eve->button() == Qt::LeftButton){
        player->fly();
    }
    QGraphicsScene::mousePressEvent(eve);
}
