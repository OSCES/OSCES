#include "Console.h"
#include "Display.h"
#include "Snake.h"
#include "Raycasting.h"
#include <QTimerEvent>
#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QVBoxLayout>

Console::Console(QWidget *parent) :
    QWidget(parent),
    m_isRunnig(false),
    m_game(0)
{
    m_display = new Display(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(QMargins());
    layout->addWidget(m_display);

    setFixedSize(800, 480);
}

Console::~Console()
{
}

void Console::createGame(int gameId)
{
    switch (gameId)
    {
    case GameSnake:
        closeGame();
        m_game = new Snake(20, 15);
        break;
    case GameRaycasting:
        closeGame();
        m_game = new Raycasting;
        break;
    default:
        return;
    }

    m_game->setDisplay(m_display);
    m_game->initialize();

    m_isRunnig = true;
    m_loopTimer = startTimer(100);
}

void Console::closeGame()
{
    if (!m_game)
        return;

    delete m_game;
    m_game = 0;

    m_isRunnig = false;
}

void Console::updateGame()
{
    m_display->invalidate();
    m_game->run();
    m_display->present();
}

int Console::convertQtKeyToGameKey(int key)
{
    switch (key)
    {
    case Qt::Key_Up:     return Key_Up;
    case Qt::Key_Right:  return Key_Right;
    case Qt::Key_Down:   return Key_Down;
    case Qt::Key_Left:   return Key_Left;
    default:
        ;
    }

    return -1;
}

void Console::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_loopTimer)
    {
        if (m_game && m_isRunnig)
            updateGame();
    }
}

void Console::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_1)
    {
        createGame(GameSnake);
        return;
    }
    else if (event->key() == Qt::Key_2)
    {
        createGame(GameRaycasting);
        return;
    }
    else if (event->key() == Qt::Key_Escape)
    {
        closeGame();
        return;
    }
    else if (event->key() == Qt::Key_Space)
    {
        m_isRunnig = !m_isRunnig;
        return;
    }

    if (m_game && m_isRunnig)
        m_game->keyPressEvent(convertQtKeyToGameKey(event->key()));
}


