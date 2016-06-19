#include "sdldecl.h"

int checkcollision(SDL_Rect *a, SDL_Rect *b)
{
    if (a->x + a->w <=b->x) return 0;
    if (b->x+b->w <=a->x) return 0;
    if (a->y >=b->y+b->h) return 0;
    if (a->y + a->h <= b->y) return 0;
    return 1;
}
