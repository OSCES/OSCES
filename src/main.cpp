#include "Simulator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Simulator oscesCoreSimulator;
    oscesCoreSimulator.show();

    return a.exec();
}
