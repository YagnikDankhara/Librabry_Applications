

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include "Publication.h"
using namespace std;
namespace sdds
{
    class Book : public Publication
    {
        char *m_author{};
        char type() const;

    public:
        Book() : Publication(){};
        virtual ~Book();

        Book &operator=(const Book &other);
        Book(const Book &other);

        istream &read(istream &is);
        ostream &write(ostream &os) const;

        void set(int Member_id);
        operator bool() const;
    };
}
#endif // !SDDS_BOOK_H
