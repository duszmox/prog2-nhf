#ifndef BETU_H
#define BETU_H
#include <iostream>
class Betu
{
    char betu;

public:
    Betu(char c);
    Betu() : betu(0) {}
    char getBetu() const;
    void setBetu(char c);
    int operator==(const Betu &b) const;
    int operator!=(const Betu &b) const;
    int operator==(char c) const;
    bool isNumber() const;
};
std::ostream &operator<<(std::ostream &os, const Betu &b);
#endif
