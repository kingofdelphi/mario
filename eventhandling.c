
#include "sdldecl.h"
#include "camera.h"
#include "marioinfo.h"
SDL_Event event;

int handleevent()
{

    extern bool checkcameramotion;//checkcameramotion=true;
    extern MARIO mario;
    if (SDL_PollEvent(&event))
    {
        if (event.type==SDL_QUIT || event.key.keysym.sym ==SDLK_ESCAPE) return SDL_QUIT;
        if (checkcameramotion)
        {
            cameratest();
        }
        else
            /* set mario states */
            if (event.type==SDL_KEYDOWN)
            {

                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    mario.direction.left=true;
                    mario.direction.right=false;
                    mario.standdirection=LEFT;
                    mario.framedir=LEFT;
                    break;
                case SDLK_RIGHT:
                    mario.direction.right=true;
                    mario.direction.left=false;
                     mario.standdirection=RIGHT;
                    mario.framedir=LEFT;
                    break;
                case SDLK_SPACE:
                    setmariojumpstate();
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
                    mario.direction.left = false;
                    break;
                case SDLK_RIGHT:
                    mario.direction.right = false;
                    break;

                default:
                    break;
                }



            }
    }
    return 0;

}
