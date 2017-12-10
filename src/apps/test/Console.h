#ifndef CONSOLE_H
#define CONSOLE_H

#include <QWidget>
#include "GameInterface.h"

class Display;
class Snake;

class Console : public QWidget
{
    Q_OBJECT

    enum Game
    {
        GameSnake,
        GameRaycasting
    };

public:
    Console(QWidget *parent = 0);
    ~Console();

private slots:
    void createGame(int gameId);
    void closeGame();

private:
    int convertQtKeyToGameKey(int key);
    void updateGame();

protected:
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    bool m_isRunnig;
    Display *m_display;
    GameInterface *m_game;
    int m_loopTimer;
};

#endif // CONSOLE_H
