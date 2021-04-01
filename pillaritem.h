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

signals:

public slots:
    void setX(qreal x);

private:
    qreal m_x;
    int yPos;
    QGraphicsPixmapItem * upP;
    QGraphicsPixmapItem * downP;
    QPropertyAnimation * xAnimation;
};

#endif // PILLARITEM_H
