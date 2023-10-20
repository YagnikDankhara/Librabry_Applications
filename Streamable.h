/*//////////////////////////////////////////////////////////////////////////
							MS- 5
Full Name  :   Preet Chakrani
Student ID#:   113115224
Email      :   pchakrani@myseneca.ca
Section    :   NGG

Authenticity Declaration:

I declare ubmission is the result of my own work and has not been
shared with any other student or 3rd party content provider. sbmitted
piece of work is entirely of my own creation.
//////////////////////////////////////////////////////////////////////////*/
#ifndef SDDS_STREAMABLE_H
#define SDDS_STREAMABLE_H
#include <iostream>

namespace sdds
{
	class Streamable
	{
	public:
		virtual std::ostream &write(std::ostream &os) const = 0;
		virtual std::istream &read(std::istream &is) = 0;
		virtual bool conIO(std::ios &io) const = 0;
		virtual operator bool() const = 0;
		virtual ~Streamable(){};
	};
	std::ostream &operator<<(std::ostream &os, const Streamable &ro);
	std::istream &operator>>(std::istream &is, Streamable &ro);

}
#endif // !SDDS_STREAMABLE_H
