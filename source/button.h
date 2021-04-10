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
    void btnClicked(QGraphicsSceneMouseEvent* eve);
    void mouseEnter(QGraphicsSceneHoverEvent* eve);
    void mouseLeave(QGraphicsSceneHoverEvent* eve);

private:
    QGraphicsRectItem* backgroundItem;
    QGraphicsTextItem* textItem;

    void setTextPos(const QPoint& newSize);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* eve);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* eve);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* eve);
};

#endif // BUTTON_H
