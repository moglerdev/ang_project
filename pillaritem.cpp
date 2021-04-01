#include "pillaritem.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QGraphicsScene>
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

    yPos = QRandomGenerator::global()->bounded(150);
    int xRandomizer = QRandomGenerator::global()->bounded(200);

    setPos(QPoint(0,0) + QPoint(260 + xRandomizer, yPos));

    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(260 + xRandomizer);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1500);

    connect(xAnimation, &QPropertyAnimation::finished, [=](){
        scene()->removeItem(this);
        delete this;
    });

    xAnimation->start();
}

PillarItem::~PillarItem(){

}

qreal PillarItem::getX() const{
    return m_x;
}

void PillarItem::setX(qreal x){
    this->m_x = x;

    setPos(QPointF(0,0) + QPointF(x, yPos));
}
