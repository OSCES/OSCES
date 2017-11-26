#ifndef OSCES_H
#define OSCES_H

class OscesPrivate;

class Display;
class SysTimer;

class Osces
{
public:
    Osces();
    ~Osces();

public:
    bool init();

    int exec();

    Display* display();
    SysTimer* sysTimer();

private:
    OscesPrivate *d_ptr;
};

#endif // OSCES_H
