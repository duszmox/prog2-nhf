#include "szo.h"
#include "memtrace.h"
#include <cstring>

/// @brief Szó konstruktora karaktertömbből
/// @param s  A karaktertömb
Szo::Szo(const char *s)
{
    length = strlen(s);
    betuk = new Betu[length];
    for (int i = 0; i < length; i++)
    {
        betuk[i] = Betu(s[i]);
    }
}

/// @brief Szó másoló konstruktora
/// @param s  A másolandó szó
Szo::Szo(const Szo &s)
{
    length = s.length;
    betuk = new Betu[length];
    for (int i = 0; i < length; i++)
    {
        betuk[i] = s.betuk[i];
    }
}

/// @brief Szó destruktora
Szo::~Szo()
{
    delete[] betuk;
}

/// @brief A szó egyenlőség operátora
/// @param s  A másik szó
/// @return Az új szó
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

/// @brief A szó egyenlőség operátora
/// @param s  A karaktertömb
/// @return Igaz, ha a szó megegyezik a karaktertömbbel, egyébként hamis
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

/// @brief A szó egyenlőtlenség operátora
/// @param s  A másik szó
/// @return Igaz, ha a szó nem egyezik meg a másikkal, egyébként hamis
int Szo::operator!=(const Szo &s) const
{
    return !(*this == s);
}

/// @brief A szó egyenlőség operátora karaktertömbre
/// @param s  A karaktertömb
/// @return Igaz, ha a szó megegyezik a karaktertömbbel, egyébként hamis
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

/// @brief A szó egyenlőtlenség operátora karaktertömbre
/// @param s  A karaktertömb
/// @return Igaz, ha a szó nem egyezik meg a karaktertömbbel, egyébként hamis
int Szo::operator!=(const char *s) const
{
    return !(*this == s);
}

/// @brief Két szó közös betűinek megtalálása
/// @param s  A másik szó
/// @return  A megtalált betűk Match tömbje
Match *Szo::match(const Szo &s) const
{
    Match *matches = new Match[length];
    bool *visited = new bool[length];
    for (int i = 0; i < length; i++)
    {
        if (betuk[i] == s.betuk[i])
        {
            matches[i].setMatch(MATCH);
            matches[i].setBetu(new Betu(betuk[i]));
            visited[i] = true;
        }
        else
        {
            visited[i] = false;
        }
    }

    for (int i = 0; i < length; i++)
    {
        if (matches[i].getMatch() == MATCH)
        {
            continue;
        }
        for (int j = 0; j < length; j++)
        {
            if (visited[j] || i == j)
            {
                continue;
            }
            if (s.betuk[i] == betuk[j])
            {
                matches[i].setMatch(PARTIAL);
                matches[i].setBetu(new Betu(s.betuk[i]));
                visited[j] = true;
                break;
            }
        }
    }
    for (int i = 0; i < length; i++)
    {
        if (matches[i].getMatch() == NOMATCH)
        {
            matches[i].setBetu(new Betu(s.betuk[i]));
        }
    }
    delete[] visited;
    return matches;
}

/// @brief A szó indexelő operátora
/// @param i Az index
/// @return  A szó i-edik betűje
Betu &Szo::operator[](int i) const
{
    return betuk[i];
}

/// @brief A szó konstrukora betűtömbből
/// @param b A betűtömb
/// @param l A betűtömb hossza
Szo::Szo(const Betu *b, int l)
{
    length = l;
    betuk = new Betu[length];
    for (int i = 0; i < length; i++)
    {
        betuk[i] = b[i];
    }
}

/// @brief A szó kiírása
/// @param os  A kimeneti stream
/// @param s A szó
/// @return A kimeneti stream
std::ostream &operator<<(std::ostream &os, const Szo &s)
{
    for (int i = 0; i < s.getLength(); i++)
    {
        os << s.getBetuk()[i];
    }
    return os;
}

