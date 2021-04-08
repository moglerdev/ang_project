#include "scene.h"

#include <QDebug>

// Konstruktor von der Klasse Scene 
Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    hud(new HUD()),
    player(new Player()),
    pillarGenTimer(new QTimer(this))
{
    isPlaying = false;
}

void Scene::init()
{
    //QPixmap bg = QPixmap(":/Images/background.png");
    //QGraphicsPixmapItem * bgItem = new QGraphicsPixmapItem(
    //            bg.scaled(this->sceneRect().width(), this->sceneRect().height()));

    QGraphicsRectItem* bgItem = new QGraphicsRectItem();
    addItem(bgItem);

    bgItem->setBrush(Qt::cyan);
    bgItem->setPos(0, 0);

    player = new Player();
    addItem(player);

    player->setX(-200);
    player->setY(0);

    hud = new HUD();
    addItem(hud);

    setUpPillarTimer();
}

void Scene::startGame()
{
    if(!isPlaying){ 
        // Wenn er NICHT spielt!

        QList<QGraphicsItem *> objs = items();                      // Alle Items in der Scene werden in einer Liste gespeichert
        foreach(QGraphicsItem * obj, objs){                         //Alle Items einzeln durchgegangen
            PillarItem * item = dynamic_cast<PillarItem*>(obj);     //über c++ funktion dynamic_cast wird es versucht in PillaerItem Obj umcasten
            if(item) {                                              // Prüft ob der "dynamic_cast" erfolgreich war,
                //wenn erfolgreich, dann wird diese if ausgeführt.
                delete obj;                                         // PillarItem wird gelöscht
            }
        }
        
                                                                    // Player wird zurück auf anfangs Position gesetzt.
        player->setX(-200);
        player->setY(0);
       
                                                                    // isPlayer wird auf "true" gesetzt
        isPlaying = true; 
        player->activatePlayer();                                   //Methode von Player -> activatePlayer wird ausgeführt
        pillarGenTimer->start(800);                                          //Timer für die Pillar generierung wird gestartet

        highscore = 0;                                              // Highscore wird auf 0 zurückgesetzt
    }
}

void Scene::stopGame()
{
    isPlaying = false;                      // 
    pillarGenTimer->stop();
    player->disablePlayer();

    QList<QGraphicsItem *> objs = items();
    foreach(QGraphicsItem * obj, objs){
        PillarItem* pillar = dynamic_cast<PillarItem*>(obj);
        if(pillar){
            pillar->stop();
        }
    }
}

void Scene::addScore()
{
    hud->addScorePoints(1); // Score in Hud hinzufügen
}

void Scene::setUpPillarTimer()
{
    connect(pillarGenTimer, &QTimer::timeout, [=](){ // connect von Qt::QtMetaObject wird ausgeführt, 
        // wenn pillarGenTimer timout als Singal emitiert, wird diese lamda Funktion ausgeführt.
       if(!isPlaying){
           // wenn das Spiel nicht ausgeührt wird, soll der pillarGenTimer gestoppt werden
           pillarGenTimer->stop();
       }else{
           // wenn das Spiel ausgeführt wird
           PillarItem * pillar = new PillarItem(); // Hinderniss wird deklariert und initialisiert
           connect(pillar, &PillarItem::collideWithPlayer, [=](){ // Signal collideWithPlayer verbinden
                stopGame(); // Game soll gestoppt werden
           });
           connect(pillar, &PillarItem::playerHitsScore, [=](){ // Signal playerHitsScore verbinden
                addScore(); // Scoreboard soll einpunkt hinzugefügt werden
           });
           addItem(pillar); // Hinderniss in die Scene hinzufügen
       }
    });
}

// Wird von Qt aufgerufen, wenn eine Taste gedrückt wird.
void Scene::keyPressEvent(QKeyEvent *eve)
{
    if(isPlaying){ 
        // wird gerade "gespielt"?
        if(eve->key() == Qt::Key_Space){ // eve wird "key()" aufgerufen und geprüft ob "Qt::Key_Space" entspricht, ob Spacebar gedrückt wurde
            // wenn Spacebar drückt wurde, 
            player->flyUp(); // player soll hochfliegen
        }
    }else{
        // wird nicht gespielt, soll das Spiel gestartet werden
        this->startGame();
    }
    //QGraphicsScene::keyPressEvent(eve);
}

// Wird von Qt aufgerufen, wenn eine Maustaste gedrückt wird.
void Scene::mousePressEvent(QGraphicsSceneMouseEvent *eve)
{
    if(isPlaying){ 
        // wird gerade "gespielt" ?
        if( eve->button() == Qt::LeftButton) {
            // Wenn linke Maustaste gedrückt
            player->flyUp(); // player hochdruck
        }
    }else{
        this->startGame(); // Spiel soll gestartet werden
    }
    //QGraphicsScene::mousePressEvent(eve);
}
