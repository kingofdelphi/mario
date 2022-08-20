#include "screeninfo.h"
#include "sdldecl.h"
#include "render.h"
#include "tileinfo.h"
#include "spritespluslevelexternals.h"

SDL_Surface *screen;

SDL_Window* window = NULL;

void initscreen()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow( "Mario", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    screen = SDL_GetWindowSurface(window);
}

void render()
{
    SDL_FillRect(screen,&screen->clip_rect,0xFFFFFF);
    renderlevel();
    SDL_UpdateWindowSurface(window);
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
