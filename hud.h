#ifndef HUD_H
#define HUD_H

#include <QGraphicsItemGroup>
#include <QGraphicsTextItem>

class HUD : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit HUD();

    void setMenu();
    void setGameOver();
    void addScorePoints(int add);

signals:

private:
    int scorePoints = 0;
    QGraphicsTextItem* scoreboard;

    // TODO Menu
    // TODO GameOver

};

#endif // HUD_H
