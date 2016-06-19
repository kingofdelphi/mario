#include "marioinfo.h"
#include "directions.h"
#include "spritespluslevelexternals.h"
#include "powerups.h"
const double xInc = 0.5;
const double xDecay = 0.25;
const double maxxSpeed=6;
const double marioinitialyVel = 25;
const double gravity = 3;
SDL_Rect mariorects[MAX_IMAGES] =
{
    /* jumping positions, right and left resp 0-1*/
    {49,50,16,16},{70,50,16,16},
    /* dying 2*/
    {93,50,16,16},
    /*small mario walk steps, right and left respectively,3-8 */
    {7,93,12,15},{28,93,12,15},{47,92,15,16},
    {70,93,12,15},{91,93,12,15},{111,92,15,16},
    /* sliding  mario 9-10*/
    {134,134,14,16}, {155,134,14,16}
};
SDL_Rect slidedustrects[3] =
{
    {113,57,8,8},{124,57,8,8},{135,57,8,8}
};

SDL_Rect coinhitrects[9] =
{
    {3,73,20,16}, {24,73,20,16}, {45,73,20,16}, {66,73,20,16}, {87,73,20,16},
    {108,73,20,16}, {129,73,20,16}, {150,73,20,16},{171,73,20,16}
};

MARIO mario;
int coinseaten;
SDL_Surface *mariospritesheet;

void initializemario()
{
    mario.animframe=0;
    mario.currentframe=0;
    mario.direction.right=false;
    mario.direction.left=false;
    mario.position.x =100;
    mario.position.y=240;
    mario.type = small;
    mario.state = standing;
    mario.imageindex=3;
    mario.position.w =mariorects[mario.imageindex].w;
    mario.position.h =mariorects[mario.imageindex].h;
    mario.standdirection=RIGHT;
    mario.jumpstate=none;
    mario.running=false;
    mario.xspeed=mario.yspeed=0;
    mario.sliding=false;
}

void loadmariospritesheet()
{
    mariospritesheet = IMG_Load("Sprites/Completed Super Mario Bros Super Rip/Characters/Super Mario.bmp");
    SDL_SetColorKey(mariospritesheet,SDL_SRCCOLORKEY,0x004040);
}

void rendermario()
{
    SDL_Rect dstrect= {mario.position.x,mario.position.y};
    calculaterelativeposition(&dstrect); /* obtain relative position of mario with respect to camera */
    int jumpframe = (mario.standdirection==RIGHT)?(0):(1);
    switch(mario.type)
    {
    case small:
        if (mario.sliding && mario.jumpstate==none)
        {
            SDL_UpperBlit(mariospritesheet,&mariorects[10-jumpframe],screen,&dstrect);
        }
        else if (mario.jumpstate !=none)  /* if mario is jumping or falling */
        {

            SDL_UpperBlit(mariospritesheet,&mariorects[jumpframe],screen,&dstrect);
        }
        else
            SDL_UpperBlit(mariospritesheet,&mariorects[3+jumpframe*3+mario.currentframe],screen,&dstrect);
        break;
    default:
        break;
    }
    if (mario.sliding && mario.jumpstate==none) displayslidinganimation();
}

void forwardmariowalkframe()
{
    if (mario.framedir==LEFT)
    {
        mario.currentframe--;
        if (mario.currentframe <0)
        {
            mario.currentframe =0;
            mario.framedir=RIGHT;
        }
    }
    else if (mario.framedir==RIGHT)
    {
        mario.currentframe++;
        if (mario.currentframe >2)
        {
            mario.currentframe =2;
            mario.framedir=LEFT;
        }
    }

}

void handlemariomotion()
{

    mario.animframe++; /* for animation delay */
    if (mario.animframe >=MARIO_ANIM_FRAME)
    {
        mario.animframe=0;
        handlemariohorizontalmotion();
        handlemarioverticalmotion();
    }
    if (mario.sliding) SDL_WM_SetCaption("sliding",0);
    else SDL_WM_SetCaption("not sliding",0);
}

bool checkcollisionwithmoveablebricks(SDL_Rect **collidedobject,SDL_Rect *mariorect,int collisionchecktype)
{
    /*check collision with movable or destroyable bricks */
    for (int i=0; i<brickpowerlist.total; i++)
    {
        if (checkcollision(&brickpowerlist.brickpower[i].poweruppos,mariorect))
        {
            *collidedobject = &brickpowerlist.brickpower[i].poweruppos;
            return true;
        }
    }
    return false;
}

