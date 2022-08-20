#include "camera.h"
#include "screen.h"
#include "marioinfo.h"
CAMERA camera;

bool checkcameramotion;

void initcamera()
{
    camera.rect.x=0;
    camera.rect.y=0;
    camera.rect.w = SCREEN_WIDTH;
    camera.rect.h = SCREEN_HEIGHT;
    camera.xspeed=camera.yspeed=0;
    camera.direction.down=camera.direction.up=camera.direction.left=camera.direction.right=false;
}

/*calculates position of object relative to camera */
void calculaterelativeposition(SDL_Rect *dest)
{
dest->x =  dest->x-camera.rect.x;
dest->y =  dest->y-camera.rect.y;
}

void handlecameramotion()
{
    extern MARIO mario;

    if (mario.position.x>camera.rect.x + camera.rect.w/2) camera.rect.x=mario.position.x - camera.rect.w/2 ;



}



void cameratest()
{
    extern SDL_Event event;
       if (event.type==SDL_KEYDOWN)
            {

                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    break;
                case SDLK_LEFT:
                    camera.direction.left=true;
                    break;
                case SDLK_RIGHT:
                    camera.direction.right=true;
                    break;

                default:
                    break;
                }
            }
            else if (event.type==SDL_KEYUP)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    camera.direction.left = false;
                    break;
                case SDLK_RIGHT:
                    camera.direction.right = false;
                    break;

                    break;
                default:
                    break;
                }

            }
}
