#include "global.h"
#include "gameControl.h"

int main()
{
    gameControl *newGame = new gameControl();
    newGame->run();
    delete newGame;
    return 0;
}
