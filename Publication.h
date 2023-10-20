
#ifndef SDDS_PUBLICATION_H
#define SDDS_PUBLICATION_H
#include "Streamable.h"
#include "Date.h"

namespace sdds
{
	class Publication : public Streamable
	{
		char *m_title{nullptr};
		char m_shelfId[5]{};
		int m_membership{0};
		int m_libRef{-1};
		Date m_date{};
		// Returns the character 'P' to identify this object as a "Publication object"

	public:
		virtual char type() const;
		Publication(){};
		virtual ~Publication();
		operator bool() const;
		bool conIO(std::ios &io) const;
		std::ostream &write(std::ostream &os) const;
		std::istream &read(std::istream &is);
		virtual void set(int member_id);
		// Sets the membership attribute to either zero or a five-digit integer.
		void setRef(int value);
		// Sets the **libRef** attribute value
		void resetDate();
		// Sets the date to the current date of the system.

		bool onLoan() const;
		// Returns true is the publication is checkout (membership is non-zero)
		Date checkoutDate() const;
		// Returns the date attribute
		bool operator==(const char *title) const;
		// Returns true if the argument title appears anywhere in the title of the
		// publication. Otherwise, it returns false; (use strstr() function in <cstring>)
		operator const char *() const;
		// Returns the title attribute
		int getRef() const;
		// Returns the libRef attirbute.
		Publication &operator=(const Publication &other);
		Publication(const Publication &other);
	};
}
#endif // !SDDS_PUBLICATION_H
