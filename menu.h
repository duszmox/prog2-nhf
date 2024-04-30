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
    virtual ~Menu();
    void addItem(const char *text, void (*action)());
    void addItem(const char *text, Menu *subMenu);
    virtual void show() const;
    Menu &getParent() const { return *parent; };
    MenuItem &operator[](int i) const;
    bool operator==(const Menu &m) const;
    bool operator!=(const Menu &m) const;
    inline int getItemCount() const { return itemCount; };
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
    void operator=(const MenuItem &m);
    bool operator==(const MenuItem &m) const;
    bool operator!=(const MenuItem &m) const;
};
#endif
