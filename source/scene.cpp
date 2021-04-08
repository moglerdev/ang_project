#include "scene.h"

#include <QDebug>

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    hud(new HUD()),
    player(new Player()),
    timer(new QTimer(this))
{
    isPlaying = false;
}

void Scene::init()
{
    //QPixmap bg = QPixmap(":/Images/background.png");
    //QGraphicsPixmapItem * bgItem = new QGraphicsPixmapItem(
    //            bg.scaled(this->sceneRect().width(), this->sceneRect().height()));

    QGraphicsRectItem* bgItem = new QGraphicsRectItem();
    addItem(bgItem);

    bgItem->setBrush(Qt::cyan);
    bgItem->setPos(0, 0);

    player = new Player();
    addItem(player);

    player->setX(-200);
    player->setY(0);

    hud = new HUD();
    addItem(hud);

    setUpPillarTimer();
}

void Scene::startGame()
{
    if(!isPlaying){
        QList<QGraphicsItem *> objs = items();
        foreach(QGraphicsItem * obj, objs){
            PillarItem * item = dynamic_cast<PillarItem*>(obj);
            if(item){
                delete obj;
            }
        }

        player->setX(-200);
        player->setY(0);

        isPlaying = true;
        player->activatePlayer();
        timer->start(800);

        highscore = 0;
    }
}

void Scene::stopGame()
{
    isPlaying = false;
    timer->stop();
    player->disablePlayer();

    QList<QGraphicsItem *> objs = items();
    foreach(QGraphicsItem * obj, objs){
        PillarItem* pillar = dynamic_cast<PillarItem*>(obj);
        if(pillar){
            pillar->stop();
        }
    }
}

void Scene::addScore()
{
    hud->addScorePoints(1);
}

void Scene::setUpPillarTimer()
{
    connect(timer, &QTimer::timeout, [=](){
       if(!isPlaying){
            timer->stop();
       }else{
           PillarItem * pillar = new PillarItem();
           connect(pillar, &PillarItem::collideWithPlayer, [=](){
                stopGame();
           });
           connect(pillar, &PillarItem::playerHitsScore, [=](){
                addScore();
           });
           addItem(pillar);
       }
    });
}

void Scene::keyPressEvent(QKeyEvent *eve)
{
    if(isPlaying){
        if(eve->key() == Qt::Key_Space){
            player->flyUp();
        }
    }else{
        this->startGame();
    }
    //QGraphicsScene::keyPressEvent(eve);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *eve)
{
    if(isPlaying){
        if( eve->button() == Qt::LeftButton){
            player->flyUp();
        }
    }else{
        this->startGame();
    }
    //QGraphicsScene::mousePressEvent(eve);
}
