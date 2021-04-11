#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class Button : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit Button(const QPoint& size, const QString& textContent, const QColor& textColor = Qt::black, const QBrush& background = QBrush(Qt::gray));

    void setText(const QString& text, const QColor& color);

    void setBackground(const QBrush& background);

    void setSize(const QPoint& size);

    void mousePressed(QGraphicsSceneMouseEvent* eve);

signals:
    void btnClicked();
    void mouseEnter();
    void mouseLeave();

private:
    QGraphicsRectItem* backgroundItem;
    QGraphicsTextItem* textItem;

    void setTextPos(const QPoint& newSize);

};

#endif // BUTTON_H
