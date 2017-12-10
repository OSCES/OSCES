#include "Console.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Console console;
    console.show();

    return a.exec();
}

//int main(int argc, char* argv[]) {
//    //    init stuff
//    QApplication app(argc, argv);

//    while(game.isRunning())
//    {
//        app.processEvents(); //(a is a QApplication created during the init, should use a better name i guess)
//        int timeSinceLastUpdate = lastUpdate.msecsTo(QTime::currentTime());
//        while (timeSinceLastUpdate > updateTimeStep)
//        {
//            game.update();
//            timeSinceLastUpdate -= updateTimeStep;
//            lastUpdate = lastUpdateaddMSecs(updateTimeStep);
//        }
////        renderer.setInterpolateFraction(static_cast<float>(timeSinceLastUpdate) / static_cast<float>updateTimeStep);
////        renderer.renderGameObjects();
////        renderer.renderGUI();
////        renderer.swap();
//    }

//    return app.exit();
//}
