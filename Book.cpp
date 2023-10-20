

#include <cstring>
#include <iomanip>
#include "Book.h"
#include "Lib.h"
using namespace std;

namespace sdds
{
    char Book::type() const
    {
        return 'B';
    }
    Book::~Book()
    {
        delete[] m_author;
        m_author = nullptr;
    }
    Book &Book::operator=(const Book &other)
    {
        if (this != &other)
        {
            (Publication &)*this = other;

            delete[] m_author;
            m_author = nullptr;

            if (other.m_author != nullptr)
            {
                m_author = new char[strlen(other.m_author) + 1];
                strcpy(m_author, other.m_author);
            }
        }
        return *this;
    }
    Book::Book(const Book &other)
    {
        *this = other;
    }

    ostream &Book::write(ostream &os) const
    {
        Publication::write(os);

        if (conIO(os) && *this)
        {
            os << " ";

            if (strlen(m_author) > SDDS_AUTHOR_WIDTH)
            {
                for (int i = 0; i < SDDS_AUTHOR_WIDTH; i++)
                {
                    os << m_author[i];
                }
            }
            else
            {
                os.width(SDDS_AUTHOR_WIDTH);
                os.setf(ios::left);
                os << m_author;
                os.unsetf(ios::left);

                // os << std::setw(SDDS_AUTHOR_WIDTH) << std::left << m_author << left;
            }
            os << " |";
        }
        else if (*this)
            os << '\t' << m_author;
        return os;
    }

    istream &Book::read(istream &is)
    {
        Publication::read(is);
        char tempauthor[256] = "";

        delete[] m_author;
        m_author = nullptr;

        is.ignore();

        if (conIO(is))
            cout << "Author: ";

        is.get(tempauthor, 256);

        if (is.good())
        {
            m_author = new char[strlen(tempauthor) + 1];
            strcpy(m_author, tempauthor);
        }
        return is;
    }
    void Book::set(int Member_id)
    {
        Publication::set(Member_id);
        resetDate();
    }
    Book::operator bool() const
    {
        return (m_author != nullptr && m_author[0] != '\0');
    }
}
