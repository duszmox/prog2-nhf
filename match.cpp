#include "match.h"

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