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
    void saveStats(char *filename, char attempts, Szo szo);
    void saveStats(char *filename, int attempts, Szo szo);
    void saveStats(char attempts, Szo szo) { saveStats((char *)"stats.csv", attempts, szo); }
    void saveStats(int attempts, Szo szo) { saveStats((char *)"stats.csv", attempts, szo); }
    int getStatsCount() const { return statsCount; }
    Stats *getStats() const { return stats; }
};

#endif