bool checkcollisionwithimmoveablebricks(SDL_Rect **collidedobject,SDL_Rect *mariorect,int collisionchecktype)
{

    for (int i=0; i<immovablebricklist.total; i++)
    {
        if (checkcollision(&immovablebricklist.immovablebrickpower[i].poweruppos,mariorect))
        {
            *collidedobject = &immovablebricklist.immovablebrickpower[i].poweruppos;
            return true;
        }
    }
    return false;
}

bool checkcollisionwithquestionmarks(SDL_Rect **collidedobject,SDL_Rect *mariorect,int collisionchecktype)
{
    for (int i=0; i<questionpowerlist.total; i++)
    {
        if (checkcollision(&questionpowerlist.questionmarkpower[i].poweruppos,mariorect))
        {
            if (collisionchecktype==VERT && mario.jumpstate==jumping && !questionpowerlist.questionmarkpower[i].powerupeaten)
            {
            questionpowerlist.questionmarkpower[i].powerupeaten=true;
            questionpowerlist.questionmarkpower[i].slidingup=true;
            questionpowerlist.questionmarkpower[i].slidedir=UP;
            questionpowerlist.questionmarkpower[i].coinhit.coinanim=true;
            questionpowerlist.questionmarkpower[i].coinhit.cointhitrect = questionpowerlist.questionmarkpower[i].poweruppos;
            questionpowerlist.questionmarkpower[i].coinhit.cointhitrect.y -=coinhitrects[0].h+15;
            questionpowerlist.questionmarkpower[i].coinhit.cointhitrect.x -= questionpowerlist.questionmarkpower[i].coinhit.cointhitrect.w/2 - spriterects[10].w/2+3;
             coinseaten++;
            }

            *collidedobject = &questionpowerlist.questionmarkpower[i].poweruppos;

            return true;
        }
    }
    return false;
}

bool checkcollisionwithpipes(SDL_Rect **collidedobject,SDL_Rect *mariorect,int collisionchecktype)
{
    for (int i=0; i<pipelist.total; i++)
    {
        if (checkcollision(&pipelist.pipepower[i].poweruppos,mariorect))
        {
            *collidedobject = &pipelist.pipepower[i].poweruppos;
            return true;
        }
    }
    return false;
}

bool checkcollisionwithgroundgrass(SDL_Rect **collidedobject,SDL_Rect *mariorect,int collisionchecktype)
{
    for (int i=0; i<groundgrasslist.total; i++)
    {
        if (checkcollision(&groundgrasslist.groundgrasspower[i].poweruppos,mariorect))
        {
            *collidedobject = &groundgrasslist.groundgrasspower[i].poweruppos;
            return true;
        }
    }
    return false;
}

/* checks collision with all the objects on screen */
bool checkmariocollision(SDL_Rect **collidedobjectrect,SDL_Rect *mariorect,int collisionchecktype)
{
    /*check collision with movable or destroyable bricks */
    if (checkcollisionwithmoveablebricks(collidedobjectrect,mariorect,collisionchecktype)) return true;
    /* check collision with immovable bricks */

    if (checkcollisionwithimmoveablebricks(collidedobjectrect,mariorect,collisionchecktype)) return true;
    /* check collision with question marks */

    if (checkcollisionwithquestionmarks(collidedobjectrect,mariorect,collisionchecktype)) return true;

    /* check collision with pipes */
    if (checkcollisionwithpipes(collidedobjectrect,mariorect,collisionchecktype)) return true;

    /* check collision with grass */
    if (checkcollisionwithgroundgrass(collidedobjectrect,mariorect,collisionchecktype)) return true;
    return false;
}


void setmariojumpstate()
{
    if (mario.jumpstate==none)
    {
        mario.yspeed=marioinitialyVel;
        mario.jumpstate =jumping;

    }
}

void handlemariohorizontalmotion()
{
    if (mario.direction.left)
    {
        mario.xspeed-=xInc;
        if (mario.xspeed < -maxxSpeed) mario.xspeed = -maxxSpeed;
        if (mario.xspeed>0) mario.sliding=true;
        else mario.sliding=false;
    }
    else if (mario.direction.right)
    {
        mario.xspeed+=xInc;
        if (mario.xspeed > maxxSpeed) mario.xspeed = maxxSpeed;
        if (mario.xspeed<0) mario.sliding=true;
        else mario.sliding=false;
    }
    else /* neither moving left nor moving right, we need to decay the speed */
    {
        if ((int) mario.xspeed==0)
        {
            mario.xspeed=0;
            mario.sliding=false;
        }
        if (mario.xspeed!=0) mario.xspeed -= xDecay* (mario.xspeed/ abs(mario.xspeed));
    }
    if ((int)mario.xspeed !=0) /* if mario is in motion */
    {
        forwardmariowalkframe();//---------------------------------------------------------------------------------------------------
    }
    else
    {
        mario.currentframe=0;

    }
    mario.position.x+=mario.xspeed;

    SDL_Rect *collidedobject;
    SDL_Rect mariorect;
    mariorect.x = mario.position.x;
    mariorect.y = mario.position.y;
    mariorect.w = mariorects[mario.imageindex].w;
    mariorect.h = mariorects[mario.imageindex].h;

    if (checkmariocollision(&collidedobject,&mariorect,HORZ))
    {
        if (mario.xspeed >0)
        {
            mario.position.x = collidedobject->x-mariorect.w;
            mario.xspeed=0;
        }
        else if (mario.xspeed<0)
        {
            mario.position.x = collidedobject->x + collidedobject->w;
             mario.xspeed=0;
        }

    }
    else if (mario.jumpstate==none)   /* mario was moved horizontally  and no collision between mario and any object, so  mario must be in air and it must fall by the effect of gravity*/
    {
        mario.jumpstate=falling;
        SDL_WM_SetCaption("falling",0);
        mario.yspeed=0; /* just in case */
    }



}

