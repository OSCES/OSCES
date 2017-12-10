#ifndef GAMECONSOLE_H
#define GAMECONSOLE_H

#include <QWidget>

class GameInterface;

class GameConsole : public QWidget
{
    Q_OBJECT
public:
    explicit GameConsole(QWidget *parent = 0);
    ~GameConsole();

    void setGame(GameInterface *game, bool start = true);
    GameInterface *game() const { return m_game; }

private:
    GameInterface *m_game;
};

#endif // GAMECONSOLE_H
