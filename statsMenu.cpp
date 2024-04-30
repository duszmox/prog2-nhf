#include "statsMenu.h"
#include <iostream>
#include <fstream>
#include <cstring>

void StatsMenu::show() const
{
    std::cout << "Stats menu" << std::endl;
    for (int i = 0; i < statsCount; i++)
    {
        std::cout << stats[i].getSzo() << " " << stats[i].getAttempts() << std::endl;
    }
}

void StatsMenu::readStats(char *filename = "stats.csv")
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
    }
    statsCount = 0;
    int bufferSize = 64;
    char *word = new char[bufferSize];
    int length = 0;
    char ch;
    int attempts = 0;
    Szo szo;
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
    szo = Szo(word);
    file >> attempts;
    stats[statsCount++] = Stats(szo, attempts);
    delete[] word;
}

StatsMenu::~StatsMenu()
{
    delete[] stats;
}