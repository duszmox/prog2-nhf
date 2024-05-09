#include "statsMenu.h"
#include <iostream>
#include <fstream>
#include <cstring>

void StatsMenu::show() const
{
    std::cout << "Number of guesses per game (%)" << std::endl;
    int attempsPerCount[maxAttempts + 2];
    int percentagePerCount[maxAttempts + 2];
    for (int i = 0; i <= maxAttempts; i++)
    {
        attempsPerCount[i] = 0;
    }
    for (int i = 0; i < statsCount; i++)
    {
        attempsPerCount[stats[i].getAttempts() == -1 ? maxAttempts + 1 : stats[i].getAttempts()]++;
    }
    for (int i = 0; i <= maxAttempts + 1; i++)
    {
        percentagePerCount[i] = attempsPerCount[i] * 100 / (statsCount - 1);
    }
    for (int i = 1; i <= maxAttempts + 1; i++)
    {
        Szo bar;
        int progressBarLength = 12;
        int filledBlocks = percentagePerCount[i] / (100 / progressBarLength);

        // Fill the progress bar string with filled and empty blocks
        for (int i = 0; i < filledBlocks - 1; ++i)
        {
            bar = bar + Szo("\u2588");
        }
        if (filledBlocks != 0)
        {
            bar = bar + Szo("\u2593"); // Unicode FULL BLOCK character
        }
        for (int i = filledBlocks; i < progressBarLength; ++i)
        {
            bar = bar + Szo("\u2591"); // Unicode LIGHT SHADE character
        }

        if (i == maxAttempts + 1)
        {
            std::cout << "X" << ": " << bar << " " << percentagePerCount[i] << "%" << std::endl;
        }
        else
        {
            std::cout << i << ": " << bar << " " << percentagePerCount[i] << "%" << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "Press 0 to return to the main menu." << std::endl;
}

void StatsMenu::readStats(char *filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Error opening file.");
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

void StatsMenu::saveStats(char *filename, char attempts, Szo szo)
{
    std::ofstream
        file(filename, std::ios_base::app);
    if (!file.is_open())
    {
        throw std::runtime_error("Error opening file.");
    }
    file << attempts << " " << szo << std::endl;
}

void StatsMenu::saveStats(char *filename, int attempts, Szo szo)
{
    std::ofstream
        file(filename, std::ios_base::app);
    if (!file.is_open())
    {
        throw std::runtime_error("Error opening file.");
    }
    file << attempts << " " << szo << std::endl;
}