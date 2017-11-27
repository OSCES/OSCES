#ifndef PLATFORMSCREEN_H
#define PLATFORMSCREEN_H

#include "Screen.h"

class PlatformScreen : public Screen
{
public:
    PlatformScreen();
    ~PlatformScreen();

    bool initialize();

    void present();
};

#endif // PLATFORMSCREEN_H
