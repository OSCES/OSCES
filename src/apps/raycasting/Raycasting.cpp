
#include "Osces.h"
#include "OscesCore.h"
#include "VideoSystem.h"
#include "PaintEngine.h"
#include "AbstractDisplay.h"
#include "KeyCode.h"

#include <stdint.h>
#include <math.h>

static const uint8_t MapWidth = 24;
static const uint8_t MapHeight = 24;

uint8_t WorldMap[MapWidth][MapHeight]=
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

enum Direction
{
    None,
    Left,
    Right,
    Up,
    Down,
};

static Direction g_Diraction = Left;

void RayKeyEventHandler(void *context, const KeyEvent &event)
{
    if (event.eventType == KeyReleased)
        return;

    switch (event.key.keyCode)
    {
    case Key_Up   : g_Diraction = Up   ; break;
    case Key_Down : g_Diraction = Down ; break;
    case Key_Right: g_Diraction = Right; break;
    case Key_Left : g_Diraction = Left ; break;

    default:
        break;
    };
}

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    AbstractDisplay *display = OscesCore::videoSystem()->display();
    OscesCore::setActiveInputHandler(0, RayKeyEventHandler);

    int displayWidth = display->width();
    int displayHeight = display->height();

    double posX = 22, posY = 12;  //x and y start position
    double dirX = -1, dirY = 0; //initial direction vector
    double planeX = 0, planeY = 0.61; //the 2d raycaster version of camera plane

    int lastTickValue = OscesCore::tickCount();

    PaintEngine paintEngine;
    do
    {
        paintEngine.drawBegin(display);
        paintEngine.setPenColor(black);
        paintEngine.fillRect(0, 0, displayWidth, displayHeight);

        //planeY += 0.001;
        //planeX += 0.001;
        for (int x = 0; x < displayWidth; x++)
        {
            //calculate ray position and direction
            double cameraX = 2 * x / double(displayWidth) - 1; //x-coordinate in camera space
            double rayPosX = posX;
            double rayPosY = posY;
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;
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
                if (WorldMap[mapX][mapY] > 0) hit = 1;
            }
            //Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
            if (side == 0)
                perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
            else
                perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);

            //Calculate height of line to draw on screen
            int lineHeight = abs((long double)(displayHeight / perpWallDist));

            //calculate lowest and highest pixel to fill in current stripe
            int drawStart = -lineHeight / 2 + displayHeight / 2;
            if(drawStart < 0)drawStart = 0;
            int drawEnd = lineHeight / 2 + displayHeight / 2;
            if(drawEnd >= displayHeight)drawEnd = displayHeight - 1;

            //choose wall color
            Color color;
            switch (WorldMap[mapX][mapY])
            {
            case 1:  color = Color(0xFF, 0x00, 0x00); break; //red
            case 2:  color = Color(0x00, 0xFF, 0x00); break; //green
            case 3:  color = Color(0x00, 0x00, 0xFF); break; //blue
            case 4:  color = Color(0xFF, 0xFF, 0xFF); break; //white
            default: color = Color(0xFF, 0xF2, 0x00); break; //yellow
            }

            //give x and y sides different brightness
            if (side == 1)
                color = Color(color.red() / 2, color.green() / 2, color.blue() / 2);

            //draw the pixels of the stripe as a vertical line
            paintEngine.setPenColor(color);
            paintEngine.drawLine(x, drawStart, x, drawEnd);
        }
        
        paintEngine.drawEnd();

        //speed modifiers
        double moveSpeed = 0.5; //the constant value is in squares/second
        double rotSpeed  = 0.1; //the constant value is in radians/second

        switch (g_Diraction)
        {
        case Up   :
            {
                if(WorldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
                if(WorldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;

                break;
            }
        case Down :
            {
                if(WorldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
                if(WorldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;

                break;
            }
        case Right:
            {
                //both camera direction and camera plane must be rotated
                double oldDirX = dirX;
                dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
                dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
                double oldPlaneX = planeX;
                planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
                planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);

                break;
            }
        case Left :
            {
                //both camera direction and camera plane must be rotated
                double oldDirX = dirX;
                dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
                dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
                double oldPlaneX = planeX;
                planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
                planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);

                break;
            }
        default:
            break;
        }

        g_Diraction = None;
        
    }
    while (OscesCore::applicationRuning());

    return 0;
}
