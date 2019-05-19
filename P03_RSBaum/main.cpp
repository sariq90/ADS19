/*************************************************
* ADS Praktikum 2.2
* main.cpp
*
*************************************************/
#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "Tree.h"
#include "catch.h"

using namespace std;

bool importfromcsv(Tree* tree)
{	//CSV-Import
	ifstream csvfile("ExportZielanalyse.csv", ios::in);
	if (csvfile) {
		string line;
		while (getline(csvfile, line))
		{
			istringstream iline(line);
			string word[4];
			for (int i = 0; i < 4; ++i)
			{
				getline(iline, word[i], ';');
			}
			tree->addNode(word[0], stoi(word[1]), stod(word[2]), stoi(word[3]));
		}
		csvfile.close();
		return true;
	}
	else
		return false;
}

int main() {

	int result = Catch::Session().run();

	std::cout << "==================================\n"
		<< "1) Datensatz einfuegen, manuell\n"
		<< "2) Datensatz einfuegen, CSV Datei\n"
		<< "3) Suchen\n"
		<< "4) Ausgabe in Levelorder\n"
		<< "5) Ausgabe in Preorder\n"
		<< "0) Beenden\n";
	string inp = "0";
	int in = 0;
	Tree* baum = new Tree();
	do
	{
		do
		{
			cout << "?> ";
			getline(cin, inp);
		} while (inp != "0" && inp != "1" && inp != "2" && inp != "3" && inp != "4" && inp != "5");
		in = stoi(inp);
		switch (in)
		{
		case 0:
			break;
		case 1:
		{
			string name, alter, eink, plz;
			try
			{
				cout << "+ Datensatz eingeben:\nName?> ";
				getline(cin, name);
				cout << "Alter?> ";
				getline(cin, alter);
				cout << "Einkommen?> ";
				getline(cin, eink);
				cout << "PLZ?> ";
				getline(cin, plz);
				baum->addNode(name, stoi(alter), stod(eink), stoi(plz));
				cout << "+ Datensatz hinzugefuegt.\n";
			}
			catch (invalid_argument)
			{
				cout << "+ Eingabe fehlerhaft.\n";
			}
			break;
		}
		case 2:
		{
			string sel;
			cout << "+ Datei 'ExportZielanalyse.csv' importieren (j/n)\n?> ";
			do
			{
				getline(cin, sel);
			} while (sel != "j" && sel != "n");

			if (sel == "j")
			{
				if (importfromcsv(baum))
					cout << "+ Daten hinzugefuegt.\n";
				else
					cout << "+ Fehler beim Import.\n";
			}
			break;
		}
		case 3:
		{
			string name;
			cout << "+ Bitte geben Sie den zu suchenden Namen ein:\n?> ";
			getline(cin, name);
			cout << "+ Fundstellen: \n";
			baum->searchNode(name);
			break;
		}
		case 4:
		{
			baum->printLevelOrder();
			break;
		}
		case 5:
		{
			baum->printAll();
			break;
		}
		}


	} while (in != 0);

	system("PAUSE");

	return 0;
}
