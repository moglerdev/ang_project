#include "player.h"

// Konstruktor von Player Klasse
Player::Player() :
    wingStatus(WingSpriteStatus::Middle), // wingStatus wird initialisiert
    sprite(new QGraphicsPixmapItem)
{
    QPixmap map = QPixmap (":/Images/player.png"); // Player Sprite wird geladen
    map = map.scaled(24, 24, Qt::AspectRatioMode::IgnoreAspectRatio); // Sprite wird an größe angepasst, dabei wird Aspekt nicht beachtet
    sprite->setPixmap(map); // Vom Objekt Player wird der bearbeite Sprite gesetzt 

    addToGroup(sprite);
    /*
    QRect t = map.rect();
    
    QGraphicsRectItem* rect = new QGraphicsRectItem(0, 0, t.width(), t.height());
    rect->setBrush(Qt::black);
    addToGroup(rect);
    */
    QTimer * flyingTimer = new QTimer(this); // Flying Timer wird deklariert und initialisiert
    connect(flyingTimer, &QTimer::timeout, [=](){ // TimeOut Signal wird connected,
        updateSprite(); // Lamda Funktion fürd "update" methode aus
    });

    flyingTimer->start(80); // Timer wird gestartet mit 80ms

    groundPos = scenePos().y() + 620;// Position des Bodens

    moveAnimation = new QPropertyAnimation(this, "y", this); // Animation für die Bewegung / Movement
    connect(moveAnimation, &QPropertyAnimation::finished, [=](){ // Führe die Lamda Funktion, wenn die Animation fertig ist.
        if(isFlyUp){ // fliegt der Spieler hoch?
            isFlyUp = false; // Er fliegt jetzt runter
            this->moveTo(groundPos, MOVE_DOWN_DURATION, QEasingCurve::InQuad); // führe die Methode aus das er Runterfliegen soll
        }
    });

    rotationAnimation = new QPropertyAnimation(this, "rotation", this); // initialisiere die Animation führ das Rotieren des Spielers
}

void Player::updateSprite(){
    if(wingStatus == WingSpriteStatus::Middle) { // Ist Sprite Flügel mittig?
        if (isSpriteWingGoingUp) { // Ist die Flügelanimation gerade nach oben
            wingStatus = WingSpriteStatus::Up; // Setze Sprite Status auf Up
            isSpriteWingGoingUp = false; // Animation geht wieder nach "unten"
        } else { // Die Flügelanimation ist geht nach unten
            wingStatus = WingSpriteStatus::Down; // Setze Sprite Status auf Down
            isSpriteWingGoingUp = true; // Animation geht wieder nach "oben"
        }
    } else { // Wenn Wing Status nicht "Middle" ist
        setRotation(0.0f); // Setzte Rotation zurück
        wingStatus = WingSpriteStatus::Middle; // Setze Wing Status auf "Middle"
    }
}

qreal Player::getRotation() const {
    return m_rotation; // gibt aktuelle Position zurück
}

qreal Player::getY() const{
    return m_y; // gibt aktuelle Höhe / Position der Y-Achse zurück
}

void Player::activatePlayer()
{
    this->moveTo(groundPos, MOVE_DOWN_DURATION, QEasingCurve::InQuad); // aktiviere die Move Animation
    this->rotateTo(90, ROTATE_UP_DURATION, QEasingCurve::InQuad); // aktiviere die Roations Animation
}

void Player::disablePlayer()
{
    rotationAnimation->stop(); // Stopt die Rotations Animation
    moveAnimation->stop(); // Stopt die Animation für die Bewegung
}

void Player::setRotation(qreal angle){
    m_rotation = angle; // setzte aktuelle Rotation
    QPointF c = boundingRect().center(); // gibt die Position vom Mittelpunkt zurück
    QTransform t = QTransform(); //Transformiert das Koordinatensystem zum Bezugsystem
    t.translate(c.x(), c.y()); // Setzte c als Bezugsystem 
    t.rotate(angle); // rotiere das Objekt
    t.translate(-c.x(), -c.y()); // Übersetzte das System zurück zum Ursprung
    setTransform(t); // setzt angepasste Transformation
}

void Player::setY(qreal y){
    if (y < 0 || y > GROUND_POS) { // TODO GameOver
        emit gameOver();
    }
    setPos(QPointF(pos().x(), 0) + QPointF(0, y));
    //qDebug() << pos();
    m_y = y;
}

void Player::moveTo(const qreal& end, const int& duration, const QEasingCurve& curve){
    moveAnimation->stop(); // Stoppe aktuelle Bewegungs-Animation
    qreal posY = y(); // erhalte aktuelle y-Position 

    moveAnimation->setStartValue(posY); // Setzte Startpunkt für die Animation (aktuelle y Pos)
    moveAnimation->setEndValue(end); // Setzte Endpunkt der Animation (end Parameter)
    moveAnimation->setEasingCurve(curve); // Setze Funktion [Linear, Quadtratisch, Expotentiel, etc.] (curve Parameter)
    moveAnimation->setDuration(duration); // Wie lange die Animation dauern soll, in Millisekunden (duration Parameter)

    moveAnimation->start(); // Animation soll gestartet werden
}

void Player::flyUp()
{
    isFlyUp = true; // Spieler setzen das er hochfliegt
    rotationAnimation->stop(); // Rotations Animation stoppen
    // Position wohin der Spieler fliegen soll. 
    qreal posTo = scenePos().y() - 120; //Dabei wird die aktuelle Szene vom Spiel um deren Höhe als Bezugsystem zu verwenden.
    this->moveTo(posTo, MOVE_UP_DURATION, QEasingCurve::OutQuad); // Der Spieler soll umgekehrt Quadtratisch in "MOVE_UP_DURATION" ms zur Position "posTo"
    this->rotateTo(-20, 100, QEasingCurve::OutCubic); //Der Spieler soll -20 rotieren in 100ms umgekehrt Kubikisch
}

void Player::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->stop(); // Stoppe aktuelle Rotations Animation

    rotationAnimation->setStartValue(this->rotation()); // Setze aktuelle Rotations als Startposition
    rotationAnimation->setEndValue(end); // Setze Parameter "end" als Endzustand
    rotationAnimation->setEasingCurve(curve); // Funktionskurve für die Animation
    rotationAnimation->setDuration(duration); // Wie lange die Animation dauern soll

    rotationAnimation->start(); // Animation ausführen
}


