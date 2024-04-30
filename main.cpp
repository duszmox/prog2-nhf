#include "szo.h"
#include <iostream>
#include "gameMenu.h"
// #include "statsMenu.h"
#include "memtrace.h"
#include <cstdlib>

int main()
{
    Menu mainMenu(nullptr);
    GameMenu gameMenu(&mainMenu);
    // StatsMenu statsMenu(&mainMenu);
    mainMenu.addItem("Game", &gameMenu);
    // mainMenu.addItem("Stats", &statsMenu);

    Menu *currMenu = &mainMenu;
    while (true)
    {
        currMenu->show();
        int selection;
        std::cin >> selection;
        if (selection == 0)
        {
            if (&currMenu->getParent() != nullptr)
            {
                currMenu = &currMenu->getParent();
            }
            else
            {
                std::cout << "Exiting..." << std::endl;
                break;
            }
        }
        else
        {
            if (selection < 0 || selection > currMenu->getItemCount())
            {
                std::cout << "Invalid selection!" << std::endl;
                continue;
            }
            if ((*currMenu)[selection - 1].getSubMenu() != nullptr)
            {
                currMenu = (*currMenu)[selection - 1].getSubMenu();
            }
            else
            {
                (*currMenu)[selection - 1].getAction()();
            }
        }
    }
}
