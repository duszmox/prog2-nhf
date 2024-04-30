#include "szo.h"
#include <cstring>

Szo::Szo(const char *s)
{
    length = strlen(s);
    betuk = new Betu[length];
    for (int i = 0; i < length; i++)
    {
        betuk[i] = Betu(s[i]);
    }
}

Szo::Szo(const Szo &s)
{
    length = s.length;
    betuk = new Betu[length];
    for (int i = 0; i < length; i++)
    {
        betuk[i] = s.betuk[i];
    }
}

Szo::~Szo()
{
    delete[] betuk;
}

Szo &Szo::operator=(const Szo &s)
{
    if (this != &s)
    {
        delete[] betuk;
        length = s.length;
        betuk = new Betu[length];
        for (int i = 0; i < length; i++)
        {
            betuk[i] = s.betuk[i];
        }
    }
    return *this;
}

int Szo::operator==(const Szo &s) const
{
    if (length != s.length)
    {
        return 0;
    }
    for (int i = 0; i < length; i++)
    {
        if (betuk[i] != s.betuk[i])
        {
            return 0;
        }
    }
    return 1;
}

int Szo::operator!=(const Szo &s) const
{
    return !(*this == s);
}

int Szo::operator==(const char *s) const
{
    int len = strlen(s);
    if (length != len)
    {
        return 0;
    }
    for (int i = 0; i < length; i++)
    {
        if (betuk[i] != s[i])
        {
            return 0;
        }
    }
    return 1;
}

int Szo::operator!=(const char *s) const
{
    return !(*this == s);
}

Match *Szo::match(const Szo &s) const
{
    Match *matches = new Match[length];
    bool visited[length];
    for (int i = 0; i < length; i++)
        if (betuk[i] == s.betuk[i])
        {
            visited[i] = true;
            matches[i].setMatch(MATCH);
            matches[i].setBetu(new Betu(s.betuk[i]));
        }
        else
            visited[i] = false;

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (betuk[i] == s.betuk[j] && !visited[j])
            {
                matches[j].setMatch(PARTIAL);
                matches[j].setBetu(new Betu(s.betuk[j]));
                visited[i] = true;
                break;
            }
        }
    }
    for (int i = 0; i < length; i++)
    {
        if (matches[i].getMatch() == NOMATCH)
        {
            matches[i].setBetu(new Betu(betuk[i]));
        }
    }
    return matches;
}

Betu &Szo::operator[](int i) const
{
    return betuk[i];
}

Szo::Szo(const Betu *b, int l)
{
    length = l;
    betuk = new Betu[length];
    for (int i = 0; i < length; i++)
    {
        betuk[i] = b[i];
    }
}

std::ostream &operator<<(std::ostream &os, const Szo &s)
{
    for (int i = 0; i < s.getLength(); i++)
    {
        os << s.getBetuk()[i];
    }
    return os;
}
bool Szo::reverseMatch(Match *m) const
{
    int length = getLength();
    bool visited[length];
    for (int i = 0; i < length; i++)
    {
        if (m[i].getMatch() == MATCH)
        {
            if (*m[i].getBetu() != betuk[i])
            {
                return false;
            }
            else
            {
                visited[i] = true;
            }
        }
    }
    for (int i = 0; i < length; i++)
    {
        if (visited[i])
        {
            continue;
        }
        if (m[i].getMatch() == PARTIAL)
        {
            bool found = false;
            for (int j = 0; j < length; j++)
            {
                if (*m[i].getBetu() == betuk[j] && !visited[j])
                {
                    visited[j] = true;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                return false;
            }
        }
    }
    return true;
}