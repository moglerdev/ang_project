#include "widget.h"
#include "ui_widget.h"

#include <QGraphicsPixmapItem>
#include "pillaritem.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget())
{
    ui->setupUi(this); // richtet die UI ein, mit dem speziellen Widget 
    scene = new Scene(this); // instanziere die Scene mit dem Paramter "sich selbst"
    scene->setSceneRect(-250, -300, 500, 600); // Setzt die Größe und Position der Scene

    scene->setup(); // passt und richtet alle Objekt ein, für die erste Ausführung

    ui->graphicsView->setScene(scene); // Setzt generierte als aktuelle Scene 
    this->setFixedSize(510, 610); // Setzt die Fenstergröße fest (nicht veränderbar)
}

Widget::~Widget()
{
    delete ui; // Wenn der Desktrutor ausgelöst wird, soll die UI (hart) gelöscht werden
}
