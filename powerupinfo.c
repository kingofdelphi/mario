
#include "powerups.h"
#include "directions.h"

QUESTIONS questionpowerlist;
BRICKS brickpowerlist;
GRASSES grasspowerlist;
GROUNDGRASSES groundgrasslist;
IMMOVABLEBRICKS immovablebricklist;
PIPES pipelist;

void slidequestionmark(QUESTIONMARK *questionmark);
void initquestlist()
{
    questionpowerlist.total=0;
    questionpowerlist.animframe=0;
}

void initpipelist()
{
    pipelist.total=0;
}

void initbricklist()
{
    brickpowerlist.total=0;
    brickpowerlist.animframe=0;
}

void initgrasslist()
{
    grasspowerlist.total=0;
    grasspowerlist.animframe=0;
}

void initgroundgrasslist()
{
    groundgrasslist.total=0;
}

void initimmovablebricklist()
{
    immovablebricklist.total=0;
}

void initializequestionmarkpowerup(QUESTIONMARK *questionmarkpower,int x, int y)
{
    questionmarkpower->curframe =0;
    questionmarkpower->framedir = LEFT;
    questionmarkpower->powerupeaten=false;
    questionmarkpower->poweruppos.x =x;
    questionmarkpower->poweruppos.y = y;
    questionmarkpower->poweruppos.w =16;
    questionmarkpower->poweruppos.h = 16;
    questionmarkpower->slidingup=false;
    questionmarkpower->slidingspeed=0;
    questionmarkpower->coinhit.coinanim=false;
    questionmarkpower->coinhit.currentframe=0;

}

void initializegrasspowerup(GRASS *grasspower,int x, int y,int grasstype)
{
    grasspower->curframe =0;
    grasspower->framedir = LEFT;
    grasspower->poweruppos.x =x;
    grasspower->poweruppos.y = y;
    grasspower->poweruppos.w =16;
    grasspower->poweruppos.h = 16;
    grasspower->grasstype=grasstype;
}

void initializegroundgrasspowerup(GROUNDGRASS *grasspower,int x, int y,int grasstype)
{
    grasspower->poweruppos.x =x;
    grasspower->poweruppos.y = y;
    grasspower->poweruppos.w =16;
    grasspower->poweruppos.h = 16;
    grasspower->grasstype=grasstype;
}

void initializebrickpowerup(BRICK *brickpower,int x, int y)
{
    brickpower->blasting=false;
    brickpower->powerupeaten=false;
    brickpower->poweruppos.x =x;
    brickpower->poweruppos.y = y;
    brickpower->poweruppos.w =16;
    brickpower->poweruppos.h = 16;
    brickpower->slidingup=false;
    brickpower->slidingspeed=0;
}

void initializeimmovablebrickpowerup(IMMOVABLEBRICK *brickpower,int x, int y,int type)
{
    brickpower->poweruppos.x =x;
    brickpower->poweruppos.y = y;
    brickpower->poweruppos.w =16;
    brickpower->poweruppos.h = 16;
    brickpower->type=type;
}

void initializepipepowerup(PIPE *pipepower,int x, int y,int type)
{
    pipepower->poweruppos.x =x;
    pipepower->poweruppos.y = y;
    pipepower->poweruppos.w =16;
    pipepower->poweruppos.h = 16;
    pipepower->type=type;
}


void forwardframequestionmark(QUESTIONS *questionlist,int index)
{

    switch( questionlist->questionmarkpower[index].framedir)
    {
    case LEFT:
        questionlist->questionmarkpower[index].curframe--;
        if (questionlist->questionmarkpower[index].curframe <0)
        {
            questionlist->questionmarkpower[index].curframe=0;
            questionlist->questionmarkpower[index].framedir = RIGHT;
        }
        break;
    case RIGHT:
        questionlist->questionmarkpower[index].curframe++;
        if (questionlist->questionmarkpower[index].curframe >2)
        {
            questionlist->questionmarkpower[index].curframe=2;
            questionlist->questionmarkpower[index].framedir = LEFT;
        }
        break;
    default:
        break;
    }

}


void forwardframegrass(GRASSES *grasslist,int index)
{
    switch( grasslist->grasspower[index].framedir)
    {
    case LEFT:
        grasslist->grasspower[index].curframe--;
        if (grasslist->grasspower[index].curframe <0)
        {
            grasslist->grasspower[index].curframe=0;
            grasslist->grasspower[index].framedir = RIGHT;
        }
        break;
    case RIGHT:
        grasslist->grasspower[index].curframe++;
        if (grasslist->grasspower[index].curframe >2)
        {
            grasslist->grasspower[index].curframe=2;
            grasslist->grasspower[index].framedir = LEFT;
        }
        break;
    default:
        break;
    }

}
/*handle question mark frames for animation */
void handlequestionmarks()
{
    if (questionpowerlist.animframe <QUESTIONS_ANIM_FRAMES)
    {
        questionpowerlist.animframe++;
    }
    else /* time has come to forward animation frames */
    {
        questionpowerlist.animframe=0;

        for (int i=0; i<questionpowerlist.total; i++)
        {
            if (!questionpowerlist.questionmarkpower[i].powerupeaten) /* if powerup has been eaten no need to animate */
                forwardframequestionmark(&questionpowerlist,i);
            if (questionpowerlist.questionmarkpower[i].slidingup)
            {
                slidequestionmark(&questionpowerlist.questionmarkpower[i]);

            }
        }
    }
}

void slidequestionmark(QUESTIONMARK *questionmark)
{
if (questionmark->slidedir==UP)
{
    questionmark->slideheight-=SLIDINGSPEED;
     if (questionmark->slideheight <=-SLIDESHIFT) questionmark->slidedir=DOWN;
}
else
{
    questionmark->slideheight+=SLIDINGSPEED;
    if (questionmark->poweruppos.y+questionmark->slideheight>=questionmark->poweruppos.y )
    {

        questionmark->slidingup=false;
    }
}
}

void handlegrasses()
{
    if (grasspowerlist.animframe <GRASS_ANIM_FRAME)
    {
        grasspowerlist.animframe++;
    }
    else
    {
        grasspowerlist.animframe=0; /* time has come to forward animation frames */

        for (int i=0; i<grasspowerlist.total; i++)
        {
            forwardframegrass(&grasspowerlist,i);
        }
    }
}

/* for all power animations */
void animatepowerups()
{
    handlequestionmarks();
    handlegrasses();


}


void initallpowerups()
{
     initquestlist();
    initbricklist(); /*movable and breakable brick list */
    initgrasslist();
    initgroundgrasslist();
    initimmovablebricklist();
    initpipelist();
}
