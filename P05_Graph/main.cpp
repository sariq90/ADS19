#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include "Graph.h"
#include <iostream>
using namespace std;

int main()
{
	int result = Catch::Session().run();

	std::cout << "==================================\n"
		<< "1) Graph einlesen\n"
		<< "2) Tiefensuche\n"
		<< "3) Breitensuche\n"
		<< "4) Prim\n"
		<< "5) Kruskal\n"
		<< "6) Print Graph\n"
		<< "0) Beenden\n";
	string inp = "0";
	int in = 0;
	Graph g;
	do
	{
		do
		{
			cout << "?> ";
			getline(cin, inp);
		} while (inp != "0" && inp != "1" && inp != "2" && inp != "3" && inp != "4" && inp != "5" && inp != "6");
		in = stoi(inp);
		switch (in)
		{
		case 0:
			break;
		case 1:
		{
			string textfile;
			try
			{
				cout << "+ Graph einlesen von\nPfad?> ";
				getline(cin, textfile);
				g.init(textfile);
			}
			catch (invalid_argument)
			{
				cout << "+ Eingabe fehlerhaft.\n";
			}
			break;
		}
		case 2:
		{
			string keyS;
			try
			{
				cout << "+ Start-Key fuer Tiefensuche\n?> ";
				getline(cin, keyS);
				int key = stoi(keyS);
				bool notPartial = g.depthSearchRek(key);
				if (notPartial)
					cout << "Graph ist vollstaendig verbunden.\n";
				else
					cout << "Graph besteht aus Teilgraphen.\n";
			}
			catch (invalid_argument)
			{
				cout << "+ Eingabe fehlerhaft.\n";
			}
			break;
		}
		case 3:
		{
			string keyS;
			try
			{
				cout << "+ Start-Key fuer Breitensuche\n?> ";
				getline(cin, keyS);
				int key = stoi(keyS);
				bool notPartial = g.breadthSearchIter(key);
				if (notPartial)
					cout << "Graph ist vollstaendig verbunden.\n";
				else
					cout << "Graph besteht aus Teilgraphen.\n";
			}
			catch (invalid_argument)
			{
				cout << "+ Eingabe fehlerhaft.\n";
			}
			break;
		}
		case 4:
		{
			string keyS;
			try
			{
				cout << "+ Start-Key fuer Prim\n?> ";
				getline(cin, keyS);
				int key = stoi(keyS);
				double result = g.prim(key);
				cout << "MST: " << result << endl;
			}
			catch (invalid_argument)
			{
				cout << "+ Eingabe fehlerhaft.\n";
			}
			break;
		}
		case 5:
		{
			double result = g.kruskal();
			cout << "MST: " << result << endl;
			break;
		}
		case 6:
		{
			g.printAll();
			break;
		}
		}


	} while (in != 0);
	system("pause");
	return 0;
}