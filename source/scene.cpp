#include "scene.h"

#include <QDebug>

// Konstruktor von der Klasse Scene 
Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    pillarGeneratorTimer(new QTimer(this))
{
    itemsBoundingRect();
    isPlaying = false;
}

void Scene::setup()
{
    //QPixmap bg = QPixmap(":/Images/background.png");
    //QGraphicsPixmapItem * bgItem = new QGraphicsPixmapItem(
    //            bg.scaled(this->sceneRect().width(), this->sceneRect().height()));

    QGraphicsRectItem* bgItem = new QGraphicsRectItem(-20, -20, 1000, 1000); // Instanziere bgItem für den Hintergrund als Rectangle
    addItem(bgItem); //Füge bgItem in die Itempool hinzu

    bgItem->setVisible(false);
    bgItem->setBrush(Qt::transparent); // Ändere die Hintergrundfarbe 
    QPen p = QPen(Qt::transparent, 1);
    bgItem->setPen(p);

    pillars = new QGraphicsItemGroup();
    addItem(pillars);

    player = new Player(); // initialisiere Player
    addItem(player); // füge Player in den Pool hinzu

    player->setPos(QPointF(0, height() / 2));

    connect(player, &Player::gameOver, [=]() {
            this->stopGame();
        });

    hud = new HUD(this); // initialisere das HUD
    addItem(hud); // füge es hinzu

    connect(hud, &HUD::closeGame, [=]() {
        stopGame();
        });
    connect(hud, &HUD::startGame, [=]() {
        startGame();
        });

    hud->setPos(QPointF(0, 0));

    //PillarItem* pillar = new PillarItem(true); // Hinderniss wird deklariert und initialisiert
    //addItem(pillar); // Hinderniss in die Scene hinzufügen
    
    setupGenerator(); // initialisere den Generator für die Hindernisse
}

void Scene::startGame()
{
    if(!isPlaying){ 
        // Wenn er NICHT spielt!
        // isPlayer wird auf "true" gesetzt
        isPlaying = true;

        QList<QGraphicsItem *> objs = pillars->childItems(); // Alle Items in der Scene werden in einer Liste gespeichert
        foreach(QGraphicsItem * obj, objs) { //Alle Items einzeln durchgegangen
            PillarItem * item = dynamic_cast<PillarItem*>(obj); //über c++ funktion dynamic_cast wird es versucht in PillaerItem Obj umcasten
            if(item) {  // Prüft ob der "dynamic_cast" erfolgreich war,
                //wenn erfolgreich, dann wird diese if ausgeführt.
                delete obj; // PillarItem wird gelöscht
            }
        }
        
        // Player wird zurück auf anfangs Position gesetzt.
        //player->setX(10);

        player->setPos(QPointF(0, height() / 2));
        player->activatePlayer(); //Methode von Player -> activatePlayer wird ausgeführt
        pillarGeneratorTimer->start(800); //Timer für die Pillar generierung wird gestartet

        hud->setScorePoints(0);   // Highscore wird auf 0 zurückgesetzt
    } 
}

void Scene::stopGame()
{
    isPlaying = false;  // setze Spiel als beendet
    pillarGeneratorTimer->stop(); // stoppe den TImer für die Hindernisse
    player->disablePlayer(); // Deaktiviere den Spieler

    QList<QGraphicsItem *> objs = items(); // instanziere die Items die im Spiel sind als QListe
    foreach(QGraphicsItem * obj, objs){ // gehe alle einzelne Items durch
        PillarItem* pillar = dynamic_cast<PillarItem*>(obj); // Versuche die Items als PillarItem zu konvetiere
        if(pillar){ // Wenn es konvertiert wurde, 
            pillar->stop(); // lösche den Pillar / Hinderniss
        }
    }
}

void Scene::addScore()
{
    hud->addScorePoints(1); // Score in Hud hinzufügen
}

void Scene::setupGenerator()
{
    connect(pillarGeneratorTimer, &QTimer::timeout, [=](){ // connect von Qt::QtMetaObject wird ausgeführt, 
        // wenn pillarGenTimer timout als Singal emitiert, wird diese lamda Funktion ausgeführt.
       if(!isPlaying){
           // wenn das Spiel nicht ausgeührt wird, soll der pillarGenTimer gestoppt werden
           pillarGeneratorTimer->stop();
       }else{
           // wenn das Spiel ausgeführt wird
           PillarItem * pillar = new PillarItem(); // Hinderniss wird deklariert und initialisiert
           pillars->addToGroup(pillar); // Hinderniss in die Scene hinzufügen

           connect(pillar, &PillarItem::collideWithPlayer, [=](){ // Signal collideWithPlayer verbinden
                stopGame(); // Game soll gestoppt werden
           });
           connect(pillar, &PillarItem::playerHitsScore, [=](){ // Signal playerHitsScore verbinden
                addScore(); // Scoreboard soll einpunkt hinzugefügt werden
           });
       }
    });
}


// Wird von Qt aufgerufen, wenn eine Taste gedrückt wird.
void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* eve)
{
    emit returnCords(eve->scenePos());
    QGraphicsScene::mouseMoveEvent(eve);
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
    }
    QGraphicsScene::keyPressEvent(eve);
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
    }
    QGraphicsScene::mousePressEvent(eve);
}
