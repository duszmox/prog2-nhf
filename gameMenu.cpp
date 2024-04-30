#include "gameMenu.h"
#include "szo.h"
#include <fstream>
int GameMenu::getRemainingPossibleWordsCount() const
{
    int currentPossibleWordsCount = 0;

    for (int i = 0; i < answerListCount; i++)
    {
        bool found = false;
        for (int j = 0; j < guessedWordsCount; j++)
        {
            if (answerList[i].reverseMatch(matches[j]))
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            currentPossibleWordsCount++;
        }
    }
    return currentPossibleWordsCount;
}
void GameMenu::readPossibleWords(char *filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
    }
    possibleWordsCount = 0;
    int bufferSize = 64;
    char *word = new char[bufferSize];
    int length = 0;
    char ch;
    int possibleWordsCountTemp = 1;
    delete[] word;

    while (file.get(ch))
    {
        if (isspace(ch) || ch == EOF)
        {
            break;
        }

        if (length >= bufferSize - 1)
        {
            bufferSize *= 2;
            char *temp = new char[bufferSize];
            strncpy(temp, word, length);
            delete[] word;
            word = temp;
        }

        word[length++] = ch;
    }
    word[length] = '\0';
    wordLength = length;
    possibleWordsCount++;
    Szo *temp = new Szo[possibleWordsCount];
    for (int i = 0; i < possibleWordsCount - 1; i++)
    {
        temp[i] = possibleWords[i];
    }
    temp[possibleWordsCount - 1] = Szo(word);
    possibleWords = temp;
    while (file.eof() == false)
    {

        char *buffer = new char[wordLength + 1];
        file.read(buffer, wordLength);
        buffer[wordLength] = '\0';
        if (possibleWordsCountTemp == possibleWordsCount)
        {
            possibleWordsCountTemp *= 2;
            Szo *temp = new Szo[possibleWordsCountTemp];
            for (int i = 0; i < possibleWordsCount; i++)
            {
                temp[i] = possibleWords[i];
            }
            delete[] possibleWords;
            possibleWords = temp;
        }
        possibleWords[possibleWordsCount++] = Szo(buffer);
        int k = 0;
        while (file.get(ch) && ch != '\n')
        {
            k++;
        };
        if (k != 0)
        {
            std::cerr << "Error reading file." << std::endl;
            delete[] buffer;
            break;
        }
        delete[] buffer;
    }
    temp = new Szo[possibleWordsCount];
    for (int i = 0; i < possibleWordsCount; i++)
    {
        temp[i] = possibleWords[i];
    }
    delete[] possibleWords;
    possibleWords = temp;
    file.close();
}
void GameMenu::show() const
{
    std::cout << "Game menu" << std::endl;
    std::cout << "Remaining possible words: " << getRemainingPossibleWordsCount() << std::endl;
    std::cout << "Current word: " << *currentWord << std::endl;

    for (int i = 0; i < guessedWordsCount; i++)
    {
        for (int j = 0; j < this->wordLength; j++)
        {
            switch (matches[i][j].getMatch())
            {
            case MATCH:
                // color green
                std::cout << "\033[32m" << guessedWords[i][j] << "\033[0m ";
                break;
            case PARTIAL:
                // color yellow
                std::cout << "\033[33m" << guessedWords[i][j] << "\033[0m ";
                break;
            default:
                std::cout << guessedWords[i][j] << " ";
                break;
            }
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < maxGuesses - guessedWordsCount; i++)
    {
        for (int j = 0; j < this->wordLength; j++)
        {
            std::cout << "_ ";
        }
        std::cout << std::endl;
    }
}
void GameMenu::readAnswerList(char *filename)
{
    answerListCount = 0;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
    }
    int bufferSize = 64;
    char *word = new char[bufferSize];
    int length = 0;
    char ch;
    int answerListCountTemp = 1;
    delete[] word;

    while (file.get(ch))
    {
        if (isspace(ch) || ch == EOF)
        {
            break;
        }

        if (length >= bufferSize - 1)
        {
            bufferSize *= 2;
            char *temp = new char[bufferSize];
            strncpy(temp, word, length);
            delete[] word;
            word = temp;
        }

        word[length++] = ch;
    }
    word[length] = '\0';
    answerListCount++;
    Szo *temp = new Szo[answerListCount];
    for (int i = 0; i < answerListCount - 1; i++)
    {
        temp[i] = answerList[i];
    }
    temp[answerListCount - 1] = Szo(word);
    answerList = temp;

    while (file.eof() == false)
    {

        char *buffer = new char[wordLength + 1];
        file.read(buffer, wordLength);
        buffer[wordLength] = '\0';
        if (answerListCountTemp == answerListCount)
        {
            answerListCountTemp *= 2;
            Szo *temp = new Szo[answerListCountTemp];
            for (int i = 0; i < answerListCount; i++)
            {
                temp[i] = answerList[i];
            }
            delete[] answerList;
            answerList = temp;
        }
        answerList[answerListCount++] = Szo(buffer);
        int k = 0;
        while (file.get(ch) && ch != '\n')
        {
            k++;
        };
        if (k != 0)
        {
            std::cerr << "Error reading file." << std::endl;
            delete[] buffer;
            break;
        }
        delete[] buffer;
    }
    temp = new Szo[answerListCount];
    for (int i = 0; i < answerListCount; i++)
    {
        temp[i] = answerList[i];
    }
    delete[] answerList;
    answerList = temp;
    file.close();
}

void GameMenu::guessWord(const Szo &word)
{
    if (guessedWords == nullptr)
    {
        guessedWords = new Szo[1];
        guessedWords[0] = word;
        guessedWordsCount++;
    }
    else
    {
        Szo *temp = new Szo[guessedWordsCount + 1];
        for (int i = 0; i < guessedWordsCount; i++)
        {
            temp[i] = guessedWords[i];
        }
        temp[guessedWordsCount] = word;
        delete[] guessedWords;
        guessedWords = temp;
        guessedWordsCount++;
    }
    if (matches != nullptr)
        delete[] matches;

    matches = new Match *[guessedWordsCount];
    for (int i = 0; i < guessedWordsCount; i++)
    {
        matches[i] = currentWord->match(guessedWords[i]);
    }
}