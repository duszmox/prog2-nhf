#include "menu.h"
#include <iostream>
#include <cstring>
#include "szo.h"

Menu::Menu(Menu *p)
{
    parent = p;
    itemCount = 0;
    items = nullptr;
    error = nullptr;
}

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
Menu::~Menu()
{
    delete[] items;
    if (error != nullptr)
    {
        delete error;
    }
}

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

MenuItem::MenuItem(const char *t, void (*a)())
{
    text = new char[strlen(t) + 1];
    strcpy(text, t);
    action = a;
    subMenu = 0;
    selectable = true;
}

MenuItem::MenuItem(const char *t, Menu *s)
{
    text = new char[strlen(t) + 1];
    strcpy(text, t);
    action = 0;
    subMenu = s;
    selectable = true;
}
MenuItem::~MenuItem()
{
    delete[] text;
}
char *MenuItem::getText() const
{
    return text;
}
void (*MenuItem::getAction())()
{
    return action;
}
Menu *MenuItem::getSubMenu() const
{
    return subMenu;
}

void MenuItem::operator=(const MenuItem &m)
{
    text = new char[strlen(m.text) + 1];
    strcpy(text, m.text);
    action = m.action;
    subMenu = m.subMenu;
    selectable = m.selectable;
}

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

bool Menu::operator!=(const Menu &m) const
{
    return !(*this == m);
}

MenuItem &Menu::operator[](int i) const
{
    return items[i];
}

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

bool MenuItem::operator!=(const MenuItem &m) const
{
    return !(*this == m);
}

void Menu::setError(const Szo s)
{
    clearError();
    error = new Szo(s);
}

void Menu::clearError()
{
    if (error != nullptr)
    {
        delete error;
        error = nullptr;
    }
}

Szo *Menu::getError() const
{
    return error;
}
void Menu::showLogo() const
{
    std::cout << "\033[2J\033[1;1H";
    std::cout << "██╗    ██╗ ██████╗ ██████╗ ██████╗ ██╗     ███████╗" << std::endl;
    std::cout << "██║    ██║██╔═══██╗██╔══██╗██╔══██╗██║     ██╔════╝" << std::endl;
    std::cout << "██║ █╗ ██║██║   ██║██████╔╝██║  ██║██║     █████╗" << std::endl;
    std::cout << "██║███╗██║██║   ██║██╔══██╗██║  ██║██║     ██╔══╝" << std::endl;
    std::cout << "╚███╔███╔╝╚██████╔╝██║  ██║██████╔╝███████╗███████╗" << std::endl;
    std::cout << " ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝" << std::endl;
}