/// @brief A szó match tömbbel való egyezése
/// @param m A match tömb
/// @return  Igaz, ha a match tömb megfelel a szónak, egyébként hamis
bool Szo::reverseMatch(Match *m) const
{
    bool *visited = new bool[length];
    for (int i = 0; i < length; i++)
    {
        if (m[i].getMatch() == MATCH)
        {
            if (betuk[i] != *m[i].getBetu())
            {
                return false;
            }
            else
            {
                visited[i] = true;
            }
        }
        else
        {
            visited[i] = false;
        }
    }
    for (int i = 0; i < length; i++)
    {
        if (m[i].getMatch() == PARTIAL)
        {
            if (betuk[i] == *m[i].getBetu())
            {
                return false;
            }
            bool found = false;
            for (int j = 0; j < length; j++)
            {
                if (betuk[j] == *m[i].getBetu() && !visited[j] && j != i)
                {
                    if ((m[j].getMatch() == NOMATCH && *m[j].getBetu() == betuk[j]))
                        continue;
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
    for (int i = 0; i < length; i++)
    {
        if (m[i].getMatch() == NOMATCH)
        {
            for (int j = 0; j < length; j++)
            {
                if (betuk[j] == *m[i].getBetu() && !visited[j])
                {
                    return false;
                }
            }
        }
    }
    delete[] visited;
    return true;
}

/// @brief Egy szó keresése egy szavak tömbben
/// @param words A szavak tömbje
/// @param len A szavak tömbjének hossza
/// @return  Igaz, ha a szó megtalálható a szavak tömbjében, egyébként hamis
bool Szo::isInWords(const Szo *words, const int len) const
{
    for (int i = 0; i < len; i++)
    {
        if (words[i] == *this)
        {
            return true;
        }
    }
    return false;
}

/// @brief Betű hozzáfűzése a szóhoz
/// @param b A betű
/// @return Az új szó
Szo &Szo::operator+=(const Betu &b)
{
    Betu *temp = new Betu[length + 1];
    for (int i = 0; i < length; i++)
    {
        temp[i] = betuk[i];
    }
    temp[length] = b;
    delete[] betuk;
    betuk = temp;
    length++;
    return *this;
}

/// @brief Szó beolvasása
/// @param is A bemeneti stream
/// @param s0  A szó
/// @return  A bemeneti stream
std::istream &operator>>(std::istream &is, Szo &s0)
{
    unsigned char ch;
    s0 = Szo("");                            // üres string, ehhez fűzünk hozzá
    std::ios_base::fmtflags fl = is.flags(); // eltesszük a régi flag-eket
    is.setf(std::ios_base::skipws);          // az elején eldobjuk a ws-t
    while (is >> ch)
    {
        is.unsetf(std::ios_base::skipws); // utána pedig már nem
        if (isspace(ch))
        {
            is.putback(ch); // na ezt nem kérjük
            break;
        }
        else
        {
            s0 += ch; // végére fűzzük a karaktert
        }
    }
    is.setf(fl); // visszaállítjuk a flag-eket
    return is;
}

/// @brief A szó karaktertömbbé alakítása
/// @return  A karaktertömb
const char *Szo::c_str() const
{
    char *s = new char[length + 1];
    for (int i = 0; i < length; i++)
    {
        s[i] = betuk[i].getBetu();
    }
    s[length] = '\0';
    return s;
}

/// @brief Két szó összefűzése
/// @param s  A másik szó
/// @return  Az új szó
Szo Szo::operator+(const Szo &s) const
{
    Szo temp;
    temp.length = length + s.length;
    temp.betuk = new Betu[temp.length];
    for (int i = 0; i < length; i++)
    {
        temp.betuk[i] = betuk[i];
    }
    for (int i = 0; i < s.length; i++)
    {
        temp.betuk[i + length] = s.betuk[i];
    }
    return temp;
}
