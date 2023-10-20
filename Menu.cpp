

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"
using namespace std;

namespace sdds
{

    void MenuItem::setName(const char *name)
    {
        if (name[0] != '\0' && name != nullptr)
        {
            delete[] m_menuName;

            m_menuName = new char[strlen(name) + 1];
            strcpy(m_menuName, name);
        }
    }

    MenuItem::MenuItem()
    {
        m_menuName = nullptr;
    }

    MenuItem::MenuItem(const char *name)
    {

        m_menuName = nullptr;
        if (name != nullptr && name[0] != '\0')
        {
            setName(name);
        }
    }

    MenuItem::~MenuItem()
    {
        delete[] m_menuName;
        m_menuName = nullptr;
    }

    MenuItem::operator bool() const
    {
        if (m_menuName != nullptr)
            return true;
        return false;
    }

    bool isValid(unsigned int &input, unsigned int min, unsigned int max)
    {
        bool success = true;
        char newline{};
        cin >> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(2000, '\n');
            success = false;
        }
        else
        {
            newline = cin.get();
            if (cin.fail() || newline != '\n')
            {
                success = false;
                cin.clear();
                cin.ignore(1000, '\n');
            }
            if (input < min || input > max)
                success = false;
        }
        return success;
    }

    MenuItem::operator const char *() const
    {
        return (const char *)m_menuName;
    }

    std::ostream &MenuItem::display() const
    {
        if (*this)
        {
            cout << (const char *)(*this);
        }
        return cout;
    }

    Menu::Menu()
    {
        m_totalptr = 0;
    }
    Menu::Menu(const char *name)
    {
        m_totalptr = 0;
        if (name != nullptr && name[0] != '\0')
            m_item.setName(name);
    }
    Menu::~Menu()
    {

        for (int i = 0; i < m_totalptr; i++)
        {
            // m_itemPtr[i]->~MenuItem();
            delete m_itemPtr[i];
            m_itemPtr[i] = nullptr;
        }
    }

    std::ostream &Menu::displayMenu(std::ostream &os) const
    {
        if (m_item)
        {
            m_item.display();
        }
        return os;
    }

    Menu &Menu::operator<<(const char *menuItemConent)
    {
        if (m_totalptr < MAX_MENU_ITEMS)
        {
            m_itemPtr[m_totalptr] = new MenuItem;
            m_itemPtr[m_totalptr]->setName(menuItemConent);
            m_totalptr++;
        }
        return *this;
    }

    Menu::operator int() const
    {
        return m_totalptr;
    }

    Menu::operator unsigned int() const
    {
        return (unsigned int)m_totalptr;
    }

    void Menu::displayItem()
    {
        if (m_item)
        {
            displayMenu() << endl;
        }
        cout.setf(ios::fixed);
        for (int i = 0; i < m_totalptr; i++)
        {
            cout.width(2);
            cout << i + 1 << "- ";
            m_itemPtr[i]->display() << endl;
        }
        cout << " 0- Exit" << endl;
        cout << "> ";
    }

    unsigned int Menu::operator~()
    {
        unsigned int num;
        displayItem();
        while (!isValid(num, 0, m_totalptr))
        {
            cout << "Invalid Selection, try again: ";
        }
        return num;
    }

    Menu::operator bool() const
    {
        return (m_totalptr > 0);
    }

    const char *Menu::operator[](unsigned int index) const
    {
        return (const char *)(*m_itemPtr[index % m_totalptr]);
    }

    unsigned int Menu::run()
    {
        unsigned int num;
        displayItem();
        while (!isValid(num, 0, m_totalptr))
        {
            cout << "Invalid Selection, try again: ";
        }
        return num;
    }

    std::ostream &operator<<(std::ostream &ls, const Menu &rs)
    {
        return rs.displayMenu(ls);
    }

}
