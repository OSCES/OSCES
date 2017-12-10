#include "System.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    System w;
    w.show();

    return a.exec();
}
