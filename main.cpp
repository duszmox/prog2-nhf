#include "szo.h"
#include <iostream>
#include "gameMenu.h"
#include "statsMenu.h"
#include "memtrace.h"
#include <cstdlib>

int main()
{
    Menu mainMenu(nullptr);
    GameMenu gameMenu(&mainMenu);
    StatsMenu statsMenu(&mainMenu);
    mainMenu.addItem("Game", &gameMenu);
    mainMenu.addItem("Stats", &statsMenu);
    statsMenu.setMaxAttempts(gameMenu.getMaxGuesses());

    Menu *currMenu = &mainMenu;
    while (true)
    {
        bool errorChanged = false;
        currMenu->showLogo();
        currMenu->show();
        if (currMenu == &gameMenu)
        {
            if (gameMenu.getIsGuessed())
            {
                std::cout << "Congratulations! You have guessed the word!" << std::endl;
                std::cout << "The word was: " << *gameMenu.getCurrentWord() << std::endl;
                std::cout << "(1) Retry" << std::endl;
                std::cout << "(0) Back" << std::endl;
                statsMenu.saveStats(gameMenu.getGuessedWordsCount(), *gameMenu.getCurrentWord());
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
            else if (gameMenu.getGuessedWordsCount() == gameMenu.getMaxGuesses())
            {
                std::cout << "(1) Retry" << std::endl;
                std::cout << "(0) Back" << std::endl;
                statsMenu.saveStats('X', *gameMenu.getCurrentWord());
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
                if (isInWords(gameMenu.getGuessedWords(), gameMenu.getGuessedWordsCount(), guess))
                {
                    currMenu->setError("You have already guessed this word!");
                    errorChanged = true;
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
                    if (currMenu == &gameMenu)
                    {
                        gameMenu.resetGame();
                    }
                    if (currMenu == &statsMenu)
                    {
                        statsMenu.updateStats();
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
