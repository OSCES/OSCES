#ifndef RAYCASTING_H
#define RAYCASTING_H

#include "GameInterface.h"

class Raycasting : public GameInterface
{
    enum Direction
    {
        Up,
        Right,
        Down,
        Left,
    };

public:
    Raycasting();
    ~Raycasting();

    void setDisplay(DisplayInterface *display);
    void initialize();

    void run();
    void keyPressEvent(int key);

private:
    float m_x;
    float m_y;
    float m_dirX; //initial direction vector
    float m_dirY;
    float m_planeX; //the 2d raycaster version of camera plane
    float m_planeY;
    DisplayInterface *m_display;
    Direction m_direction;
};

#endif // RAYCASTING_H
