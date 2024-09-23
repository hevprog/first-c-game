///client code

#include "game_call.h"


int main()
{
   Swindows();
   while (game_loop())
   {
    begindraw(true);
    gameDesignTable();
    game_init();
    begindraw(false);
   }
    game_close();
    return 0;
}

