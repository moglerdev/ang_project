#include "widget.h"
#include "ui_widget.h"

#include <QGraphicsPixmapItem>
#include <string>
#include "pillaritem.h"

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget())
{
    ui->setupUi(this); // richtet die UI ein, mit dem speziellen Widget 
    scene = new Scene(this); // instanziere die Scene mit dem Paramter "sich selbst"
    scene->setSceneRect(0, 0, 490, 590); // Setzt die Gr��e und Position der Scene

    scene->setup(); // passt und richtet alle Objekt ein, f�r die erste Ausf�hrung

    ui->graphicsView->setScene(scene); // Setzt generierte als aktuelle Scene 
    this->setFixedSize(520, 620); // Setzt die Fenstergr��e fest (nicht ver�nderbar)

    connect(scene, &Scene::returnCords, [=](QPointF cords) {
        std::string t = "Cords=> X:" + std::to_string(cords.x()) + "| Y:" + std::to_string(cords.y());
        ui->label->setText( t.c_str() );
    });
}

Widget::~Widget()
{
    delete ui; // Wenn der Desktrutor ausgel�st wird, soll die UI (hart) gel�scht werden
}
