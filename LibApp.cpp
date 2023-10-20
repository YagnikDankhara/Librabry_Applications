
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

#include "LibApp.h"

using namespace std;
namespace sdds
{
	bool LibApp::confirm(const char *message)
	{
		Menu temp(message);
		temp << "Yes";
		int selection = temp.run();
		return (selection == 1);
	}

	bool Search(Publication &pub, int mode, char type)
	{
		switch (mode)
		{
		case 1:
			return (pub.type() == type);
		case 2:
			return (pub.type() == type && pub.onLoan());
		default:
			return (pub.type() == type && !pub.onLoan());
		}
	}

	void LibApp::save()
	{
		cout << "Saving Data" << endl;
		ofstream overwrite(m_fileName);
		for (int i = 0; i < m_NOLP; i++)
		{
			if (m_PPA[i]->getRef())
			{
				overwrite << *m_PPA[i] << endl;
			}
		}
	}

	int LibApp::search(int M)
	{
		int i, ref = 0;
		char type{};
		char title[256];
		PublicationSelector pubSel("Select one of the following found matches:");
		int selection = m_selectingMenu->run();
		if (selection == 1)
			type = 'B';
		else if (selection == 2)
			type = 'P';
		if (selection)
		{
			cout << "Publication Title: ";
			cin.getline(title, 256);
			for (i = 0; i < m_NOLP; i++)
			{
				if (m_PPA[i]->getRef() && Search(*m_PPA[i], M, type) && strstr(*m_PPA[i], title))
					pubSel << *m_PPA[i];
			}
			if (pubSel)
			{
				pubSel.sort();
				ref = pubSel.run();
				if (!ref)
				{
					cout << "Aborted!" << endl;
				}
			}
			else
			{
				cout << "No matches found!" << endl;
			}
		}
		else
		{
			cout << "Aborted!" << endl;
		}
		return ref;
	}

	Publication *LibApp::getPub(int libRef)
	{
		int i;
		Publication *p{};
		for (i = 0; i < m_NOLP; i++)
		{
			if (m_PPA[i]->getRef() == libRef)
			{
				p = m_PPA[i];
				i = m_NOLP;
			}
		}
		return p;
	}

