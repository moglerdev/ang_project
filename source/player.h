#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

#define MOVE_UP
#define MOVE_DOWN_DURATION 800
#define MOVE_UP_DURATION 400
#define ROTATE_UP_DURATION 800
#define ROTATE_DOWN_DURATION 800

class Player : public QObject, public QGraphicsPixmapItem
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

public slots:
    void setRotation(qreal angle);
    void setY(qreal y);
    void flyUp();
    void rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve);
    void moveTo(const qreal& end, const int& duration = 1000, const QEasingCurve& curve = QEasingCurve::InQuad);

private:
    enum WingStatus {
        Up,
        Middle,
        Down
    };
    void update();
    WingStatus wingStatus;
    bool isWingsUp;
    bool isFlyUp;
    qreal m_rotation;
    qreal m_y;

    QPropertyAnimation * moveAnimation;
    QPropertyAnimation * rotationAnimation;

    qreal groundPos;
};

#endif // PLAYER_H
