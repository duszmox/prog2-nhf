#include "szo.h"
#include <iostream>
#include "gameMenu.h"
#include "statsMenu.hpp"
#include "memtrace.h"
#include <cstdlib>
#include "gtest_lite.h"
#include <sstream>

int main()
{
#ifdef CPORTA
    Menu mainMenu(nullptr);
    GameMenu gameMenu(&mainMenu);
    StatsMenu statsMenu(&mainMenu);
    mainMenu.addItem("Game", &gameMenu);
    mainMenu.addItem("Stats", &statsMenu);
    statsMenu.setMaxAttempts(gameMenu.getMaxGuesses());
    TEST(Szo Betu, _szoBetu)
    {
        Betu b('a');
        EXPECT_EQ('a', b.getBetu());
        b.setBetu('b');
        EXPECT_EQ('b', b.getBetu());
        EXPECT_EQ(1, b == Betu('b'));
        EXPECT_EQ(0, b == Betu('c'));
        EXPECT_EQ(0, b.isNumber());
        EXPECT_EQ(1, Betu('1').isNumber());
    }
    END
    TEST(Match, _out)
    {
        std::stringstream ss;
        Match m(MATCH, new Betu('a'));
        ss << m;
        EXPECT_STREQ("MATCH", ss.str().c_str());
        m.setMatch(NOMATCH);
        ss.str("");
        ss << m;
        EXPECT_STREQ("NOMATCH", ss.str().c_str());
        m.setMatch(PARTIAL);
        ss.str("");
        ss << m;
        EXPECT_STREQ("PARTIAL", ss.str().c_str());
    }
    END
    TEST(Menu, _error)
    {
        mainMenu.setError(Szo("hiba"));
        Szo *error = mainMenu.getError();
        const char *errorStr = error->c_str();
        EXPECT_STREQ("hiba", errorStr);
        delete[] errorStr;
    }
    END
    TEST(Wordle init, _init)
    {
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
        gameMenu.resetGame();
        gameMenu.guessWord(Szo("crave"));
        EXPECT_EQ(1, gameMenu.getGuessedWordsCount());
        const char *word = gameMenu.getGuessedWords()[0].c_str();
        EXPECT_STRCASEEQ("crave", word);
        delete[] word;
    }
    END
    TEST(Wordle guess same twice, _sameWordTwice)
    {
        gameMenu.resetGame();
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
        gameMenu.resetGame();
        EXPECT_THROW(gameMenu.guessWord(Szo("cravee")), std::runtime_error);
        EXPECT_THROW(gameMenu.guessWord(Szo("arggh")), std::runtime_error);
        EXPECT_THROW(gameMenu.guessWord(Szo("cra ve")), std::runtime_error);
        EXPECT_THROW(gameMenu.guessWord(Szo("cra1ve")), std::runtime_error);
        EXPECT_THROW(gameMenu.guessWord(Szo("cra ve1")), std::runtime_error);
    }
    END
    TEST(Wordle guess matches, _match)
    {
        gameMenu.resetGame();
        gameMenu.guessWord(Szo("berry"));
        EXPECT_EQ('b', gameMenu.getMatches()[0][0].getBetu()->getBetu());
        EXPECT_EQ('e', gameMenu.getMatches()[0][1].getBetu()->getBetu());
        EXPECT_EQ('r', gameMenu.getMatches()[0][2].getBetu()->getBetu());
        EXPECT_EQ('r', gameMenu.getMatches()[0][3].getBetu()->getBetu());
        EXPECT_EQ('y', gameMenu.getMatches()[0][4].getBetu()->getBetu());
        EXPECT_EQ(PARTIAL, gameMenu.getMatches()[0][0].getMatch());
        EXPECT_EQ(MATCH, gameMenu.getMatches()[0][1].getMatch());
        EXPECT_EQ(PARTIAL, gameMenu.getMatches()[0][2].getMatch());
        EXPECT_EQ(NOMATCH, gameMenu.getMatches()[0][3].getMatch());
        EXPECT_EQ(NOMATCH, gameMenu.getMatches()[0][4].getMatch());
    }
    END
    TEST(Wordle guess remaining, _remaining)
    {
        GameMenu gameMenu2(&mainMenu);
        gameMenu2.guessWord(Szo("crave"));
        gameMenu2.guessWord(Szo("arced"));
        gameMenu2.guessWord(Szo("arcus"));
        gameMenu2.guessWord(Szo("arcos"));
        gameMenu2.guessWord(Szo("barca"));
        EXPECT_EQ(3, gameMenu2.getRemainingPossibleWordsCount());
    }
    END
    TEST(Wordle guessed, _guessed)
    {
        GameMenu gameMenu2(&mainMenu);
        gameMenu2.guessWord(Szo("crave"));
        gameMenu2.guessWord(Szo("arced"));
        gameMenu2.guessWord(Szo("arcus"));
        gameMenu2.guessWord(Szo("arcos"));
        gameMenu2.guessWord(Szo("barca"));
        gameMenu2.guessWord(Szo("cigar"));
        EXPECT_EQ(1, gameMenu2.getRemainingPossibleWordsCount());
        EXPECT_EQ(true, gameMenu2.getIsGuessed());
    }
    END
    TEST(Wordle stats, _stats)
    {
        std::remove("stats.csv");
        GameMenu gameMenu2(&mainMenu);
        gameMenu2.guessWord(Szo("crave"));
        gameMenu2.guessWord(Szo("arced"));
        gameMenu2.guessWord(Szo("arcus"));
        gameMenu2.guessWord(Szo("arcos"));
        gameMenu2.guessWord(Szo("barca"));
        gameMenu2.guessWord(Szo("cigar"));
        statsMenu.saveStats(gameMenu2.getGuessedWordsCount(), *gameMenu2.getCurrentWord());
        statsMenu.readStats();
        EXPECT_EQ(1, statsMenu.getStatsCount());
        const char *word = statsMenu.getStats()[0].getSzo().c_str();
        EXPECT_EQ(6, statsMenu.getStats()[0].getAttempts());
        EXPECT_STRCASEEQ("cigar", word);
        delete[] word;
    }
    END
    TEST(Wordle reset, _reset)
    {
        GameMenu gameMenu2(&mainMenu);
        gameMenu2.guessWord(Szo("crave"));
        gameMenu2.guessWord(Szo("arced"));
        gameMenu2.guessWord(Szo("arcus"));
        gameMenu2.guessWord(Szo("arcos"));
        gameMenu2.guessWord(Szo("barca"));
        gameMenu2.guessWord(Szo("cigar"));
        statsMenu.saveStats(gameMenu2.getGuessedWordsCount(), *gameMenu2.getCurrentWord());
        statsMenu.readStats();
        gameMenu2.resetGame();
        EXPECT_EQ(0, gameMenu2.getGuessedWordsCount());
        EXPECT_EQ(14855, gameMenu2.getRemainingPossibleWordsCount());
        EXPECT_EQ(false, gameMenu2.getIsGuessed());
        const char *word = gameMenu2.getCurrentWord()->c_str();
        EXPECT_STRCASEEQ("rebut", word);
        delete[] word;
    }
    END
#else
    try
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
            try
            {
                currMenu->show();
            }
            catch (const std::exception &e)
            {
                currMenu = &mainMenu;
                currMenu->setError(e.what());
                errorChanged = true;
                continue;
            }
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
                            continue;
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
                Szo selection;
                std::cin >> selection;
                if (selection == "0")
                {
                    if (&currMenu->getParent() != nullptr)
                    {
                        currMenu = &currMenu->getParent();
                    }
                    else
                    {
                        std::cout << selection << std::endl;
                        std::cout << "Exiting..." << std::endl;
                        break;
                    }
                }
                else
                {
                    int selected = selection[0].getBetu() - '0';
                    if (selection.getLength() != 1 || selection[0].getBetu() < '1' || selection[0].getBetu() > '9' || selection[0].getBetu() - '0' > currMenu->getItemCount())
                    {
                        currMenu->setError("Invalid input!");
                        errorChanged = true;
                        continue;
                    }
                    if ((*currMenu)[selected - 1].getSubMenu() != nullptr)
                    {
                        currMenu->clearError();
                        currMenu = (*currMenu)[selected - 1].getSubMenu();
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
                        (*currMenu)[selected - 1].getAction()();
                    }
                }
            }
            if (!errorChanged)
            {
                currMenu->clearError();
            }
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
#endif
        return 0;
}
