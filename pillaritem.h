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
    void playerHitsScore();

public slots:
    void setX(qreal x);

private:
    void startAnimation();
    bool hitPlayerPillar();
    bool hitPlayerScore();

    bool isScoreHitted;

    qreal m_x;
    int yPos;
    QGraphicsPixmapItem * upP;
    QGraphicsPixmapItem * downP;
    QGraphicsRectItem * scoreBox;

    QPropertyAnimation * moveAnimation;
};

#endif // PILLARITEM_H
