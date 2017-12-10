#include "GameConsole.h"
#include "Display.h"

GameConsole::GameConsole(QWidget *parent) :
    QWidget(parent),
    m_game(0)
{
    resize(parent ? parent->size() : QSize(800, 480));
}

GameConsole::~GameConsole()
{
}

void GameConsole::setGame(GameInterface *game, bool start)
{
    if (m_game == game)
        return;

    m_game = game;
}
