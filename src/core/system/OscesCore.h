#ifndef OSCESCORE_H
#define OSCESCORE_H

#include "InterruptManager.h"
#include "KeyboardInterface.h"

class AbstractDisplay;
class VideoSystem;
class SysTimer;
class OscesCore
{
public:
    OscesCore();
    ~OscesCore();

public:
    bool initialize();
    int exec();
    void stop();

    static unsigned long tickCount();
    static AbstractKeyboard* keyboard(); // do not use from app
    static VideoSystem* videoSystem();
    static bool applicationRuning();

    static void setActiveInputHandler(void *context, KeyEventHandler handler);

private:
    void keyEvent(const KeyEvent &event);

    static void keyEventHandler(void *context, const KeyEvent &event);

private:
    static InterruptManager m_interruptManager;
    static AbstractDisplay *m_display;
    static AbstractKeyboard *m_keyBoard;
    static VideoSystem *m_videoSystem;
    static bool m_running;

    static void *m_activeAppContext;
    static KeyEventHandler m_activeAppKeyHandler;
};

#endif // OSCESCORE_H
