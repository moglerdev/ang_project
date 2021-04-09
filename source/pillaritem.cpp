#include "pillaritem.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QGraphicsScene>

#include "player.h"

PillarItem::PillarItem() :
    isScoreHitted(false),
    upP(new QGraphicsPixmapItem(QPixmap(":/Images/pillar.png"))),
    downP(new QGraphicsPixmapItem(QPixmap(":/Images/pillar.png"))),
    scoreBox(new QGraphicsRectItem(0, -60, 10, 120))
{
    addToGroup(upP);
    addToGroup(downP);
    //addToGroup(scoreBox);

    upP->setPos(
        QPointF(upP->boundingRect().width() / -2,
            (-1 * downP->boundingRect().height()) + 100
        )
    );

    downP->setRotation(180.0f);
    downP->setPos(
        QPointF(downP->boundingRect().width() / 2,
            (downP->boundingRect().height()) + 300
        )
    );

    //DEBUG
    scoreBox->setBrush(Qt::red);

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

    setPos(QPoint(0,0) + QPoint(500 + randXPos, yPos));

    moveAnimation = new QPropertyAnimation(this, "x", this);

    connect(moveAnimation, &QPropertyAnimation::finished, [=](){
        scene()->removeItem(this);
        delete this;
    });

    moveAnimation->setStartValue(500 + randXPos);
    moveAnimation->setDuration(1500);
    moveAnimation->setEndValue(-20);
    moveAnimation->setEasingCurve(QEasingCurve::Linear);

    moveAnimation->start();
}

void PillarItem::stop()
{
    moveAnimation->stop();
}

void PillarItem::setX(qreal x){
    this->m_x = x;
    if(hitPlayerScore()){
        emit playerHitsScore();
    }
    else if(hitPlayerPillar()){
        emit collideWithPlayer();
    }
    setPos(QPointF(0,0) + QPointF(x, yPos));
}

bool PillarItem::hitPlayerPillar()
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
bool PillarItem::hitPlayerScore()
{
    if(isScoreHitted){
        return false;
    }

    QList<QGraphicsItem*> collindingItems = this->scoreBox->collidingItems();
    foreach(QGraphicsItem * item, collindingItems){
        Player * player = dynamic_cast<Player*>(item);
        if(player){
            isScoreHitted = true;
            return true;
        }
    }

    return false;
}
