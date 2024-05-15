#ifndef STATS_MENU_H
#define STATS_MENU_H
#include "menu.h"
#include "szo.h"

class Stats
{
    Szo szo;
    int attempts;

public:
    Stats(Szo s, int a) : szo(s), attempts(a) {}
    Stats() : szo(), attempts(0) {}
    Szo getSzo() const { return szo; }
    int getAttempts() const { return attempts; }
};

class StatsMenu : public Menu
{
    Stats *stats;
    int statsCount;
    int maxAttempts;

public:
    StatsMenu(Menu *p) : Menu(p), stats(nullptr), statsCount(0), maxAttempts(0)
    {
        readStats((char *)"stats.csv");
    }
    StatsMenu() : Menu(), stats(nullptr), statsCount(0), maxAttempts(0)
    {
        readStats((char *)"stats.csv");
    }
    void show() const;
    void readStats(char *filename = (char *)"stats.csv");
    ~StatsMenu() { delete[] stats; }
    Stats operator[](int i) const { return stats[i]; }
    void setMaxAttempts(int m) { maxAttempts = m; }
    /// @brief Új statisztika mentése
    /// @tparam T A kísérletek száma
    /// @param filename A fájl neve
    /// @param attempts A kísérletek száma
    /// @param szo A szó
    template <typename T>
    void saveStats(char *filename, T attempts, Szo szo)
    {
        std::ofstream
            file(filename, std::ios_base::app);
        if (!file.is_open())
        {
            throw std::runtime_error("Error opening file.");
        }
        file << attempts << " " << szo << std::endl;
    }
    /// @brief Új statisztika mentése
    /// @tparam T A kísérletek száma
    /// @param attempts A kísérletek száma
    /// @param szo A szó
    template <typename T>
    void saveStats(T attempts, Szo szo) { saveStats((char *)"stats.csv", attempts, szo); }
    int getStatsCount() const { return statsCount; }
    Stats *getStats() const { return stats; }
};

#endif
