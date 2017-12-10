#ifndef SYSTEM_H
#define SYSTEM_H

#include <QWidget>

class GameConsole;
class QListWidget;
class QVBoxLayout;

class System : public QWidget
{
    Q_OBJECT

public:
    System(QWidget *parent = 0);
    ~System();

private slots:
    void selectGame(const QModelIndex &index);

private:
    void initGameList();

private:
    GameConsole *m_gameConsole;
    QListWidget *m_view;
};

#endif // SYSTEM_H
