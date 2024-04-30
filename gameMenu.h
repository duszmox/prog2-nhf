#ifndef GAME_MENU_H
#define GAME_MENU_H
#include "menu.h"
#include "szo.h"
class GameMenu : public Menu
{
    Szo *possibleWords;
    int possibleWordsCount;
    Szo *currentWord;
    int currentWordIndex;
    Szo *guessedWords;
    int guessedWordsCount;
    int maxGuesses;
    Szo *answerList;
    int answerListCount;
    Match **matches;
    int wordLength = 0;

public:
    GameMenu(Menu *p) : Menu(p), guessedWords(nullptr), guessedWordsCount(0), matches(nullptr)
    {
        possibleWords = nullptr;
        currentWord = nullptr;
        readPossibleWords("possible.csv");
        readAnswerList("answerlist.csv");
        srand((unsigned)time(NULL));
        int random = rand();
        currentWordIndex = random % answerListCount;
        currentWord = &answerList[currentWordIndex];
        maxGuesses = 6;
        guessWord(Szo("apple"));
    }
    GameMenu() : Menu(), guessedWords(nullptr), guessedWordsCount(0), matches(nullptr)
    {
        possibleWords = nullptr;
        currentWord = nullptr;
        readPossibleWords("possible.csv");
        readAnswerList("answerlist.csv");
        srand((unsigned)time(NULL));
        int random = rand();
        currentWordIndex = random % answerListCount;
        // currentWordIndex = 0;
        currentWord = &answerList[currentWordIndex];
        maxGuesses = 6;
    }
    void show() const;
    int getRemainingPossibleWordsCount() const;
    void readPossibleWords(char *filename);
    void readAnswerList(char *filename);
    void guessWord(const Szo &word);
    int getAnswerListCount() const { return answerListCount; }
    Szo *getAnswerList() const { return answerList; }
    Szo *getCurrentWord() const { return currentWord; }
    ~GameMenu()
    {
        delete[] possibleWords;
        delete[] guessedWords;
        delete[] answerList;
        for (int i = 0; i < guessedWordsCount; i++)
            delete[] matches[i];
        delete[] matches;
    }
};
#endif
