#ifndef PILLARITEM_H
#define PILLARITEM_H

#include <QGraphicsItemGroup>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>

/// <summary>
/// Hindernis
/// </summary>
class PillarItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT // The Q_OBJECT macro must appear in the private section of a class definition that declares its own signals and slots or that uses other services provided by Qt's meta-object system.
    Q_PROPERTY(qreal x READ getX WRITE setX) // This macro is used for declaring properties in classes that inherit QObject. Properties behave like class data members, but they have additional features accessible through the Meta-Object System.
public:
    /// <summary>
    /// Konstruktor
    /// </summary>
    explicit PillarItem();
    ~PillarItem();
    /// <summary>
    /// Gibt aktuelle Position der X-Achse zur�ck
    /// </summary>
    /// <returns>Position von X als qreal</returns>
    qreal getX() const;
    /// <summary>
    /// Stopt alles vom PillarItem
    /// </summary>
    void stop();

signals:
    /// <summary>
    /// Signal das Spieler ber�hrt wurde
    /// </summary>
    void collideWithPlayer();
    /// <summary>
    /// Signal das Spieler ScoreBox ber�hrt hat
    /// </summary>
    void playerHitsScore();

public slots:
    /// <summary>
    /// Slot f�r das Setzen der X Achse
    /// </summary>
    void setX(qreal x);

private:
    /// <summary>
    /// Startet die Animationen
    /// </summary>
    void startAnimation();
    /// <summary>
    /// Pr�ft ob der Spieler R�hre ber�hrt hat
    /// </summary>
    /// <returns>Wenn Spieler ber�hrt = true; wenn nicht = false</returns>
    bool hitPlayerPillar();
    /// <summary>
    /// Pr�ft ob Spieler ScoreBox ber�hrt
    /// </summary>
    /// <returns>Wenn Spieler ber�hrt = true; wenn nicht = false</returns>
    bool hitPlayerScore();

    bool isScoreHitted; // Wurde Scorebox bereits ber�hrt?

    qreal m_x;
    int yPos;

    QGraphicsPixmapItem * upP;  // R�hre Oben
    QGraphicsPixmapItem * downP; // R�hre Unten
    QGraphicsRectItem * scoreBox; // ScoreBox ( f�r die Punkte )

    QPropertyAnimation * moveAnimation; // Animation f�r die Bewegung nach Links
};

#endif // PILLARITEM_H
