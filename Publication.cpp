
#include <cstring>

#include "Publication.h"
#include "Utils.h"
#include "Lib.h"
using namespace std;

namespace sdds
{
	Publication::~Publication()
	{
		delete[] m_title;
		m_title = nullptr;
	}
	Publication::operator bool() const
	{
		if (m_shelfId != nullptr && m_shelfId[0] != '\0')
			return true;
		return false;
	}
	bool Publication::conIO(ios &io) const
	{
		if (&io == &cin || &io == &cout)
			return true;
		return false;
	}

	std::ostream &Publication::write(std::ostream &os) const
	{
		if (conIO(os) && *this)
		{
			os << "| ";
			os.width(SDDS_SHELF_ID_LEN);
			os << m_shelfId << " | ";

			if (m_title)
			{
				if (strlen(m_title) > SDDS_TITLE_WIDTH)
				{
					os.write(m_title, SDDS_TITLE_WIDTH);
				}
				else
				{
					os.width(SDDS_TITLE_WIDTH);
					os.fill('.');
					os.setf(std::ios::left);
					os << m_title;
					os.unsetf(std::ios::left);
				}
			}
			os << " | ";
			if (onLoan())
				os << m_membership;
			else
				os << " N/A ";
			os << " | " << checkoutDate() << " |";
		}
		else if (*this)
		{
			os << type() << "\t" << getRef() << '\t';
			os << m_shelfId << '\t' << m_title << '\t';
			os << m_membership << '\t' << m_date;
		}
		return os;
	}
	std::istream &Publication::read(std::istream &is)
	{
		char title[256] = "";
		Publication temp;
		*this = temp;
		if (conIO(is))
		{
			std::cout << "Shelf No: ";
			is.getline(temp.m_shelfId, SDDS_SHELF_ID_LEN + 1);
			if (strlen(temp.m_shelfId) != 4)
				is.setstate(is.failbit);
			std::cout << "Title: ";
			is.getline(title, 256);
			std::cout << "Date: ";
			is >> temp.m_date;
		}
		else
		{
			is >> temp.m_libRef;
			is.ignore();
			is >> temp.m_shelfId;
			is.ignore();
			is.getline(title, 256, '\t');
			is >> temp.m_membership;
			is.ignore();
			is >> temp.m_date;
		}
		if (!temp.m_date)
			is.setstate(is.failbit);
		if (!is.fail())
		{
			m_title = new char[strlen(title) + 1];
			strcpy(m_title, title);
			strcpy(m_shelfId, temp.m_shelfId);
			set(temp.m_membership);
			m_date = temp.m_date;
			setRef(temp.m_libRef);
		}
		return is;
	}
	void Publication::set(int member_id)
	{
		m_membership = member_id;
	}
	void Publication::setRef(int value)
	{
		m_libRef = value;
	}
	void Publication::resetDate()
	{
		this->m_date = Date();
	}
	char Publication::type() const
	{
		return 'P';
	}
	bool Publication::onLoan() const
	{
		return (m_membership != 0);
	}
	Date Publication::checkoutDate() const
	{
		return this->m_date;
	}
	bool Publication::operator==(const char *title) const
	{
		if (strstr(m_title, title) != nullptr)
			return true;
		return false;
	}
	Publication::operator const char *() const
	{
		return static_cast<const char *>(m_title);
	}
	int Publication::getRef() const
	{
		return m_libRef;
	}
	Publication &Publication::operator=(const Publication &other)
	{
		if (this != &other)
		{
			m_membership = other.m_membership;
			m_libRef = other.m_libRef;
			strcpy(m_shelfId, other.m_shelfId);
			this->m_date = other.m_date;
			delete[] m_title;
			if (other.m_title != nullptr)
			{
				m_title = new char[strlen(other.m_title) + 1];
				strcpy(m_title, other.m_title);
			}
			else
				m_title = nullptr;
		}
		return *this;
	}
	Publication::Publication(const Publication &other)
	{
		*this = other;
	}
}
