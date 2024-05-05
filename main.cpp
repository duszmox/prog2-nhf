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
        if (currMenu == &gameMenu)
        {
            if (gameMenu.getIsGuessed())
            {
                std::cout << "Congratulations! You have guessed the word!" << std::endl;
                std::cout << "The word was: " << *gameMenu.getCurrentWord() << std::endl;
                std::cout << "Enter 0 to return to the main menu." << std::endl;

                Szo guess;
                std::cin >> guess;
                if (guess == "0")
                {
                    currMenu = &mainMenu;
                    continue;
                }
                else
                {
                    std::cout << "Invalid input!" << std::endl;
                    continue;
                }
            }
            else if (gameMenu.getGuessedWordsCount() == gameMenu.getMaxGuesses())
            {
                std::cout << "Enter 0 to return to the main menu or 1 to restart." << std::endl;
                Szo guess;
                std::cin >> guess;
                if (guess.getLength() > 1)
                {
                    std::cout << "Invalid input!" << std::endl;
                    continue;
                }
                switch (guess[0].getBetu())
                {
                case '0':
                    currMenu = &mainMenu;
                    break;
                case '1':
                    gameMenu.resetGame();
                    break;

                default:
                    std::cout << "Invalid input!" << std::endl;
                    break;
                }
            }
            else
            {
                std::cout << "Enter your guess (or 0 to quit): ";
                Szo guess;
                std::cin >> guess;
                if (guess.getLength() != gameMenu.getWordLength() || guess.containsNumber())
                {
                    if (guess.getLength() == 1)
                    {
                        if (guess[0] == '0')
                        {
                            currMenu = &mainMenu;
                            continue;
                        }
                        continue;
                    }
                    std::cout << "Invalid guess length!" << std::endl;
                    continue;
                }
                bool invalid = false;
                for (int i = 0; i < guess.getLength(); i++)
                {
                    if (guess[i].getBetu() < 'a' || guess[i].getBetu() > 'z')
                    {
                        std::cout << "Invalid character!" << std::endl;
                        invalid = true;
                        break;
                    }
                }
                if (invalid)
                {
                    continue;
                }
                try
                {
                    gameMenu.guessWord(guess);
                }
                catch (const std::exception &e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
        }
        else
        {
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
                    if (currMenu == &gameMenu)
                    {
                        gameMenu.resetGame();
                    }
                }
                else
                {
                    (*currMenu)[selection - 1].getAction()();
                }
            }
        }
    }
}
