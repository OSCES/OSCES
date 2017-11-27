#ifndef OSCES_H
#define OSCES_H

class OscesPrivate;

class VideoDevice;
class SysTimer;

class Osces
{
public:
    Osces();
    ~Osces();

public:
    bool init();

    int exec();

    VideoDevice* display();
    SysTimer* sysTimer();

private:
    OscesPrivate *d_ptr;
};

#endif // OSCES_H
