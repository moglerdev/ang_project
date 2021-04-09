#include "scene.h"

#include <QDebug>

// Konstruktor von der Klasse Scene 
Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    pillarGeneratorTimer(new QTimer(this))
{
    isPlaying = false;
}

void Scene::setup()
{
    //QPixmap bg = QPixmap(":/Images/background.png");
    //QGraphicsPixmapItem * bgItem = new QGraphicsPixmapItem(
    //            bg.scaled(this->sceneRect().width(), this->sceneRect().height()));

    
    QGraphicsRectItem* bgItem = new QGraphicsRectItem(-20, -20, 1000, 1000); // Instanziere bgItem f�r den Hintergrund als Rectangle
    addItem(bgItem); //F�ge bgItem in die Itempool hinzu

    bgItem->setBrush(Qt::black); // �ndere die Hintergrundfarbe 

    hud = new HUD(); // initialisere das HUD
    addItem(hud); // f�ge es hinzu

    player = new Player(); // initialisiere Player
    addItem(player); // f�ge Player in den Pool hinzu
    
    setupGenerator(); // initialisere den Generator f�r die Hindernisse
}

void Scene::startGame()
{
    if(!isPlaying){ 
        // Wenn er NICHT spielt!
        // isPlayer wird auf "true" gesetzt
        isPlaying = true;

        QList<QGraphicsItem *> objs = items(); // Alle Items in der Scene werden in einer Liste gespeichert
        foreach(QGraphicsItem * obj, objs) { //Alle Items einzeln durchgegangen
            PillarItem * item = dynamic_cast<PillarItem*>(obj); //�ber c++ funktion dynamic_cast wird es versucht in PillaerItem Obj umcasten
            if(item) {  // Pr�ft ob der "dynamic_cast" erfolgreich war,
                //wenn erfolgreich, dann wird diese if ausgef�hrt.
                delete obj; // PillarItem wird gel�scht
            }
        }
        
        // Player wird zur�ck auf anfangs Position gesetzt.
        //player->setX(10);

        player->activatePlayer(); //Methode von Player -> activatePlayer wird ausgef�hrt
        pillarGeneratorTimer->start(800); //Timer f�r die Pillar generierung wird gestartet

        highscore = 0;   // Highscore wird auf 0 zur�ckgesetzt
    }
}

void Scene::stopGame()
{
    isPlaying = false;  // setze Spiel als beendet
    pillarGeneratorTimer->stop(); // stoppe den TImer f�r die Hindernisse
    player->disablePlayer(); // Deaktiviere den Spieler

    QList<QGraphicsItem *> objs = items(); // instanziere die Items die im Spiel sind als QListe
    foreach(QGraphicsItem * obj, objs){ // gehe alle einzelne Items durch
        PillarItem* pillar = dynamic_cast<PillarItem*>(obj); // Versuche die Items als PillarItem zu konvetiere
        if(pillar){ // Wenn es konvertiert wurde, 
            pillar->stop(); // l�sche den Pillar / Hinderniss
        }
    }
}

void Scene::addScore()
{
    hud->addScorePoints(1); // Score in Hud hinzuf�gen
}

void Scene::setupGenerator()
{
    connect(pillarGeneratorTimer, &QTimer::timeout, [=](){ // connect von Qt::QtMetaObject wird ausgef�hrt, 
        // wenn pillarGenTimer timout als Singal emitiert, wird diese lamda Funktion ausgef�hrt.
       if(!isPlaying){
           // wenn das Spiel nicht ausge�hrt wird, soll der pillarGenTimer gestoppt werden
           pillarGeneratorTimer->stop();
       }else{
           // wenn das Spiel ausgef�hrt wird
           PillarItem * pillar = new PillarItem(); // Hinderniss wird deklariert und initialisiert
           addItem(pillar); // Hinderniss in die Scene hinzuf�gen

           connect(pillar, &PillarItem::collideWithPlayer, [=](){ // Signal collideWithPlayer verbinden
                stopGame(); // Game soll gestoppt werden
           });
           connect(pillar, &PillarItem::playerHitsScore, [=](){ // Signal playerHitsScore verbinden
                addScore(); // Scoreboard soll einpunkt hinzugef�gt werden
           });
       }
    });
}

// Wird von Qt aufgerufen, wenn eine Taste gedr�ckt wird.
void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    emit returnCords(mouseEvent->scenePos());
    //QGraphicsScene::keyPressEvent(eve);
}

// Wird von Qt aufgerufen, wenn eine Taste gedr�ckt wird.
void Scene::keyPressEvent(QKeyEvent *eve)
{
    if(isPlaying){ 
        // wird gerade "gespielt"?
        if(eve->key() == Qt::Key_Space){ // eve wird "key()" aufgerufen und gepr�ft ob "Qt::Key_Space" entspricht, ob Spacebar gedr�ckt wurde
            // wenn Spacebar dr�ckt wurde, 
            player->flyUp(); // player soll hochfliegen
        }
    }else{
        // wird nicht gespielt, soll das Spiel gestartet werden
        this->startGame();
    }
    //QGraphicsScene::keyPressEvent(eve);
}

// Wird von Qt aufgerufen, wenn eine Maustaste gedr�ckt wird.
void Scene::mousePressEvent(QGraphicsSceneMouseEvent *eve)
{
    if(isPlaying){ 
        // wird gerade "gespielt" ?
        if( eve->button() == Qt::LeftButton) {
            // Wenn linke Maustaste gedr�ckt
            player->flyUp(); // player hochdruck
        }
    }else{
        this->startGame(); // Spiel soll gestartet werden
    }
    //QGraphicsScene::mousePressEvent(eve);
}
