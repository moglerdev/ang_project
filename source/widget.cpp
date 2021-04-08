#include "widget.h"
#include "ui_widget.h"

#include <QGraphicsPixmapItem>
#include "pillaritem.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget())
{
    ui->setupUi(this);
    scene = new Scene(this);
    scene->setSceneRect(-250, -300, 500, 600);

    scene->init();

    ui->graphicsView->setScene(scene);
    this->setFixedSize(510, 610);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnStart_clicked()
{
    scene->startGame();
}
