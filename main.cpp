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
        bool errorChanged = false;
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
                    currMenu->setError("Invalid input!");
                    errorChanged = true;
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
                    currMenu->setError("Invalid input!");
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
                    currMenu->setError("Invalid input!");
                    errorChanged = true;
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
                    currMenu->setError("Invalid guess length!");
                    errorChanged = true;
                    continue;
                }
                bool invalid = false;
                for (int i = 0; i < guess.getLength(); i++)
                {
                    if (guess[i].getBetu() < 'a' || guess[i].getBetu() > 'z')
                    {
                        currMenu->setError("Invalid character!");
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
                    currMenu->setError(Szo(e.what()));
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
                    currMenu->setError("Invalid selection!");
                    errorChanged = true;
                    continue;
                }
                if ((*currMenu)[selection - 1].getSubMenu() != nullptr)
                {
                    currMenu->clearError();
                    currMenu = (*currMenu)[selection - 1].getSubMenu();
                    std::cout << "Entering " << std::endl;
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
        if (!errorChanged)
        {
            currMenu->clearError();
        }
    }
}
