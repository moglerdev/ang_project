#include "widget.h"
#include "ui_widget.h"

#include <QGraphicsPixmapItem>
#include "pillaritem.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new Scene(this);
    scene->setSceneRect(-250, -300, 500, 600);

    QGraphicsPixmapItem * bgItem = new QGraphicsPixmapItem(
                QPixmap(":/Images/background.png"));
    scene->addItem(bgItem);
    bgItem->setPos(QPointF(0,0) -
                   QPointF( bgItem->boundingRect().width()/2,
                            bgItem->boundingRect().height()/2));
    ui->graphicsView->setScene(scene);
}

Widget::~Widget()
{
    delete ui;
}

