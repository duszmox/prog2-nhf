#include "match.h"

/// @brief Kiírja a Match objektumot
/// @param os A kimeneti stream
/// @param m A Match objektum
/// @return  A kimeneti stream
std::ostream &operator<<(std::ostream &os, const Match &m)
{
    switch (m.getMatch())
    {
    case MATCH:
        os << "MATCH";
        break;
    case NOMATCH:
        os << "NOMATCH";
        break;
    case PARTIAL:
        os << "PARTIAL";
        break;
    default:
        os << "UNKNOWN";
        break;
    }
    return os;
}

Match::~Match()
{
    if (betu != nullptr)
    {
        delete betu;
    }
}