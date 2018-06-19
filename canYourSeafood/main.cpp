#include "global.h"
#include "gameControl.h"

Fonts font_lib;

int main()
{
    gameControl *newGame = new gameControl();
    newGame->run();
    delete newGame;
    return 0;
}
