#include "tileinfo.h"
#include "sdldecl.h"
#include "loadresources.h"
#include "spritespluslevelexternals.h"
#include "powerups.h"
SDL_Surface *levelspritesheet;
SDL_Surface *spritedatabase[MAX_IMAGES];
SDL_Surface *coinspritesheet;
/* sprite rects for designing level (excluding characters) */
SDL_Rect spriterects[MAX_IMAGES] =
{
    /*normal grass portion start 0 - 9 */
    {652,39,16,16},{},
    {671,39,16,16},{},
    {690,39,16,16},{},
    {},{},
    {},{},
    /*question powerups 10-12*/
    {686,152,16,16},
    {705,152,16,16},
    {724,152,16,16},
    /*bricks    13 - 15 */
    {686,171,16,16},{705,171,16,16},{724,171,16,16},
    /*eaten bricks     16-18 */
    {686,190,16,16},{705,190,16,16},{724,190,16,16},
    /* animating grass 19-27*/
    {344,34,16,16},{344,51,16,16},{344,68,16,16}, /* first column of grass */
    {363,34,16,16},{363,51,16,16},{363,68,16,16}, /*second column of grass */
    {382,34,16,16},{382,51,16,16},{382,68,16,16}, /* third column of grass */
    /* other bricks (immovable,unbreakable), 28-30*/
    {686,209,16,16},{705,209,16,16},{724,209,16,16},
    /* green pipes 31-34*/
    {572,152,16,16},{572,171,16,16},
    {591,152,16,16},{591,171,16,16}

};
/* loads all the sprites evaluating level map */
void loadresourcesfromlevel()
{
    loadlevelspritesheet();
    loadmariospritesheet();
    SDL_SetColorKey(levelspritesheet,SDL_SRCCOLORKEY,0x004040);
    /*set count of all powerups to zero */
    initallpowerups();
    //if (levelspritesheet ==NULL) MessageBox(0,"couldnt load",0,0);
    for (int i=0; i<TOTAL_VERT_TILES; i++) /* x */
    {
        for (int j=0; j<TOTAL_HORZ_TILES; j++) /* y */
        {
            switch(levelmap[i][j])
            {
            case 10: /* for question mark powerup */
                initializequestionmarkpowerup(&questionpowerlist.questionmarkpower[questionpowerlist.total],j*16,i*16);
                questionpowerlist.total++;
                break;
            case 13: /* for question mark powerup */
                initializebrickpowerup(&brickpowerlist.brickpower[brickpowerlist.total],j*16,i*16);
                brickpowerlist.total++;
                break;
            case 0:
            case 2:
            case 4:
                initializegroundgrasspowerup(&groundgrasslist.groundgrasspower[groundgrasslist.total],j*16,i*16,levelmap[i][j]);
                groundgrasslist.total++;
                break;
            case 19:
            case 22:
            case 25:
                initializegrasspowerup(&grasspowerlist.grasspower[grasspowerlist.total],j*16,i*16,levelmap[i][j]);
                grasspowerlist.total++;
                break;
            case 28:
            case 29:
            case 30:
                initializeimmovablebrickpowerup(&immovablebricklist.immovablebrickpower[immovablebricklist.total],j*16,i*16,levelmap[i][j]);
                immovablebricklist.total++;
                break;
            case 31:
            case 32:
            case 33:
            case 34:
                initializepipepowerup(&pipelist.pipepower[pipelist.total],j*16,i*16,levelmap[i][j]);
                pipelist.total++;
                break;
            default:
                break;
            }
        }
    }
}

void loadlevelspritesheet()
{
        levelspritesheet=IMG_Load("Sprites/Completed Super Mario Bros Super Rip/Level Formations/Objects and Flooring.bmp");

        coinspritesheet = IMG_Load("Sprites/Completed Super Mario Bros Super Rip/Level Formations/Items and Coins.bmp");

        SDL_SetColorKey(coinspritesheet,SDL_SRCCOLORKEY,0x004040);
}
