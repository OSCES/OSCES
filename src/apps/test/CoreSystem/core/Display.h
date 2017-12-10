#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QImage>
#include "DisplayInterface.h"

class QPainter;

class Display : public DisplayInterface,
                public QWidget
{
public:
    explicit Display(QWidget *parent = 0);
    ~Display();

    int width();
    int height();

    void drawLine(int x1, int y1, int x2, int y2, Rgb color = rgb(255, 255, 255));
    void drawRect(int x, int y, int w, int h, Rgb color = rgb(255, 255, 255));

    void invalidate();
    void present();

private:
    void resizeRenderSurface(const QSize &newSize);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    QImage m_renderSurface;
};

#endif // DISPLAY_H
