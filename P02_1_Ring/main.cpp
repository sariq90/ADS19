/*************************************************
* ADS Praktikum 2.1
* main.cpp
* 
*************************************************/
#define CATCH_CONFIG_RUNNER

#include <iostream>
#include <string>
#include "Ring.h"
#include "catch.hpp"

using namespace std;


int main()
{
	int result = Catch::Session().run();
	// Ihr Code hier:

	Ring* ring = new Ring;
	while (true)
	{
		int inp = -1;
		string inps;
		cout << "Ringworld engaged.\n"
			<< "================================================================\n"
			<< "1) Insert back-up\n2) Search for back-up\n3) Print back-ups\n0) Quit\n?>";
		do
		{
			getline(cin, inps);
			try
			{
				inp = stoi(inps);
			}
			catch (invalid_argument)
			{ }
		} while (inp != 0 && inp !=1 && inp !=2 && inp != 3);

		if (inp == 0)
			break;
		else if (inp == 1)
		{
			string descr;
			string data;
			cout << "Description?>\n";
			getline(cin, descr);
			cout << "Data?>\n";
			getline(cin, data);
			ring->addNode(descr, data);
		}
		else if (inp == 2)
		{
			string searchstring;
			cout << "Search-string?>\n";
			getline(cin, searchstring);
			ring->search(searchstring);
		}
		else
		{
			ring->print();
		}
	}

	//
	///////////////////////////////////////
	system("Pause");
	return 0;
}
