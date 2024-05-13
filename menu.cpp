#include "menu.h"
#include <iostream>
#include <cstring>
#include "szo.h"
#ifdef _WIN32
#include <windows.h>
#endif

/// @brief A menü konstruktora
/// @param p Az őt tartalmazó menü memóriacíme
Menu::Menu(Menu *p)
{
    parent = p;
    itemCount = 0;
    items = nullptr;
    error = nullptr;
}

/// @brief A menü másoló konstruktora
/// @param m  A másolandó menü
Menu::Menu(const Menu &m)
{
    parent = m.parent;
    itemCount = m.itemCount;
    items = new MenuItem[itemCount];
    for (int i = 0; i < itemCount; i++)
    {
        items[i] = m.items[i];
    }
    if (m.error != nullptr)
    {
        setError(*m.error);
    }
    else
    {
        clearError();
    }
}
/// @brief A menü destruktora
Menu::~Menu()
{
    delete[] items;
    if (error != nullptr)
    {
        delete error;
    }
}

/// @brief Menüpont hozzáadása művelettel
/// @param text A menüpont szövege
/// @param action  A menüpont művelete
void Menu::addItem(const char *text, void (*action)())
{
    MenuItem *newItems = new MenuItem[itemCount + 1];
    for (int i = 0; i < itemCount; i++)
    {
        newItems[i] = items[i];
    }
    newItems[itemCount] = MenuItem(text, action);
    delete[] items;
    items = newItems;
    itemCount++;
}

/// @brief Menüpont hozzáadása almenüvel
/// @param text A menüpont szövege
/// @param subMenu  Az almenü memóriacíme
void Menu::addItem(const char *text, Menu *subMenu)
{
    MenuItem *newItems = new MenuItem[itemCount + 1];
    for (int i = 0; i < itemCount; i++)
    {
        newItems[i] = items[i];
    }
    newItems[itemCount] = MenuItem(text, subMenu);
    delete[] items;
    items = newItems;
    itemCount++;
}

/// @brief Menü megjelenítése
void Menu::show() const
{
    int selection = 0;
    for (int i = 0; i < itemCount; i++)
    {
        if (items[i].getSelectable())
        {
            selection++;
            std::cout << selection << ". " << items[i].getText() << std::endl;
        }
        else
        {
            std::cout << items[i].getText() << std::endl;
        }
    }
    std::cout << "0. Exit" << std::endl;
    if (error != nullptr)
    {
        std::cout << "\033[1;31m" << *error << "\033[0m" << std::endl;
    }
}

/// @brief Menüpont konstruktor művelettel
/// @param t A menüpont szövege
/// @param a A menüpont művelete
MenuItem::MenuItem(const char *t, void (*a)())
{
    text = new char[strlen(t) + 1];
    strcpy(text, t);
    action = a;
    subMenu = 0;
    selectable = true;
}

/// @brief Menüpont konstruktor almenüvel
/// @param t A menüpont szövege
/// @param s A menüpont almenüje
MenuItem::MenuItem(const char *t, Menu *s)
{
    text = new char[strlen(t) + 1];
    strcpy(text, t);
    action = 0;
    subMenu = s;
    selectable = true;
}

/// @brief Menüpont destruktora
MenuItem::~MenuItem()
{
    delete[] text;
}

/// @brief A menüpont szövegének lekérdezése
/// @return  A menüpont szövege
char *MenuItem::getText() const
{
    return text;
}

/// @brief A menüpont műveletének lekérdezése
/// @return  A menüpont művelete
void (*MenuItem::getAction())()
{
    return action;
}

/// @brief A menüpont almenüjének lekérdezése
/// @return  A menüpont almenüje
Menu *MenuItem::getSubMenu() const
{
    return subMenu;
}

/// @brief A menüpont egyenlőség operátora
/// @param m A másik menüpont
void MenuItem::operator=(const MenuItem &m)
{
    text = new char[strlen(m.text) + 1];
    strcpy(text, m.text);
    action = m.action;
    subMenu = m.subMenu;
    selectable = m.selectable;
}

/// @brief Két menü egyenlőségének vizsgálata
/// @param m A másik menü
/// @return  Igaz, ha a két menü megegyezik, egyébként hamis
bool Menu::operator==(const Menu &m) const
{
    if (itemCount != m.itemCount)
    {
        return false;
    }
    for (int i = 0; i < itemCount; i++)
    {
        if (items[i] != m.items[i])
        {
            return false;
        }
    }
    return true;
}

/// @brief A két menü egyenlőtlenségének vizsgálata
/// @param m A másik menü
/// @return  Igaz, ha a két menü nem egyezik meg, egyébként hamis
bool Menu::operator!=(const Menu &m) const
{
    return !(*this == m);
}

/// @brief A menü indexelő operátora
/// @param i  Az index
/// @return  A menüpont a megadott indexen
MenuItem &Menu::operator[](int i) const
{
    return items[i];
}

/// @brief A két menüpont egyenlőségének vizsgálata
/// @param m  A másik menüpont
/// @return  Igaz, ha a két menüpont megegyezik, egyébként hamis
bool MenuItem::operator==(const MenuItem &m) const
{
    if (strcmp(text, m.text) != 0)
    {
        return false;
    }
    if (action != m.action)
    {
        return false;
    }
    if (subMenu != m.subMenu)
    {
        return false;
    }
    return true;
}

/// @brief A két menüpont egyenlőtlenségének vizsgálata
/// @param m A másik menüpont
/// @return  Igaz, ha a két menüpont nem egyezik meg, egyébként hamis
bool MenuItem::operator!=(const MenuItem &m) const
{
    return !(*this == m);
}

/// @brief Hibaüzenet beállítása a menühöz
/// @param s  A hibaüzenet szövege
void Menu::setError(const Szo s)
{
    clearError();
    error = new Szo(s);
}

/// @brief Hibaüzenet törlése
void Menu::clearError()
{
    if (error != nullptr)
    {
        delete error;
        error = nullptr;
    }
}

/// @brief A hiabüzenet lekérdezése
/// @return  A hibaüzenet
Szo *Menu::getError() const
{
    return error;
}

/// @brief A Logo megjelenítése
void Menu::showLogo() const
{
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    // clear screen
    system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
    std::cout << "██╗    ██╗ ██████╗ ██████╗ ██████╗ ██╗     ███████╗" << std::endl;
    std::cout << "██║    ██║██╔═══██╗██╔══██╗██╔══██╗██║     ██╔════╝" << std::endl;
    std::cout << "██║ █╗ ██║██║   ██║██████╔╝██║  ██║██║     █████╗" << std::endl;
    std::cout << "██║███╗██║██║   ██║██╔══██╗██║  ██║██║     ██╔══╝" << std::endl;
    std::cout << "╚███╔███╔╝╚██████╔╝██║  ██║██████╔╝███████╗███████╗" << std::endl;
    std::cout << " ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝" << std::endl;
}