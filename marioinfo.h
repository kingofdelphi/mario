#ifndef MARIOINFO_H
#define MARIOINFO_H

#include "sdldecl.h"
#include "loadresources.h"

#define MARIO_ANIM_FRAME 5

typedef struct {
    enum MarioType {small,super,fire} type; /* small mario, super mario, fire mario */
    enum State {standing,supertosmall,smalltosuper,supertofire,climb,sliding,dying} state;
    struct {
        bool left,right;
    } direction;
    int currentframe; /* for current image of mario*/
    int animframe; /* for animation delay */
    int framedir;
    int imageindex;
    int standdirection;
    double xspeed,yspeed;
    bool running;
    bool sliding;
    enum JumpState {noverticalmotion,jumping,falling,NONE} jumpstate;
    SDL_Rect position;
} MARIO;


bool checkmariocollision(SDL_Rect **collidedobjectrect,SDL_Rect *mariorect,int collisionchecktype);
bool checkcollisionwithpipes(SDL_Rect **collidedobject,SDL_Rect *mariorect,int collisionchecktype);
bool checkcollisionwithquestionmarks(SDL_Rect **collidedobject,SDL_Rect *mariorect,int collisionchecktype);
bool checkcollisionwithmoveablebricks(SDL_Rect **collidedobject,SDL_Rect *mariorect,int collisionchecktype);
bool checkcollisionwithimmoveablebricks(SDL_Rect **collidedobject,SDL_Rect *mariorect,int collisionchecktype);
bool checkcollisionwithgroundgrass(SDL_Rect **collidedobject,SDL_Rect *mariorect,int collisionchecktype);

void setmariojumpstate();
void handlemariomotion();
void animatepowerups();

#endif
