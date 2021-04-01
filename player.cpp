#include "player.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>

Player::Player() :
    wingStatus(WingStatus::Up),
    isWingsUp(true)
{
    QPixmap map = QPixmap (":/Images/player.png");
    map = map.scaled(64, 64, Qt::AspectRatioMode::IgnoreAspectRatio);
    setPixmap(map);

    QTimer * flyingTimer = new QTimer(this);
    connect(flyingTimer, &QTimer::timeout, [=](){
        updatePlayerFrame();
    });

    flyingTimer->start(80);

    groundPos = scenePos().y() + 290;

    yAnimation = new QPropertyAnimation(this, "y", this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPos);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);

    yAnimation->start();

    rotationAnimation = new QPropertyAnimation(this, "rotation", this);
    rotateTo(90, 800, QEasingCurve::InQuad);
}

void Player::updatePlayerFrame(){
    if(wingStatus == WingStatus::Middle){
        if(isWingsUp){
            // Up
            // set Pixmap Up
            wingStatus = WingStatus::Up;
            isWingsUp = false;
        }else{
            // Down
            //set Pixmap Down
            wingStatus = WingStatus::Down;
            isWingsUp = true;
        }
    }else{
        setRotation(0.0f);
        wingStatus = WingStatus::Middle;
    }
}

qreal Player::getRotation() const{
    return m_rotation;
}

qreal Player::getY() const{
    return m_y;
}

void Player::setRotation(qreal angle){
    m_rotation = angle;
    QPointF c = boundingRect().center();
    QTransform t;
    t.translate(c.x(), c.y());
    t.rotate(angle);
    t.translate(-c.x(), -c.y());
    setTransform(t);
}

void Player::setY(qreal y){
    moveBy(0, y-m_y);
    m_y = y;
}

void Player::fly()
{
    yAnimation->stop();
    rotationAnimation->stop();

    qreal posY = y();

    yAnimation->setStartValue(posY);
    yAnimation->setEndValue(posY - scene()->sceneRect().height()/8);
    yAnimation->setEasingCurve(QEasingCurve::OutQuad);
    yAnimation->setDuration(1000);
    yAnimation->start();

    rotateTo(-20, 100, QEasingCurve::OutCubic);
}

void Player::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(this->rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);

    rotationAnimation->start();
}


