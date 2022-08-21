#include "sdldecl.h"
#include "powerups.h"
#include "marioinfo.h"
#include "camera.h"
#include "screen.h"

#ifdef EMSCRIPTEN
 #include <emscripten.h>
#endif
int handleevent();
int run = 1;
void loop() {
        if (handleevent() == SDL_QUIT) {
            run = 0;
            return;
        }
        //logic
        handlemariomotion();
        handlecameramotion(); /* move camera relative to the position of mario */
        animatepowerups();

        //rendering
        render(); /* to screen */
        SDL_Delay(10);
}

void rungame()
{
#ifdef EMSCRIPTEN
    emscripten_set_main_loop(loop, 0, 1);
#else
    while (run)
    {
        loop();
    }
#endif
}
