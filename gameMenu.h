#ifndef GAME_MENU_H
#define GAME_MENU_H
#include "menu.h"
#include "szo.h"
// #define CPORTA 1
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
    bool isGuessed = false;

public:
    GameMenu(Menu *p) : Menu(p), guessedWords(nullptr), guessedWordsCount(0), matches(nullptr)
    {
        possibleWords = nullptr;
        currentWord = nullptr;
        readPossibleWords("possible.csv");
        readAnswerList("answerlist.csv");
#ifdef CPORTA
        currentWordIndex = 0;
#else
        srand((unsigned)time(NULL));
        int random = rand();
        currentWordIndex = random % answerListCount;
#endif
        currentWord = &answerList[currentWordIndex];

        maxGuesses = 6;
        clearError();
    }
    GameMenu() : Menu(), guessedWords(nullptr), guessedWordsCount(0), matches(nullptr)
    {
        possibleWords = nullptr;
        currentWord = nullptr;
        readPossibleWords("possible.csv");
        readAnswerList("answerlist.csv");
#ifdef CPORTA
        currentWordIndex = 0;
#else
        srand((unsigned)time(NULL));
        int random = rand();
        currentWordIndex = random % answerListCount;
#endif
        currentWord = &answerList[currentWordIndex];
        maxGuesses = 6;
        clearError();
    }
    void show() const;
    int getRemainingPossibleWordsCount() const;
    void readPossibleWords(char *filename);
    void readAnswerList(char *filename);
    void guessWord(const Szo &word);
    int getAnswerListCount() const { return answerListCount; }
    Szo *getAnswerList() const { return answerList; }
    Szo *getCurrentWord() const { return currentWord; }
    int getWordLength() const { return wordLength; }
    bool getIsGuessed() const { return isGuessed; }
    void resetGame();
    int getGuessedWordsCount() const { return guessedWordsCount; }
    int getMaxGuesses() const { return maxGuesses; }
    Szo *getGuessedWords() const { return guessedWords; }
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
