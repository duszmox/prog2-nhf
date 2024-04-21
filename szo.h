#ifndef SZO_H
#define SZO_H
#include "betu.h"
#include "match.h"
class Szo
{
    int length;
    Betu *betuk;

public:
    Szo(const char *s);
    Szo(const Szo &s);
    ~Szo();
    Szo &operator=(const Szo &s);
    int operator==(const Szo &s) const;
    int operator!=(const Szo &s) const;
    int operator==(const char *s) const;
    int operator!=(const char *s) const;
    Match *match(const Szo &s) const;
    Betu &operator[](int i) const;
    inline int getLength() const { return length; }
};
#endif
