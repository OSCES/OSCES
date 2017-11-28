#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Display.h"
#include "PaintEngine.h"

#include <QWidget>

class OscesCore;

class Simulator : public QWidget
{
    Q_OBJECT

public:
    Simulator(QWidget *parent = 0);
    ~Simulator();

    static void presentListener(void *context);

protected:
    bool event(QEvent *event);
    void paintEvent(QPaintEvent *e);
    void closeEvent(QCloseEvent *e);

private:
    OscesCore *m_oscesCore;
};

#endif // SIMULATOR_H
