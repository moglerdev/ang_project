#include "menu.h"

Menu::Menu(QGraphicsScene* scene, const QString& textTitle) :
    curScene(scene),
    title(new QGraphicsTextItem(textTitle)),
    btnGroup(new QGraphicsItemGroup())
{
    addToGroup(btnGroup);
    addToGroup(title);

    title->setFont(QFont("Arial", TITLE_FONT_SIZE));
    int t_x = (scene->width() / 2) - title->boundingRect().width() / 2;
    title->setPos(t_x, 0);

    QPoint f(scene->width(), BTN_HEIGHT);
    int g_y = MENU_Y_POS;
    this->setPos(0, g_y);
}

Button* Menu::addBtn(const QString& text, const QColor& textColor, const QBrush& background) {
    Button* btn = new Button(QPoint(curScene->width(), 50), text, textColor, background);

    int len = btnGroup->childItems().length();

    btnGroup->addToGroup(btn);
    btn->setPos(QPointF(
        0,
        (len * (BTN_HEIGHT + 10)) + title->boundingRect().height() + 10
    ));

    return btn;
}


/*

    Button* btnRestart = new Button(f, "Neuer versuch?", Qt::black, QBrush(Qt::green));
    gameOverGroup->addToGroup(btnRestart);
    btnRestart->setPos(0, 100);

    Button* btnClose = new Button(f, "Beenden", Qt::black, QBrush(Qt::red));
    gameOverGroup->addToGroup(btnClose);
    btnClose->setPos(0, 200);

    connect(btnRestart, &Button::btnClicked, [=]() {
        emit startGame();
        });
    connect(btnClose, &Button::btnClicked, [=]() {
        emit closeGame();
        });
    */