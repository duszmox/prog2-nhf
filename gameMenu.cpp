#include "gameMenu.h"
#include "szo.h"
#include "memtrace.h"
#include <fstream>
int GameMenu::getRemainingPossibleWordsCount() const
{
    int currentPossibleWordsCount = 0;
    Szo *temp = new Szo[possibleWordsCount];

    if (guessedWordsCount == 0)
    {
        delete[] temp;
        return possibleWordsCount;
    }
    for (int i = 0; i < guessedWordsCount; i++)
    {
        Szo *currArr = i == 0 ? possibleWords : temp;
        int currCount = i == 0 ? possibleWordsCount : currentPossibleWordsCount;
        Szo *tempArr = i == 0 ? temp : new Szo[currentPossibleWordsCount];
        int tempCount = 0;
        for (int j = 0; j < currCount; j++)
        {
            if (currArr[j].reverseMatch(matches[i]))
            {
                tempArr[tempCount++] = currArr[j];
            }
        }
        if (i != 0)
            delete[] temp;
        temp = tempArr;
        currentPossibleWordsCount = tempCount;
    }
    delete[] temp;
    return currentPossibleWordsCount;
}
void GameMenu::readPossibleWords(char *filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Error opening file.");
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
            throw std::runtime_error("Error reading file.");
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
    std::cout << "Remaining possible words: " << getRemainingPossibleWordsCount() << std::endl;
    std::cout << "Current word: " << *currentWord << std::endl;
    if (getError() != nullptr)
    {
        std::cout << "\033[1;31m" << *getError() << "\033[0m" << std::endl;
    }
    for (int i = 0; i < guessedWordsCount; i++)
    {
        for (int j = 0; j < this->wordLength; j++)
        {
            switch (matches[i][j].getMatch())
            {
            case MATCH:
                std::cout << "\033[32m[" << guessedWords[i][j] << "]\033[0m ";
                break;
            case PARTIAL:
                std::cout << "\033[33m[" << guessedWords[i][j] << "]\033[0m ";
                break;
            default:
                std::cout << "[" << guessedWords[i][j] << "] ";
                break;
            }
        }
        std::cout << std::endl;
    }
    bool everythingMatched = true;
    if (guessedWordsCount == 0)
    {
        everythingMatched = false;
    }
    else
        for (int i = 0; i < this->wordLength; i++)
        {
            if (matches[guessedWordsCount - 1][i].getMatch() != MATCH)
            {
                everythingMatched = false;
                break;
            }
        }
    if (everythingMatched)
    {
        std::cout << "You won!" << std::endl;
    }
    else if (guessedWordsCount == maxGuesses)
    {
        std::cout << "You lost!" << std::endl;
        std::cout << "The word was: " << *currentWord << std::endl;
    }
    else
        for (int i = 0; i < maxGuesses - guessedWordsCount; i++)
        {
            for (int j = 0; j < this->wordLength; j++)
            {
                if (i == 0 && j == 0)
                {
                    std::cout << "[|] ";
                    continue;
                }

                std::cout << "[ ] ";
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
        throw std::runtime_error("Error opening file.");
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
            throw std::runtime_error("Error reading file.");
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
    bool invalid = false;
    for (int i = 0; i < wordLength; i++)
    {
        if (word[i].getBetu() < 'a' || word[i].getBetu() > 'z')
        {
            invalid = true;
            break;
        }
    }
    if (invalid || word.getLength() != wordLength)
    {
        throw std::runtime_error("Invalid guess!");
        return;
    }
    if (word.isInWords(possibleWords, possibleWordsCount) || word.isInWords(answerList, answerListCount))
    {
        if (word.isInWords(guessedWords, guessedWordsCount))
        {
            throw std::runtime_error("You have already guessed this word!");
            return;
        }
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
    else
    {
        throw std::runtime_error("Invalid guess!");
        return;
    }
    if (matches != nullptr)
    {
        for (int i = 0; i < guessedWordsCount - 1; i++)
        {
            delete[] matches[i];
        }
        delete[] matches;
    }

    matches = new Match *[guessedWordsCount];
    for (int i = 0; i < guessedWordsCount; i++)
    {
        matches[i] = currentWord->match(guessedWords[i]);
    }
    bool everythingMatched = true;
    if (guessedWordsCount == 0)
    {
        everythingMatched = false;
    }
    else
        for (int i = 0; i < this->wordLength; i++)
        {
            if (matches[guessedWordsCount - 1][i].getMatch() != MATCH)
            {
                everythingMatched = false;
                break;
            }
        }
    if (everythingMatched)
        this->isGuessed = true;
}

void GameMenu::resetGame()
{
    if (matches != nullptr)
    {
        for (int i = 0; i < guessedWordsCount; i++)
        {
            delete[] matches[i];
        }
        delete[] matches;
        matches = nullptr;
    }
    guessedWordsCount = 0;
    isGuessed = false;
    if (guessedWords != nullptr)
    {
        delete[] guessedWords;
        guessedWords = nullptr;
    }

#ifdef CPORTA
    currentWordIndex = 1;
#else
    srand((unsigned)time(NULL));
    int random = rand();

    currentWordIndex = random % answerListCount;
#endif
    currentWord = &answerList[currentWordIndex];
}