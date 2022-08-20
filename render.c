
#include "render.h"
#include "camera.h"
#include "spritespluslevelexternals.h"
#include "hiddentreasures.h"
/* renders all question mark powerup according to its members */
void cointhitanim(COINHIT *coinhit);

void renderquestionmark()
{
    for (int i=0;i<questionpowerlist.total;i++)
    {
        SDL_Rect dstrect = {questionpowerlist.questionmarkpower[i].poweruppos.x,questionpowerlist.questionmarkpower[i].poweruppos.y};
        int animframe = questionpowerlist.questionmarkpower[i].curframe;
        calculaterelativeposition(&dstrect);
        if (questionpowerlist.questionmarkpower[i].powerupeaten)
        {
           dstrect.y += questionpowerlist.questionmarkpower[i].slideheight;
            SDL_UpperBlit(levelspritesheet,&spriterects[16],screen,&dstrect);
        }
            else
        SDL_UpperBlit(levelspritesheet,&spriterects[10+animframe],screen,&dstrect);
        if (questionpowerlist.questionmarkpower[i].coinhit.coinanim)
            cointhitanim(&questionpowerlist.questionmarkpower[i].coinhit);
    }
}

  void cointhitanim(COINHIT *coinhit)
   {
extern SDL_Rect coinhitrects[];
SDL_Rect dstrc = coinhit->cointhitrect;
calculaterelativeposition(&dstrc);
   SDL_UpperBlit(coinspritesheet,&coinhitrects[coinhit->currentframe],screen,&dstrc);
   if ((++(coinhit->coinanimframe)) > COIN_HIT_ANIM_FRAME) /*for animation delay */
   {
       coinhit->coinanimframe=0;
   coinhit->currentframe++;
   coinhit->cointhitrect.y-=4;
   if (coinhit->currentframe >8) coinhit->coinanim=false;
   }
   }


void renderbrick()
{
    for (int i=0;i<brickpowerlist.total;i++)
    {
        SDL_Rect dstrect = {brickpowerlist.brickpower[i].poweruppos.x,brickpowerlist.brickpower[i].poweruppos.y};
        calculaterelativeposition(&dstrect);
        if (!brickpowerlist.brickpower[i].powerupeaten)
            SDL_UpperBlit(levelspritesheet,&spriterects[13],screen,&dstrect);
    }
}

void renderimmovablebrick()
{
    for (int i=0;i<immovablebricklist.total;i++)
    {
        SDL_Rect dstrect = {immovablebricklist.immovablebrickpower[i].poweruppos.x,immovablebricklist.immovablebrickpower[i].poweruppos.y};
        calculaterelativeposition(&dstrect);
        int immovablebricktype=immovablebricklist.immovablebrickpower[i].type;
            SDL_UpperBlit(levelspritesheet,&spriterects[immovablebricktype],screen,&dstrect);
    }
}

void rendergrass()
{
    for (int i=0;i<grasspowerlist.total;i++)
    {
        int animframe = grasspowerlist.grasspower[i].curframe;
        SDL_Rect dstrect = {grasspowerlist.grasspower[i].poweruppos.x,grasspowerlist.grasspower[i].poweruppos.y+1};
        if (animframe==2) dstrect.y-=1; /*1 pixel down clipping already in third row, check spritesheet */
        calculaterelativeposition(&dstrect);
        int grasstype = grasspowerlist.grasspower[i].grasstype;
        SDL_UpperBlit(levelspritesheet,&spriterects[grasstype+animframe],screen,&dstrect);
    }
}

void renderpipe()
{
    for (int i=0;i<pipelist.total;i++)
    {
        SDL_Rect dstrect = {pipelist.pipepower[i].poweruppos.x,pipelist.pipepower[i].poweruppos.y};
        calculaterelativeposition(&dstrect);
        int pipetype= pipelist.pipepower[i].type;
        SDL_UpperBlit(levelspritesheet,&spriterects[pipetype],screen,&dstrect);
    }
}

void rendergroundgrass()
{
    for (int i=0;i<groundgrasslist.total;i++)
    {
        SDL_Rect dstrect = {groundgrasslist.groundgrasspower[i].poweruppos.x,groundgrasslist.groundgrasspower[i].poweruppos.y};
        calculaterelativeposition(&dstrect);
        int grasstype = groundgrasslist.groundgrasspower[i].grasstype;
        SDL_UpperBlit(levelspritesheet,&spriterects[grasstype],screen,&dstrect);
    }
}
