#include "pillaritem.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QGraphicsScene>

#include "player.h"

PillarItem::PillarItem() :
    upP(new QGraphicsPixmapItem(QPixmap(":/Images/pillar.png"))),
    downP(new QGraphicsPixmapItem(QPixmap(":/Images/pillar.png")))
{
    addToGroup(upP);
    addToGroup(downP);

    upP->setPos(QPointF(0,0) - QPointF(upP->boundingRect().width()/2,
                                                upP->boundingRect().height()+60));
    downP->setRotation(180.0f);
    downP->setPos(QPointF(downP->boundingRect().width()/2,
                                                downP->boundingRect().height()+60));

    this->startAnimation();
}

PillarItem::~PillarItem(){

}

qreal PillarItem::getX() const{
    return m_x;
}

void PillarItem::startAnimation(){
    yPos = QRandomGenerator::global()->bounded(150);
    int randXPos = QRandomGenerator::global()->bounded(200);

    setPos(QPoint(0,0) + QPoint(260 + randXPos, yPos));

    moveAnimation = new QPropertyAnimation(this, "x", this);

    connect(moveAnimation, &QPropertyAnimation::finished, [=](){
        scene()->removeItem(this);
        delete this;
    });

    moveAnimation->setStartValue(260 + randXPos);
    moveAnimation->setDuration(1500);
    moveAnimation->setEndValue(-260);
    moveAnimation->setEasingCurve(QEasingCurve::Linear);

    moveAnimation->start();
}

void PillarItem::stop()
{
    moveAnimation->stop();
}

void PillarItem::setX(qreal x){
    this->m_x = x;
    if(isCollidingWithPlayer()){
        emit collideWithPlayer();
    }
    setPos(QPointF(0,0) + QPointF(x, yPos));
}

bool PillarItem::isCollidingWithPlayer()
{
    QList<QGraphicsItem*> collindingItems = this->upP->collidingItems();
    collindingItems.append(this->downP->collidingItems());

    foreach(QGraphicsItem * item, collindingItems){
        Player * player = dynamic_cast<Player*>(item);
        if(player){
            return true;
        }
    }

    return false;
}
