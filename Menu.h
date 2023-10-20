

#ifndef SDDS_MENU_H_
#define SDDS_MENU_H_
#define MAX_MENU_ITEMS 20

#include <iostream>
namespace sdds
{
    class Menu;
    class MenuItem
    {
        char *m_menuName;
        friend class Menu;

        void setName(const char *name);
        MenuItem();
        MenuItem(const char *name);
        ~MenuItem();
        operator bool() const;

        operator const char *() const;
        std::ostream &display() const;

        MenuItem(const MenuItem &) = delete;
        MenuItem &operator=(const MenuItem &) = delete;
    };

    class Menu
    {
        MenuItem m_item;
        MenuItem *m_itemPtr[MAX_MENU_ITEMS];
        int m_totalptr;

    public:
        Menu();
        Menu(const char *name);
        ~Menu();

        Menu(const Menu &) = delete;
        Menu &operator=(const Menu &) = delete;

        std::ostream &displayMenu(std::ostream &os = std::cout) const;
        void displayItem();

        unsigned int run();
        unsigned int operator~();

        Menu &operator<<(const char *menuItemConent);
        operator int() const;
        operator unsigned int() const;
        operator bool() const;
        const char *operator[](unsigned int index) const;
    };

    std::ostream &operator<<(std::ostream &ls, const Menu &rs);

}

#endif // !SDDS_MENU_H_
