#include "Raycasting.h"
#include "DisplayInterface.h"
#include <stdint.h>
#include <math.h>

#define mapWidth  24
#define mapHeight 24

uint8_t worldMap[mapWidth][mapHeight]=
{
  {1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4},
  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,4},
  {2,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {3,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,2},
  {4,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,4},
  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {2,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {3,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
  {4,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
  {3,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {4,1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4,1,2,3}
};

Raycasting::Raycasting() :
    m_x(12),
    m_y(12),
    m_dirX(-1),
    m_dirY(0),
    m_planeX(0),
    m_planeY(0.61)
{
}

Raycasting::~Raycasting()
{
}

void Raycasting::setDisplay(DisplayInterface *display)
{
    m_display = display;
}

void Raycasting::initialize()
{

}

void Raycasting::run()
{
    for (int x = 0; x < m_display->width(); ++x)
    {
        //calculate ray position and direction
        double cameraX = 2 * x / double(m_display->width()) - 1; //x-coordinate in camera space
        double rayPosX = m_x;
        double rayPosY = m_y;
        double rayDirX = m_dirX + m_planeX * cameraX;
        double rayDirY = m_y + m_planeY * cameraX;
        //which box of the map we're in
        int mapX = int(rayPosX);
        int mapY = int(rayPosY);

        //length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        //length of ray from one x or y-side to next x or y-side
        double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
        double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
        double perpWallDist;

        //what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; //was there a wall hit?
        int side; //was a NS or a EW wall hit?
        //calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (rayPosX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
        }

        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (rayPosY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
        }

        //perform DDA
        while (hit == 0)
        {
            //jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if (worldMap[mapX][mapY] > 0)
                hit = 1;
        }

        //Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
        if (side == 0)
            perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
        else
            perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);

        //Calculate height of line to draw on screen
        int lineHeight = abs((long double)(m_display->height() / perpWallDist));

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + m_display->height() / 2;
        if (drawStart < 0)
            drawStart = 0;

        int drawEnd = lineHeight / 2 + m_display->height() / 2;
        if (drawEnd >= m_display->height())
            drawEnd = m_display->height() - 1;

        //choose wall color
        Rgb color;
        switch(worldMap[mapX][mapY])
        {
        case 1:  color = rgb(0xFF, 0x00, 0x00); break; //red
        case 2:  color = rgb(0x00, 0xFF, 0x00); break; //green
        case 3:  color = rgb(0x00, 0x00, 0xFF); break; //blue
        case 4:  color = rgb(0xFF, 0xFF, 0xFF); break; //white
        default: color = rgb(0xFF, 0xF2, 0x00); break; //yellow
        }

        //give x and y sides different brightness
        if (side == 1)
//            color = rgb(color.Red / 2, color.Green / 2, color.Blue / 2);
            color = color >> 1;

        //draw the pixels of the stripe as a vertical line
        m_display->drawLine(x, drawStart, x, drawEnd, color);
    }
}

void Raycasting::keyPressEvent(int key)
{
    //speed modifiers
    double moveSpeed = 0.5; //the constant value is in squares/second
    double rotSpeed  = 0.5; //the constant value is in radians/second

    switch (key)
    {
    case Key_Up:
    {
        if(worldMap[int(m_x - m_dirX * moveSpeed)][int(m_y)] == false)
            m_x -= m_dirX * moveSpeed;
        if(worldMap[int(m_x)][int(m_y - m_dirY * moveSpeed)] == false)
            m_y -= m_dirY * moveSpeed;
        break;
    }
    case Key_Right:
    {
        //both camera direction and camera plane must be rotated
        double oldDirX = m_dirX;
        m_dirX = m_dirX * cos(-rotSpeed) - m_dirY * sin(-rotSpeed);
        m_dirY = oldDirX * sin(-rotSpeed) + m_dirY * cos(-rotSpeed);
        double oldPlaneX = m_planeX;
        m_planeX = m_planeX * cos(-rotSpeed) - m_planeY * sin(-rotSpeed);
        m_planeY = oldPlaneX * sin(-rotSpeed) + m_planeY * cos(-rotSpeed);
        break;
    }
    case Key_Down:
    {
        if (worldMap[int(m_x + m_dirX * moveSpeed)][int(m_y)] == false)
            m_x += m_dirX * moveSpeed;
        if (worldMap[int(m_x)][int(m_y + m_dirY * moveSpeed)] == false)
            m_y += m_dirY * moveSpeed;
        break;
    }
    case Key_Left:
    {
        //both camera direction and camera plane must be rotated
        double oldDirX = m_dirX;
        m_dirX = m_dirX * cos(rotSpeed) - m_dirY * sin(rotSpeed);
        m_dirY = oldDirX * sin(rotSpeed) + m_dirY * cos(rotSpeed);
        double oldPlaneX = m_planeX;
        m_planeX = m_planeX * cos(rotSpeed) - m_planeY * sin(rotSpeed);
        m_planeY = oldPlaneX * sin(rotSpeed) + m_planeY * cos(rotSpeed);
        break;
    }
    default:
        ;
    }
}
