#include "menu.h"
#include <iostream>
#include <cstring>

Menu::Menu(Menu *p)
{
    parent = p;
    itemCount = 0;
    items = nullptr;
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
}
Menu::~Menu()
{
    delete[] items;
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
}

MenuItem::MenuItem(const char *t, void (*a)())
{
    text = new char[strlen(t) + 1];
    strcpy(text, t);
    action = a;
    subMenu = 0;
}

MenuItem::MenuItem(const char *t, Menu *s)
{
    text = new char[strlen(t) + 1];
    strcpy(text, t);
    action = 0;
    subMenu = s;
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
