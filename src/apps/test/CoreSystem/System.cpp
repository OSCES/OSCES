#include "System.h"
#include "core/GameConsole.h"
#include <QListWidget>
#include <QVBoxLayout>
#include <QDebug>

System::System(QWidget *parent) :
    QWidget(parent /*Qt::FramelessWindowHint*/),
    m_gameConsole(0)
{
    m_view = new QListWidget(this);
    m_view->setFrameShape(QFrame::NoFrame);
    connect(m_view, SIGNAL(clicked(QModelIndex)), this, SLOT(selectGame(QModelIndex)));

    m_gameConsole = new GameConsole;
    m_gameConsole->hide();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(QMargins());
    layout->addWidget(m_view);

    initGameList();
    resize(800, 480);
}

System::~System()
{
    delete m_gameConsole;
}

void System::selectGame(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    m_gameConsole->setGame();
    m_gameConsole->show();
}

void System::initGameList()
{
    QStringList items;
    items << "Snake"
          << "Super Mario Bros"
          << "Contra";

    m_view->addItems(items);
    m_view->setCurrentRow(0);
}

