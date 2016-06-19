#include "screeninfo.h"
#include "sdldecl.h"
#include "tileinfo.h"
#include "spritespluslevelexternals.h"

SDL_Surface *screen;

void initscreen()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BITS,SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Mario",0);
}

void render()
{
    SDL_FillRect(screen,&screen->clip_rect,0xFFFFFF);
    renderlevel();
    SDL_Flip(screen);
}

void renderlevel()
{
    renderquestionmark();
    renderpipe();
    renderbrick();
    rendergrass();
    rendergroundgrass();
    renderimmovablebrick();
    rendermario();
    for (int i=0; i<TOTAL_VERT_TILES; i++) /*x pos */
    {
        for (int j=0; j<TOTAL_HORZ_TILES; j++) /*y pos */
        {
            int spritetype;
            if ((spritetype=levelmap[i][j])==TILE_EMPTY) continue; /*skip rendering empty tiles */
            switch(spritetype)
            {
            case 10: /* for question mark */

                break;
            case 13:

                break;
            case 19:
            case 22:
            case 25:
                break;
            case 0:
            case 2:
            case 4:

                break;
            case 28:
            case 29:
            case 30:

                break;
            case 31:
            case 32:
            case 33:
            case 34:
                break;
            default :
            {
                SDL_Rect dstrect = {j*16,i*16};
                //SDL_UpperBlit(levelspritesheet,0,screen,&(SDL_Rect){0,0});
                SDL_UpperBlit(levelspritesheet,&spriterects[spritetype],screen,&dstrect);
            }
            break;
            }

        }
    }
}
