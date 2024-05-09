#include "szo.h"
#include <iostream>
#include "gameMenu.h"
#include "statsMenu.h"
#include "memtrace.h"
#include <cstdlib>
#include "gtest_lite.h"
#include <sstream>

void game()
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
                if (guess.getLength() == 1)
                {
                    if (guess[0].getBetu() == '0')
                    {
                        std::cout << "Exiting..." << std::endl;
                        currMenu = &mainMenu;
                    }
                }
                try
                {
                    gameMenu.guessWord(guess);
                }
                catch (std::runtime_error &e)
                {
                    currMenu->setError(Szo(e.what()));
                    errorChanged = true;
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
                        statsMenu.readStats();
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

int main()
{
#ifdef CPORTA
    TEST(Wordle init, _init)
    {
        Menu mainMenu(nullptr);
        GameMenu gameMenu(&mainMenu);
        StatsMenu statsMenu(&mainMenu);
        mainMenu.addItem("Game", &gameMenu);
        mainMenu.addItem("Stats", &statsMenu);
        statsMenu.setMaxAttempts(gameMenu.getMaxGuesses());
        EXPECT_EQ(2, mainMenu.getItemCount());
        EXPECT_STRCASEEQ("Game", mainMenu[0].getText());
        EXPECT_STRCASEEQ("Stats", mainMenu[1].getText());
        const char *word = gameMenu.getCurrentWord()->c_str();
        EXPECT_STRCASEEQ("cigar", word);
        delete[] word;
        EXPECT_EQ(14855, gameMenu.getRemainingPossibleWordsCount());
    }
    END
    TEST(Wordle guess, _crave)
    {
        Menu mainMenu(nullptr);
        GameMenu gameMenu(&mainMenu);
        StatsMenu statsMenu(&mainMenu);
        mainMenu.addItem("Game", &gameMenu);
        mainMenu.addItem("Stats", &statsMenu);
        statsMenu.setMaxAttempts(gameMenu.getMaxGuesses());
        gameMenu.guessWord(Szo("crave"));
        EXPECT_EQ(1, gameMenu.getGuessedWordsCount());
        const char *word = gameMenu.getGuessedWords()[0].c_str();
        EXPECT_STRCASEEQ("crave", word);
        delete[] word;
    }
    END
    TEST(Wordle guess same twice, _sameWordTwice)
    {
        Menu mainMenu(nullptr);
        GameMenu gameMenu(&mainMenu);
        StatsMenu statsMenu(&mainMenu);
        mainMenu.addItem("Game", &gameMenu);
        mainMenu.addItem("Stats", &statsMenu);
        statsMenu.setMaxAttempts(gameMenu.getMaxGuesses());
        gameMenu.guessWord(Szo("crave"));
        EXPECT_EQ(1, gameMenu.getGuessedWordsCount());
        const char *word = gameMenu.getGuessedWords()[0].c_str();
        EXPECT_STRCASEEQ("crave", word);
        delete[] word;
        EXPECT_THROW(gameMenu.guessWord(Szo("crave")), std::runtime_error);
        EXPECT_EQ(1, gameMenu.getGuessedWordsCount());
    }
    END
    TEST(Wordle guess invalid, _invalidGuess)
    {
        Menu mainMenu(nullptr);
        GameMenu gameMenu(&mainMenu);
        StatsMenu statsMenu(&mainMenu);
        mainMenu.addItem("Game", &gameMenu);
        mainMenu.addItem("Stats", &statsMenu);
        statsMenu.setMaxAttempts(gameMenu.getMaxGuesses());
        EXPECT_THROW(gameMenu.guessWord(Szo("cravee")), std::runtime_error);
        EXPECT_THROW(gameMenu.guessWord(Szo("arggh")), std::runtime_error);
        EXPECT_THROW(gameMenu.guessWord(Szo("cra ve")), std::runtime_error);
        EXPECT_THROW(gameMenu.guessWord(Szo("cra1ve")), std::runtime_error);
        EXPECT_THROW(gameMenu.guessWord(Szo("cra ve1")), std::runtime_error);
    }
    END
    TEST(Wordle guess matches, _match)
    {
        Menu mainMenu(nullptr);
        GameMenu gameMenu(&mainMenu);
        StatsMenu statsMenu(&mainMenu);
        mainMenu.addItem("Game", &gameMenu);
        mainMenu.addItem("Stats", &statsMenu);
        statsMenu.setMaxAttempts(gameMenu.getMaxGuesses());
        gameMenu.guessWord(Szo("crave"));
        EXPECT_EQ('c', gameMenu.getMatches()[0][0].getBetu()->getBetu());
        EXPECT_EQ('r', gameMenu.getMatches()[0][1].getBetu()->getBetu());
        EXPECT_EQ('a', gameMenu.getMatches()[0][2].getBetu()->getBetu());
        EXPECT_EQ('v', gameMenu.getMatches()[0][3].getBetu()->getBetu());
        EXPECT_EQ('e', gameMenu.getMatches()[0][4].getBetu()->getBetu());
        EXPECT_EQ(MATCH, gameMenu.getMatches()[0][0].getMatch());
        EXPECT_EQ(PARTIAL, gameMenu.getMatches()[0][1].getMatch());
        EXPECT_EQ(PARTIAL, gameMenu.getMatches()[0][2].getMatch());
        EXPECT_EQ(NOMATCH, gameMenu.getMatches()[0][3].getMatch());
        EXPECT_EQ(NOMATCH, gameMenu.getMatches()[0][4].getMatch());
    }
    END
    TEST(Wordle guess remaining, _remaining)
    {
        Menu mainMenu(nullptr);
        GameMenu gameMenu(&mainMenu);
        StatsMenu statsMenu(&mainMenu);
        mainMenu.addItem("Game", &gameMenu);
        mainMenu.addItem("Stats", &statsMenu);
        statsMenu.setMaxAttempts(gameMenu.getMaxGuesses());
        gameMenu.guessWord(Szo("crave"));
        gameMenu.guessWord(Szo("arced"));
        gameMenu.guessWord(Szo("arcus"));
        gameMenu.guessWord(Szo("arcos"));
        gameMenu.guessWord(Szo("barca"));
        EXPECT_EQ(3, gameMenu.getRemainingPossibleWordsCount());
    }
    END
    TEST(Wordle guessed, _guessed)
    {
        Menu mainMenu(nullptr);
        GameMenu gameMenu(&mainMenu);
        StatsMenu statsMenu(&mainMenu);
        mainMenu.addItem("Game", &gameMenu);
        mainMenu.addItem("Stats", &statsMenu);
        statsMenu.setMaxAttempts(gameMenu.getMaxGuesses());
        gameMenu.guessWord(Szo("crave"));
        gameMenu.guessWord(Szo("arced"));
        gameMenu.guessWord(Szo("arcus"));
        gameMenu.guessWord(Szo("arcos"));
        gameMenu.guessWord(Szo("barca"));
        gameMenu.guessWord(Szo("cigar"));
        EXPECT_EQ(1, gameMenu.getRemainingPossibleWordsCount());
        EXPECT_EQ(true, gameMenu.getIsGuessed());
    }
    END
    TEST(Wordle stats, _stats)
    {
        Menu mainMenu(nullptr);
        GameMenu gameMenu(&mainMenu);
        StatsMenu statsMenu(&mainMenu);
        mainMenu.addItem("Game", &gameMenu);
        mainMenu.addItem("Stats", &statsMenu);
        statsMenu.setMaxAttempts(gameMenu.getMaxGuesses());
        gameMenu.guessWord(Szo("crave"));
        gameMenu.guessWord(Szo("arced"));
        gameMenu.guessWord(Szo("arcus"));
        gameMenu.guessWord(Szo("arcos"));
        gameMenu.guessWord(Szo("barca"));
        gameMenu.guessWord(Szo("cigar"));
        statsMenu.saveStats(gameMenu.getGuessedWordsCount(), *gameMenu.getCurrentWord());
        statsMenu.readStats();
        EXPECT_EQ(1, statsMenu.getStatsCount());
        const char *word = statsMenu.getStats()[0].getSzo().c_str();
        EXPECT_STRCASEEQ("cigar", word);
        delete[] word;
    }
    END
    TEST(Wordle reset, _reset)
    {
        Menu mainMenu(nullptr);
        GameMenu gameMenu(&mainMenu);
        StatsMenu statsMenu(&mainMenu);
        mainMenu.addItem("Game", &gameMenu);
        mainMenu.addItem("Stats", &statsMenu);
        statsMenu.setMaxAttempts(gameMenu.getMaxGuesses());
        gameMenu.guessWord(Szo("crave"));
        gameMenu.guessWord(Szo("arced"));
        gameMenu.guessWord(Szo("arcus"));
        gameMenu.guessWord(Szo("arcos"));
        gameMenu.guessWord(Szo("barca"));
        gameMenu.guessWord(Szo("cigar"));
        statsMenu.saveStats(gameMenu.getGuessedWordsCount(), *gameMenu.getCurrentWord());
        statsMenu.readStats();
        gameMenu.resetGame();
        EXPECT_EQ(0, gameMenu.getGuessedWordsCount());
        EXPECT_EQ(14855, gameMenu.getRemainingPossibleWordsCount());
        EXPECT_EQ(false, gameMenu.getIsGuessed());
        const char *word = gameMenu.getCurrentWord()->c_str();
        EXPECT_STRCASEEQ("rebut", word);
        delete[] word;
    }
    END
#else
    game();
#endif
        return 0;
}
