#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QGraphicsItemGroup>
#include <QFont>
#include <QGraphicsScene>

#include "button.h"

#define MENU_Y_POS 140
#define BTN_HEIGHT 50
#define TITLE_FONT_SIZE 30

class Menu : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit Menu(QGraphicsScene* scene, const QString& textTitle);

    Button* addBtn(const QString& text, const QColor& textColor = Qt::black, const QBrush& background = QBrush(Qt::gray));

signals:

private:
    QGraphicsScene* curScene;
    QGraphicsTextItem* title;
    QGraphicsItemGroup* btnGroup;
};

#endif // MENU_H
