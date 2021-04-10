#ifndef HUD_H
#define HUD_H

#include <QGraphicsItemGroup>
#include <QGraphicsTextItem>

#include "button.h"

/// <summary>
/// Klasse für die Menü Anzeige, Scoreboard, etc.
/// </summary>
class HUD : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT // The Q_OBJECT macro must appear in the private section of a class definition that declares its own signals and slots or that uses other services provided by Qt's meta-object system.
public:
    /// <summary>
    /// Für die Menüanzeige 
    /// </summary>
    enum MenuType {
        Start,
        GameOver
    };

    /// <summary>
    /// Konstruktor
    /// </summary>
    explicit HUD(QGraphicsScene* scene);
    /// <summary>
    /// Zeigt Menü an
    /// </summary>
    /// <param name="menuType">Welches Menü angezeigt werden soll; HUD::MenuType</param>
    void setMenu(MenuType menuType);
    /// <summary>
    /// Zeigt GameOver screen
    /// </summary>
    void setGameOver();
    /// <summary>
    /// Fügt Punkte zum Scoreboard hinzu
    /// </summary>
    /// <param name="add">wie viele Punkte sollen hinzugefügt werden</param>
    void addScorePoints(int add);
    /// <summary>
    /// Fügt Punkte zum Scoreboard hinzu
    /// </summary>
    /// <param name="add">wie viele Punkte sollen hinzugefügt werden</param>
    void setScorePoints(int val);

signals:
    void startGame();
    void closeGame();

private:
    int scorePoints = 0; // aktuelles Punktzahl
    QGraphicsTextItem* scoreboard; // GrahicsItem für die Punkteanzeige als Text

    /// <summary>
    /// Fügt Punkte zum Scoreboard hinzu
    /// </summary>
    /// <param name="add">wie viele Punkte sollen hinzugefügt werden</param>
    void updateScoreboard();
    // TODO Menu
    // TODO GameOver

    QGraphicsItemGroup* gameOverGroup;
    QGraphicsItemGroup* startMenu;

};

#endif // HUD_H