#include "sdldecl.h"
#include "powerups.h"
#include "marioinfo.h"
#include "camera.h"
#include "screen.h"

int handleevent();

void rungame()
{
    while(1)
    {

        if (handleevent() == SDL_QUIT) break;
        //logic
        handlemariomotion();
        handlecameramotion(); /* move camera relative to the position of mario */
        animatepowerups();

        //rendering
        render(); /* to screen */
        SDL_Delay(10);
    }
}
