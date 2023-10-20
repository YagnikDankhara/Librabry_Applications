

#include "Streamable.h"
using namespace std;

namespace sdds
{
    ostream &operator<<(ostream &os, const Streamable &S)
    {
        return S.write(os);
    }
    istream &operator>>(istream &is, Streamable &S)
    {
        return S.read(is);
    }
}
