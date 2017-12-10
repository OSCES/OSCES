#include "OscesCore.h"
#include "Display.h"
#include "VideoSystem.h"
#include "Keyboard.h"

extern int osces_main(int, char **);

#ifdef WIN32
#include <windows.h>
HANDLE     g_AppThreadId;
DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
    (void)lpParam;
    return osces_main(0, '\0');
}
#else
#include <sys/time.h>
#include <pthread.h>
static pthread_t AppThreadId = 0;
void* AppThread(void *)
{
    osces_main(0, '\0');
    return 0;
}
#endif

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
#ifdef WIN32
    WaitForSingleObject(g_AppThreadId, INFINITE);
#else
    pthread_join(AppThreadId, 0);
#endif

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
#ifdef WIN32
    g_AppThreadId = CreateThread(NULL, 0, MyThreadFunction, 0, 0, 0);
#else
    pthread_create(&AppThreadId, 0, AppThread, 0);
#endif
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

#ifdef WIN32
    WaitForSingleObject(g_AppThreadId, INFINITE);
#else
    if (AppThreadId > 0)
        pthread_join(AppThreadId, 0);
#endif
}

unsigned long OscesCore::tickCount()
{
#ifdef WIN32
    return GetTickCount();
#else
    struct timeval tv;
    if(gettimeofday(&tv, NULL) != 0)
        return 0;

    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
#endif
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
