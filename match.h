#ifndef MATCH_H
#define MATCH_H
#include "memtrace.h"
#include "betu.h"

enum MatchTypes
{
    MATCH,
    NOMATCH,
    PARTIAL
};
class Match
{
    MatchTypes match;
    Betu *betu;

public:
    Match(MatchTypes m, Betu *b) : match(m), betu(b) {}
    Match() : match(NOMATCH), betu(nullptr) {}
    MatchTypes getMatch() const { return match; }
    Betu *getBetu() const { return betu; }
    void setMatch(MatchTypes m) { match = m; }
    void setBetu(Betu *b) { betu = b; }
    ~Match()
    {
        if (betu != nullptr)
        {
            delete betu;
        }
    }
};
std::ostream &operator<<(std::ostream &os, const Match &m);

#endif
