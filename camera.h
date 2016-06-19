#ifndef CAMERA_H
#define CAMERA_H

#include "sdldecl.h"
#include <stdbool.h>
#include "directions.h"

/*1 pixel position change */
#define DELTAX 0.1
#define DELTAY 0.1

typedef struct {
    SDL_Rect rect;
    struct {
        bool left,right,up,down;
    } direction;
    double xspeed,yspeed;

} CAMERA;


#endif
