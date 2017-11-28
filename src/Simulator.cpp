#include "Simulator.h"
#include "OscesCore.h"
#include "VideoSystem.h"
#include <QPainter>
#include <QImage>
#include <QKeyEvent>

Simulator::Simulator(QWidget *parent) :
    QWidget(parent),
    m_oscesCore(new OscesCore)
{
    m_oscesCore->initialize();

    Display *display = static_cast<Display *>(m_oscesCore->videoSystem()->display());
    display->setPresentListener(presentListener, this);

    m_oscesCore->exec();

    setAutoFillBackground(true);
    resize(400, 300);
}

Simulator::~Simulator()
{
    delete m_oscesCore;
}

void Simulator::presentListener(void *context)
{
    Simulator *simulator = static_cast<Simulator *>(context);
    simulator->update();
}

bool Simulator::event(QEvent *event)
{
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    {
        KeyEvent keyEvent;
        keyEvent.eventType = event->type() == QEvent::KeyPress ? KeyPressed : KeyReleased;

        QKeyEvent *key = static_cast<QKeyEvent *>(event);
        switch (key->key())
        {
        case Qt::Key_Up:
            keyEvent.key.keyCode = Key_Up;
            OscesCore::keyboard()->proceedKeyEvent(keyEvent);
            break;
        case Qt::Key_Left:
            keyEvent.key.keyCode = Key_Left;
            OscesCore::keyboard()->proceedKeyEvent(keyEvent);
            break;
        case Qt::Key_Down:
            keyEvent.key.keyCode = Key_Down;
            OscesCore::keyboard()->proceedKeyEvent(keyEvent);
            break;
        case Qt::Key_Right:
            keyEvent.key.keyCode = Key_Right;
            OscesCore::keyboard()->proceedKeyEvent(keyEvent);
            break;
        case Qt::Key_E:
            keyEvent.key.keyCode = Key_E;
            OscesCore::keyboard()->proceedKeyEvent(keyEvent);
            break;
        case Qt::Key_S:
            keyEvent.key.keyCode = Key_S;
            OscesCore::keyboard()->proceedKeyEvent(keyEvent);
            break;
        case Qt::Key_Z:
            keyEvent.key.keyCode = Key_Z;
            OscesCore::keyboard()->proceedKeyEvent(keyEvent);
            break;
        case Qt::Key_X:
            keyEvent.key.keyCode = Key_X;
            OscesCore::keyboard()->proceedKeyEvent(keyEvent);
            break;
        case Qt::Key_Return:
            keyEvent.key.keyCode = Key_Enter;
            OscesCore::keyboard()->proceedKeyEvent(keyEvent);
            break;
        case Qt::Key_Tab:
            keyEvent.key.keyCode = Key_Tab;
            OscesCore::keyboard()->proceedKeyEvent(keyEvent);
            break;
        default:
            ;
        }
        return true;
    }

    return QWidget::event(event);
}

void Simulator::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);

    static int frameCount = 0;

    VideoSystem *videoSystem = m_oscesCore->videoSystem();
    if (videoSystem && videoSystem->displayCount())
    {
        AbstractDisplay *display = videoSystem->display();

        uchar *data = static_cast<uchar *>(display->displayBuffer(Display::FrontBuffer));
        QImage image(data, display->width(), display->height(), QImage::Format_RGB32);

        QPainter p(this);
        p.drawImage(rect(), image);

        p.setPen(Qt::green);
        QTextOption opt;
        opt.setAlignment(Qt::AlignLeft | Qt::AlignTop);
        p.drawText(rect(), QString("Frame: %1\nFPS: %2").arg(++frameCount).arg(display->fpsInfo()), opt);
    }
}

void Simulator::closeEvent(QCloseEvent *e)
{
    m_oscesCore->stop();
    QWidget::closeEvent(e);
}