	void LibApp::newPublication()
	{
		Publication *temp{};
		if (m_NOLP >= SDDS_LIBRARY_CAPACITY)
		{
			cout << "Library is at its maximum capacity!";
			cout << endl;
		}
		else
		{
			cout << "Adding new publication to the library" << endl;
			int selection = m_selectingMenu->run();
			if (selection == 0)
			{
				cout << "Aborted!" << endl;
			}
			else
			{
				if (selection == 1)
				{
					temp = new Book;
				}
				else if (selection == 2)
				{
					temp = new Publication;
				}
				cin >> *temp;
				if (!cin)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Aborted!";
				}
				else
				{
					bool istrue = confirm("Add this publication to the library?");
					if (!istrue)
					{
						cout << "Aborted!";
					}
					else
					{
						if (temp)
						{
							temp->setRef(++m_LLRN);
							m_PPA[m_NOLP] = temp;
							m_NOLP++;
							m_changed = true;
							cout << "Publication added" << endl;
						}
						else
						{
							cout << "Failed to add publication!";
							delete temp;
						}
					}
				}
			}
		}
	}

	void LibApp::removePublication()
	{
		int ref;
		cout << "Removing publication from the library" << endl;
		ref = search(1);
		if (ref)
		{
			cout << *getPub(ref) << endl;
			bool istrue = confirm("Remove this publication from the library?");
			if (istrue)
			{
				getPub(ref)->setRef(0);
				m_changed = true;
				cout << "Publication removed" << endl;
			}
		}
	}

	void LibApp::load()
	{
		ifstream inFile(m_fileName);
		char type{};
		int i = 0;
		cout << "Loading Data" << endl;
		while (i < SDDS_LIBRARY_CAPACITY && inFile)
		{
			inFile >> type;
			inFile.ignore();
			if (inFile)
			{
				if (type == 'P')
				{
					m_PPA[i] = new Publication;
				}
				else if (type == 'B')
				{
					m_PPA[i] = new Book;
				}
				inFile >> *m_PPA[i];
				m_NOLP++;
				i++;
			}
		}
		if (m_NOLP > 0)
		{
			m_LLRN = m_PPA[m_NOLP - 1]->getRef();
		}
	}

	void LibApp::checkOutPub()
	{
		int ref, memberID = 0;
		cout << "Checkout publication from the library" << endl;
		ref = search(3);
		if (ref)
		{
			cout << *getPub(ref) << endl;
			bool istrue = confirm("Check out publication?");
			if (istrue)
			{
				cout << "Enter Membership number: ";
				cin >> memberID;
				while (memberID < 10000 || memberID > 99999)
				{
					cout << "Invalid membership number, try again: ";
					cin >> memberID;
				}
				getPub(ref)->set(memberID);
				m_changed = true;
				cout << "Publication checked out" << endl;
			}
		}
	}

	LibApp::LibApp(const char *filename)
	{
		m_mainMenu = new Menu("Seneca Library Application");
		// *m_exitMenu << "Save changes and exit"
		// 			<< "Cancel and go back to the main menu";

		*m_mainMenu << "Add New Publication"
					<< "Remove Publication"
					<< "Checkout publication from library"
					<< "Return publication to library";

		m_exitMenu = new Menu("Changes have been made to the data, what would you like to do?");

		*m_exitMenu << "Save changes and exit"
					<< "Cancel and go back to the main menu";

		// m_mainMenu = new Menu("Seneca Library Application");
		m_selectingMenu = new Menu("Choose the type of publication:");

		*m_selectingMenu << "Book"
						 << "Publication";

		strncpy(m_fileName, filename, strlen(filename));
		m_fileName[strlen(filename)] = '\0';
		load();
	}

	void LibApp::run()
	{
		int flag = 1;
		while (flag)
		{
			int temp = m_mainMenu->run();

			if (temp == 1)
			{
				newPublication();
			}
			else if (temp == 2)
			{
				removePublication();
			}
			else if (temp == 3)
			{
				checkOutPub();
			}
			else if (temp == 4)
			{
				returnPub();
			}
			else
			{
				if (!m_changed)
					flag = 0;
				else
				{
					int value = m_exitMenu->run();
					if (value == 1)
					{
						save();
						flag = 0;
					}
					if (value == 0)
					{
						int temp1 = confirm("This will discard all the changes are you sure?");
						if (temp1)
						{
							flag = 0;
						}
					}
				}
			}
			cout << endl;
		}
		cout << "-------------------------------------------" << endl;
		cout << "Thanks for using Seneca Library Application" << endl;
	}
	void LibApp::returnPub()
	{
		Date currentDay;

		int Ref, latedays;

		cout << "Return publication to the library" << endl;
		Ref = search(2);
		if (Ref)
		{
			cout << *getPub(Ref) << endl;
			bool istrue = confirm("Return Publication?");
			if (istrue)
			{
				double temppen = 0.0;
				latedays = currentDay - getPub(Ref)->checkoutDate();
				if (latedays > SDDS_MAX_LOAN_DAYS)
				{
					temppen = (double(latedays) - SDDS_MAX_LOAN_DAYS) * 0.5;
					// cout << latedays - SDDS_MAX_LOAN_DAYS << " days late!" << endl;
					cout << "Please pay $" << fixed << setprecision(2);

					cout << temppen << " penalty for being ";
					// cout << "Please pay $" << fixed << setprecision(10);
					cout << latedays - SDDS_MAX_LOAN_DAYS << " days late!" << endl;
				}
				getPub(Ref)->set(0);
				m_changed = true;
				cout << "Publication returned" << endl;
			}
		}
	}

	LibApp::~LibApp()
	{
		delete m_mainMenu;
		delete m_exitMenu;
		delete m_selectingMenu;
		int i;
		for (i = 0; i < m_NOLP; i++)
			delete m_PPA[i];
	}
}
