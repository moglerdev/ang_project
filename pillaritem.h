#ifndef PILLARITEM_H
#define PILLARITEM_H

#include <QGraphicsItemGroup>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>

class PillarItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit PillarItem();
    ~PillarItem();

    qreal getX() const;
    void stop();

signals:
    void collideWithPlayer();

public slots:
    void setX(qreal x);

private:
    void startAnimation();
    bool isCollidingWithPlayer();

    qreal m_x;
    int yPos;
    QGraphicsPixmapItem * upP;
    QGraphicsPixmapItem * downP;
    QPropertyAnimation * moveAnimation;
};

#endif // PILLARITEM_H
