#include "Osces.h"
#include "OscesDefs.h"

// Greate host and board Osces.cpp
// host.cpp

class OscesPrivate
{
public:
    OscesPrivate()
    {

    }

    Display *display;
    SysTimer *sysTimer;
};

Osces::Osces() :
    d_ptr(new OscesPrivate)
{
}

Osces::~Osces()
{
}

bool Osces::init()
{
    // init clocks
    // init kernel
    // init private data
}

int Osces::exec()
{
    int argc = 0;
    char **argv = 0;

    // start app
    int ret = osces_main(argc, argv);

    return ret;
}

Display *Osces::display()
{

}

SysTimer *Osces::sysTimer()
{

}
