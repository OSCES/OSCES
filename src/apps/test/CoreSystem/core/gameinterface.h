#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

class DisplayInterface;

class GameInterface
{
public:
    virtual ~GameInterface() {}

    virtual void update() = 0;
    virtual void keyPressEvent() = 0;
};

//enum Key
//{
//    Key_Up,
//    Key_Right,
//    Key_Down,
//    Key_Left
//};

//class DisplayInterface;

//class GameInterface
//{
//public:
//    virtual void setDisplay(DisplayInterface *display) = 0;
//    virtual void initialize() = 0;

//    virtual void run() = 0;
//    virtual void keyPressEvent(int key) = 0;

//    virtual ~GameInterface() {}
//};

#endif // GAMEINTERFACE_H
