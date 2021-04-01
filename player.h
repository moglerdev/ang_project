#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ getRotation WRITE setRotation)
    Q_PROPERTY(qreal y READ getY WRITE setY)
public:
    explicit Player();

    qreal getRotation() const;
    qreal getY() const;

signals:

public slots:
    void setRotation(qreal angle);
    void setY(qreal y);
    void fly();
    void rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve);
private:
    enum WingStatus {
        Up,
        Middle,
        Down
    };
    void updatePlayerFrame();

    WingStatus wingStatus;
    bool isWingsUp;
    qreal m_rotation;
    qreal m_y;

    QPropertyAnimation * yAnimation;
    QPropertyAnimation * rotationAnimation;

    qreal groundPos;
};

#endif // PLAYER_H