void handlemarioverticalmotion()
{
    if (mario.jumpstate == jumping)
    {
        mario.position.y-=mario.yspeed;
        mario.yspeed = mario.yspeed - gravity; //v = u - g * t; /*t = 1 sec suppose */
        if (mario.yspeed <0)
        {
            mario.yspeed=0;
            mario.jumpstate=falling;
        }
    }
    else if (mario.jumpstate==falling)
    {
        mario.position.y+=mario.yspeed;
        mario.yspeed = mario.yspeed+ gravity; //v = u + g * t; /*t = 1 sec suppose */
    }


    SDL_Rect *collidedobject;
    SDL_Rect mariorect;
    mariorect.x = mario.position.x;
    mariorect.y = mario.position.y+1;
    mariorect.w = mariorects[mario.imageindex].w;
    mariorect.h = mariorects[mario.imageindex].h;

    if (checkmariocollision(&collidedobject,&mariorect,VERT))
    {
        if (mario.jumpstate==falling) /*collided while falling, so collided object is below, and mario must stop falling */
        {
            mario.position.y = collidedobject->y - mariorect.h;
            mario.jumpstate=none;
        }
        else if (mario.jumpstate==jumping) /*collided while jumping, so collided object is above, and mario must begin falling down*/
        {
            mario.position.y = collidedobject->y + collidedobject->h;
            mario.jumpstate=falling;
        }
        mario.yspeed=0;


    }
}


void displayslidinganimation()
{
    int mariodir = mario.standdirection;
    SDL_Rect dstrect = {mario.position.x,mario.position.y+mariorects[mario.imageindex].h - slidedustrects[0].h};
    if (mariodir==RIGHT) dstrect.x+=mariorects[mario.imageindex].w/2;
    else dstrect.x-=10;
    dstrect.y+=2;
    calculaterelativeposition(&dstrect);
      dstrect.y += rand() %2;
    dstrect.x += rand() %2;
    SDL_UpperBlit(mariospritesheet,&slidedustrects[0],screen,&dstrect);
    dstrect.x = mario.position.x;
    dstrect.y = mario.position.y+12;
     if (mariodir==RIGHT) dstrect.x+=18;
    else dstrect.x-=14;
        calculaterelativeposition(&dstrect);
    int dir = (rand() % 2 ==0) ? (1) :(-1);
    dstrect.y += rand() %3 * dir;
    dstrect.x += rand() %3 * dir;

    SDL_UpperBlit(mariospritesheet,&slidedustrects[1],screen,&dstrect);
       dir = (rand() % 2 ==0) ? (1) :(-1);
    dstrect.y += 2;
dstrect.x += rand() %3 * dir;
    SDL_UpperBlit(mariospritesheet,&slidedustrects[2],screen,&dstrect);
    dstrect.x = mario.position.x;
 if (mariodir==RIGHT) dstrect.x+=mariorects[mario.imageindex].w ;
    else dstrect.x-=3;
    dstrect.y = mario.position.y +mariorects[mario.imageindex].h - slidedustrects[0].h+2;

    calculaterelativeposition(&dstrect);


    SDL_UpperBlit(mariospritesheet,&slidedustrects[0],screen,&dstrect);


     dir = (rand() % 2 ==0) ? (1) :(-1);
 dstrect.y += 2;

    SDL_UpperBlit(mariospritesheet,&slidedustrects[1],screen,&dstrect);
       dir = (rand() % 2 ==0) ? (1) :(-1);
  dstrect.y += 2;
    dstrect.x += rand() %3 * dir;
    SDL_UpperBlit(mariospritesheet,&slidedustrects[2],screen,&dstrect);
}
