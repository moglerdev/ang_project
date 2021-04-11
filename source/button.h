#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>

class Button : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit Button(const QPoint& size, const QString& textContent, const QColor& textColor = Qt::black, const QBrush& background = QBrush(Qt::gray));

    void setText(const QString& text, const QColor& color);

    void setBackground(const QBrush& background);

    void setSize(const QPoint& size);

signals:
    void btnClicked();
    void mouseEnter();
    void mouseLeave();

private:
    QGraphicsRectItem* backgroundItem;
    QGraphicsTextItem* textItem;

    void setTextPos(const QPoint& newSize);

protected:

    // QGraphicsItem interface
//public:
    //QRectF boundingRect() const;
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

#endif // BUTTON_H
