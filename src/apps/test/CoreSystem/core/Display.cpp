#include "Display.h"
#include <QPainter>
#include <QResizeEvent>

Display::Display(QWidget *parent) :
    QWidget(parent)
{
    QSize size = parent ? parent->size() : QSize();
    m_renderSurface = QImage(size, QImage::Format_ARGB32);

    invalidate();
}

Display::~Display()
{
}

int Display::width()
{
    return m_renderSurface.width();
}

int Display::height()
{
    return m_renderSurface.height();
}

void Display::drawLine(int x1, int y1, int x2, int y2, Rgb color)
{
    QPainter p(&m_renderSurface);
    p.setPen(QColor::fromRgb(color));
    p.drawLine(x1, y1, x2, y2);
}

void Display::drawRect(int x, int y, int w, int h, Rgb color)
{
    QPainter p(&m_renderSurface);
    p.setPen(QColor::fromRgb(color));
    p.drawRect(x, y, w, h);
}

void Display::invalidate()
{
    m_renderSurface.fill(Qt::black);
}

void Display::present()
{
    update();
}

void Display::resizeRenderSurface(const QSize &newSize)
{
    m_renderSurface = QImage(newSize, QImage::Format_ARGB32);
}

void Display::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawImage(0, 0, m_renderSurface);
}

void Display::resizeEvent(QResizeEvent *event)
{
    if (!event->spontaneous())
        resizeRenderSurface(event->size());
    QWidget::resizeEvent(event);
}
