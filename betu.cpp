#include "betu.h"

Betu::Betu(char c)
{
    betu = c;
}

char Betu::getBetu() const
{
    return betu;
}

void Betu::setBetu(char c)
{
    betu = c;
}

int Betu::operator==(const Betu &b) const
{
    return betu == b.betu;
}

int Betu::operator!=(const Betu &b) const
{
    return betu != b.betu;
}

int Betu::operator==(char c) const
{
    return betu == c;
}

std::ostream &operator<<(std::ostream &os, const Betu &b)
{
    os << b.getBetu();
    return os;
}