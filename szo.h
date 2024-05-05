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
    Szo() : length(0), betuk(nullptr){};
    Szo(const Szo &s);
    Szo(const Betu *b, int l);
    ~Szo();
    Szo &operator=(const Szo &s);
    int operator==(const Szo &s) const;
    int operator!=(const Szo &s) const;
    int operator==(const char *s) const;
    int operator!=(const char *s) const;
    Match *match(const Szo &s) const;
    Betu &operator[](int i) const;
    inline int getLength() const { return length; }
    Betu *getBetuk() const { return betuk; }
    bool reverseMatch(Match *m) const;
    bool containsNumber() const;
    Szo &operator+=(const Betu &b);
    Szo operator+(const Szo &s) const;
    const char *c_str() const;
};
std::ostream &operator<<(std::ostream &os, const Szo &s);
bool isInWords(const Szo *words, const int len, const Szo &word);
std::istream &operator>>(std::istream &is, Szo &s);

#endif
