#ifndef MENU_H
#define MENU_H
class MenuItem;
class Menu
{
    MenuItem *items;
    Menu *parent;
    int itemCount;

public:
    Menu(Menu *p);
    Menu(const Menu &m);
    Menu() : parent(nullptr), itemCount(0), items(nullptr) {}
    ~Menu();
    void addItem(const char *text, void (*action)());
    void addItem(const char *text, Menu *subMenu);
    virtual void show() const;
};

class MenuItem
{
    char *text;
    void (*action)();
    Menu *subMenu;
    bool selectable = true;

public:
    MenuItem(const char *t, void (*a)());
    MenuItem(const char *t, Menu *s);
    MenuItem() : text(nullptr), action(nullptr), subMenu(nullptr), selectable(false){};
    ~MenuItem();
    char *getText() const;
    void (*getAction())();
    Menu *getSubMenu() const;
    inline bool getSelectable() const { return selectable; };
};
#endif
