#include "Game.h"

int main()
{
    Game* game = new Game(false, 800, 600, "Test Game");
    game->run();
    delete game;
}