#include "statsMenu.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

/// @brief A statisztikák menü megjelenítése
void StatsMenu::show() const
{
    std::cout << "Number of guesses per game (%)" << std::endl;
    int *attempsPerCount = new int[maxAttempts + 1];
    int *percentagePerCount = new int[maxAttempts + 1];
    for (int i = 0; i <= maxAttempts; i++)
    {
        attempsPerCount[i] = 0;
        for (int j = 0; j < statsCount; j++)
        {
            if (stats[j].getAttempts() == i + 1)
            {
                attempsPerCount[i]++;
            }
            else if (stats[j].getAttempts() == -1)
            {
                attempsPerCount[maxAttempts]++;
            }
        }
    }
    for (int i = 0; i <= maxAttempts; i++)
    {
        percentagePerCount[i] = (attempsPerCount[i] * 100) / statsCount;
        if (percentagePerCount[i] > 100)
        {
            delete[] attempsPerCount;
            delete[] percentagePerCount;
            throw std::runtime_error("Error while calculating stats.");
        }
    }
    for (int i = 0; i <= maxAttempts; i++)
    {
        Szo bar;
        int progressBarLength = 12;
        int filledBlocks = percentagePerCount[i] / (100 / progressBarLength);

        for (int i = 0; i < filledBlocks - 1; ++i)
        {
            bar = bar + Szo("\u2588");
        }
        if (filledBlocks != 0)
        {
            bar = bar + Szo("\u2593");
        }
        for (int i = filledBlocks; i < progressBarLength; ++i)
        {
            bar = bar + Szo("\u2591");
        }

        if (i == maxAttempts)
        {
            std::cout << "X" << ": " << bar << " " << percentagePerCount[i] << "%" << std::endl;
        }
        else
        {
            std::cout << i + 1 << ": " << bar << " " << percentagePerCount[i] << "%" << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "Press 0 to return to the main menu." << std::endl;
    delete[] attempsPerCount;
    delete[] percentagePerCount;
}

/// @brief A statisztikák beolvasása fájlból
/// @param filename A fájl neve
void StatsMenu::readStats(char *filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::ofstream newFile(filename);
        newFile.close();
        file.open(filename);
    }
    statsCount = 0;
    Szo szo;
    char attempts;
    while (file >> attempts >> szo)
    {
        Stats *newStats = new Stats[statsCount + 1];
        for (int i = 0; i < statsCount; i++)
        {
            newStats[i] = stats[i];
        }
        newStats[statsCount] = Stats(szo, attempts == 'X' ? -1 : std::atoi(&attempts));
        delete[] stats;
        stats = newStats;
        statsCount++;
    }
    file.close();
}
