#include "player.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>

Player::Player() :
    wingStatus(WingStatus::Up),
    isWingsUp(true)
{
    QPixmap map = QPixmap (":/Images/player.png");
    map = map.scaled(24, 24, Qt::AspectRatioMode::IgnoreAspectRatio);
    setPixmap(map);

    QTimer * flyingTimer = new QTimer(this);
    connect(flyingTimer, &QTimer::timeout, [=](){
        update();
    });

    flyingTimer->start(80);

    groundPos = scenePos().y() + 290;

    moveAnimation = new QPropertyAnimation(this, "y", this);
    connect(moveAnimation, &QPropertyAnimation::finished, [=](){
        if(isFlyUp){
            isFlyUp = false;
            this->moveTo(groundPos, MOVE_DOWN_DURATION);
        }
    });

    rotationAnimation = new QPropertyAnimation(this, "rotation", this);
}

void Player::update(){
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

void Player::activatePlayer()
{
    this->moveTo(groundPos, MOVE_DOWN_DURATION);
    this->rotateTo(90, ROTATE_UP_DURATION, QEasingCurve::InQuad);
}

void Player::disablePlayer()
{
    rotationAnimation->stop();
    moveAnimation->stop();
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

void Player::moveTo(const qreal& end, const int& duration, const QEasingCurve& curve){
    moveAnimation->stop();
    qreal posY = y();

    moveAnimation->setStartValue(posY);
    moveAnimation->setEndValue(end);
    moveAnimation->setEasingCurve(curve);
    moveAnimation->setDuration(duration);

    moveAnimation->start();
}

void Player::flyUp()
{
    isFlyUp = true;
    rotationAnimation->stop();
    qreal posTo = y() - scene()->sceneRect().height() / 10;
    this->moveTo(posTo, MOVE_UP_DURATION, QEasingCurve::OutQuad);
    this->rotateTo(-20, 100, QEasingCurve::OutCubic);
}

void Player::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(this->rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);

    rotationAnimation->start();
}


