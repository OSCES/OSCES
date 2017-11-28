#include "OscesCore.h"
#include "Display.h"
#include "VideoSystem.h"
#include "Keyboard.h"

extern int osces_main(int, char **);

#include <windows.h>
HANDLE     g_AppThreadId;
DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
    (void)lpParam;
    return osces_main(0, '\0');
}

AbstractDisplay *OscesCore::m_display = new Display;
AbstractKeyboard *OscesCore::m_keyBoard = new Keyboard;
VideoSystem *OscesCore::m_videoSystem = new VideoSystem;
bool OscesCore::m_running = false;
void *OscesCore::m_activeAppContext = 0;
KeyEventHandler OscesCore::m_activeAppKeyHandler = 0;

OscesCore::OscesCore()
{
}

OscesCore::~OscesCore()
{
    WaitForSingleObject(g_AppThreadId, INFINITE);

    m_keyBoard->unRegisterCallBack(keyEventHandler);

    delete m_keyBoard;
    delete m_videoSystem;
}

bool OscesCore::initialize()
{
    m_interruptManager.initialize();
    m_keyBoard->registerCallBack(this, keyEventHandler);

    if (m_display && m_display->initialize())
        m_videoSystem->addDisplay(m_display);

    return true;
}

int OscesCore::exec()
{
    stop(); // stop active app

    // start app
    m_running = true;
    g_AppThreadId = CreateThread(NULL, 0, MyThreadFunction, 0, 0, 0);
//    int argc = 0;
//    char **argv = 0;
//    int ret = osces_main(argc, argv);
    return 0;
}

void OscesCore::stop()
{
    m_running = false;
    m_activeAppContext = 0;
    m_activeAppKeyHandler = 0;

    WaitForSingleObject(g_AppThreadId, INFINITE);
}

unsigned long OscesCore::tickCount()
{
    return GetTickCount();
}

VideoSystem *OscesCore::videoSystem()
{
    return m_videoSystem;
}

bool OscesCore::applicationRuning()
{
    return m_running;
}

void OscesCore::setActiveInputHandler(void *context, KeyEventHandler handler)
{
    m_activeAppContext = context;
    m_activeAppKeyHandler = handler;
}

void OscesCore::keyEvent(const KeyEvent &event)
{
    // send event to active app;
    switch (event.key.keyCode)
    {
    case Key_S: stop(); return;
    case Key_E: exec(); return;
    default:
        ;
    }

    if (m_activeAppKeyHandler)
        m_activeAppKeyHandler(m_activeAppContext, event);
}

void OscesCore::keyEventHandler(void *context, const KeyEvent &event)
{
    OscesCore *core = static_cast<OscesCore *>(context);
    core->keyEvent(event);
}

AbstractKeyboard *OscesCore::keyboard()
{
    return m_keyBoard;
}
