#ifndef PLAYER_H
#define PLAYER_H

#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

#define MOVE_UP
#define MOVE_DOWN_DURATION 1500
#define MOVE_UP_DURATION 400
#define ROTATE_UP_DURATION 800
#define ROTATE_DOWN_DURATION 800
#define GROUND_POS 588

/// <summary>
/// Klasse für den Spieler
/// </summary>
class Player : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ getRotation WRITE setRotation)
    Q_PROPERTY(qreal y READ getY WRITE setY)
public:
    explicit Player();

    qreal getRotation() const;
    qreal getY() const;

    void activatePlayer();
    void disablePlayer();

signals:
    void gameOver();

public slots:
    void setRotation(qreal angle);
    void setY(qreal y);
    void flyUp();
    void rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve);
    void moveTo(const qreal& end, const int& duration, const QEasingCurve& curve);

private:
    enum WingSpriteStatus {
        Up,
        Middle,
        Down
    };
    void updateSprite();
    WingSpriteStatus wingStatus;
    bool isSpriteWingGoingUp;
    bool isFlyUp;
    qreal m_rotation;
    qreal m_y;

    QGraphicsPixmapItem* sprite;

    QPropertyAnimation * moveAnimation;
    QPropertyAnimation * rotationAnimation;

    qreal groundPos;
};

#endif // PLAYER_H
