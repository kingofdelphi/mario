#ifndef HIDDEN_TREASURES_H
#define HIDDEN_TREASURES_H

#include <stdbool.h>
#include "sdldecl.h"

/* image is displayed for required amount of frames */
#define QUESTIONS_ANIM_FRAMES 5
#define BRICKS_ANIM_FRAME 5 /*  when  mario hits the moveable and breakable brick */
#define GRASS_ANIM_FRAME 15
#define COIN_HIT_ANIM_FRAME 5
#define SLIDESHIFT 8
#define COINSHIFT 18
typedef struct
{
    SDL_Rect cointhitrect;
    int currentframe;
        bool coinanim;
    int coinanimframe;
} COINHIT;
typedef struct
{
    int curframe;
    SDL_Rect poweruppos;
    bool slidingup;
    int slidingspeed;
    int slideheight;
    bool powerupeaten;
    int slidedir;
    int framedir;
    int coinheight;
    COINHIT coinhit;
} QUESTIONMARK;


typedef struct
{
    int curframe;
    SDL_Rect poweruppos;
    int framedir;
    int grasstype; /* left, middle, right */
} GRASS;

typedef struct
{
    SDL_Rect poweruppos;
    int grasstype; /* left, middle, right */
} GROUNDGRASS;


typedef struct
{
    SDL_Rect poweruppos;
    bool blasting;
    bool slidingup;
    int slidingspeed;
    bool powerupeaten;
    SDL_Rect slidingpos;
    SDL_Rect fallingbricks[4];
} BRICK;

typedef struct
{
    SDL_Rect poweruppos;
    int type;
} IMMOVABLEBRICK;


typedef struct
{
    SDL_Rect poweruppos;
    int type; /* either green or silver */
} PIPE;


typedef struct
{
    QUESTIONMARK questionmarkpower[MAXPOWERS];
    int total;
    int animframe;
} QUESTIONS;


typedef struct
{
    BRICK brickpower[MAXPOWERS];
    int total;
    int animframe;
} BRICKS;

typedef struct
{
    GRASS grasspower[MAXPOWERS];
    int total;
    int animframe;
} GRASSES;

typedef struct
{
    PIPE pipepower[MAXPOWERS];
    int total;

} PIPES;

typedef struct
{
    GROUNDGRASS groundgrasspower[MAXPOWERS];
    int total;
} GROUNDGRASSES;

typedef struct {
IMMOVABLEBRICK immovablebrickpower[MAXPOWERS];
int total;
}IMMOVABLEBRICKS;
#endif
