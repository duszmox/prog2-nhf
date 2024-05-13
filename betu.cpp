#include "betu.h"

/// @brief  Betu konstruktor
/// @param c  A karakter, amit a betu objektum tárol
Betu::Betu(char c)
{
    betu = c;
}
/// @brief A betu karakterének lekérdezése
/// @return A betu karaktere
char Betu::getBetu() const
{
    return betu;
}
/// @brief Megváltoztatja a betu karakterét
/// @param c Az új karakter
void Betu::setBetu(char c)
{
    betu = c;
}

/// @brief Egyenlőség operátor
/// @param b A másik betu objektum
/// @return  Igaz, ha a két betu karaktere megegyezik, egyébként hamis
int Betu::operator==(const Betu &b) const
{
    return betu == b.betu;
}

/// @brief Nem egyenlő operátor
/// @param b A másik betu objektum
/// @return  Igaz, ha a két betu karaktere nem egyezik meg, egyébként hamis
int Betu::operator!=(const Betu &b) const
{
    return betu != b.betu;
}

/// @brief Egyenlőség operátor char-ra
/// @param c A másik karakter
/// @return  Igaz, ha a betu karaktere megegyezik a paraméterként kapott karakterrel, egyébként hamis
int Betu::operator==(char c) const
{
    return betu == c;
}

/// @brief Kiiírja a betu karakterét
/// @param os  A kimeneti stream
/// @param b  A betu objektum
/// @return  A kimeneti stream
std::ostream &operator<<(std::ostream &os, const Betu &b)
{
    os << b.getBetu();
    return os;
}

/// @brief Megvizsgálja, hogy a betu objektumban tárolt karakter egy szám-e
/// @return Igaz, ha a betu karaktere szám, egyébként hamis
bool Betu::isNumber() const
{
    return betu >= '0' && betu <= '9';
}
