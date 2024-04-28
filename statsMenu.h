#ifndef STATS_MENU_H
#define STATS_MENU_H
#include "menu.h"
#include "szo.h"

class Stats
{
    Szo szo;
    int attempts;
};

class statsMenu : public Menu
{
    Stats *stats;
    int statsCount;

public:
    statsMenu(Menu *p) : Menu(p), stats(nullptr), statsCount(0)
    {
        readStats("stats.csv");
    }
    statsMenu() : Menu(), stats(nullptr), statsCount(0)
    {
        readStats("stats.csv");
    }
    void show() const;
    void readStats(char *filename);
};

#endif