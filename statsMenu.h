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

public:
    StatsMenu(Menu *p) : Menu(p), stats(nullptr), statsCount(0) {}
    StatsMenu() : Menu(), stats(nullptr), statsCount(0) {}
    void show() const;
    void readStats(char *filename);
    ~StatsMenu();
    Stats operator[](int i) const { return stats[i]; }
};

#endif