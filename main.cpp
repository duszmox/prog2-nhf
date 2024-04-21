#include "szo.h"
#include <iostream>
#include "gameMenu.h"
#include <cstdlib>

int main()
{
    GameMenu gameMenu;
    std::cout << *(gameMenu.getCurrentWord()) << std::endl;
    gameMenu.guessWord(Szo("cyber"));
    std::cout << gameMenu.getRemainingPossibleWordsCount() << std::endl;
    return 0;
}
