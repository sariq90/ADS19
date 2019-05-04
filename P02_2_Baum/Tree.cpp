/*************************************************
* ADS Praktikum 2.2
* Tree.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iostream>
#include <iomanip>

using namespace std;

Tree::Tree() : anker{ nullptr }, NodeIDCounter{ 0 } {}

// Berechnung ndpos = alter+eink+plz
void Tree::addNode(string name, int alter, double eink, int plz)
{
	int ndpos = alter + eink + plz;
	TreeNode* newnode = new TreeNode(ndpos, NodeIDCounter, name, alter, eink, plz);
	++NodeIDCounter;

	if (!anker)
	{	//Erster Node bei leerem Baum
		anker = newnode;
		return;
	}
	TreeNode* tmp = anker;
	while (true)
	{
		if (ndpos < tmp->getNodePosID())
		{	//NodePosID < Vergleichswert
			if (!tmp->getLeft())
			{	//Ablegen wenn leer
				tmp->setLeft(newnode);
				return;
			}
			else
			{	//Weiter wenn belegt
				tmp = tmp->getLeft();
			}
		}
		else
		{	//NodePosID >= Vergleichswert
			if (!tmp->getRight())
			{	//Ablegen wenn leer
				tmp->setRight(newnode);
				return;
			}
			else
			{	//Weiter wenn belegt
				tmp = tmp->getRight();
			}
		}
	}
}

void Tree::deleteNode(int ndpos)
{	// Lösche und besetze mit Minimum aus RTB
	if (!anker)
	{
		cout << "+ Leerer Baum.\n";
		return;
	}
	TreeNode* del = anker;
	TreeNode* par = nullptr;
	while (del->getNodePosID() != ndpos)
	{	// Suche anhand der NodePosID nach Knoten
		par = del;
		if (ndpos < del->getNodePosID())
			del = del->getLeft();
		else if (ndpos > del->getNodePosID())
			del = del->getRight();
		if (!del)
		{	// Falls Blatt erreicht und != ndpos
			cout << "+ Eintrag nicht gefunden.\n";
			return;
		}
	}
	TreeNode* min = del;
	TreeNode* minpar = del;
	if (del == anker)
	{	// Wurzelknoten
		if (!del->getLeft() && !del->getRight())
		{	// Nur ein Knoten im Baum
			anker = nullptr;
		}
		else if (del->getRight())
		{	// RTB existisert
			min = del->getRight();
			while (min->getLeft())
			{	// finde Minimum im RTB
				minpar = min;
				min = min->getLeft();
			}
			if (minpar != del)
			{	// Klebe Min-Rest an Par wenn vorhanden
				if (min->getRight())
					minpar->setLeft(min->getRight());
				else
					minpar->setLeft(nullptr);
				// RTB und LTB von del an min
				min->setLeft(del->getLeft());
				min->setRight(del->getRight());
			}
			if (minpar == del)
				min->setLeft(del->getLeft());
			anker = min;
		}
		else
		{	// nur LTB an Wurzel existiert
			anker = del->getLeft();
		}
	}
	else if (del->getLeft() && del->getRight())
	{	// beide Nachfolger (RTB,LTB existieren)
		min = del->getRight();
		while (min->getLeft())
		{	// finde Minimum im RTB
			minpar = min;
			min = min->getLeft();
		}
		if (minpar != del)
		{	// Klebe Min-Rest an Par wenn vorhanden
			if (min->getRight())
				minpar->setLeft(min->getRight());
			else
				minpar->setLeft(nullptr);
			// RTB und LTB von del an min
			min->setLeft(del->getLeft());
			min->setRight(del->getRight());
			// Setze par von del auf min
		}
		if (par->getLeft() == del)
			par->setLeft(min);
		else
			par->setRight(min);
		if (minpar == del)
			min->setLeft(del->getLeft());
	}
	else if (del->getLeft())
	{	// nur linker Nachfolger
		if (par->getLeft() == del)
			par->setLeft(del->getLeft());
		else
			par->setRight(del->getLeft());
	}
	else if (del->getRight())
	{	// nur rechter Nachfolger
		if (par->getLeft() == del)
			par->setLeft(del->getRight());
		else
			par->setRight(del->getRight());
	}
	else
	{	// Blattknoten
		if (par->getLeft() == del)
			par->setLeft(nullptr);
		else
			par->setRight(nullptr);
	}
	delete del;
	cout << "+ Eintrag geloescht.\n";
}

bool Tree::searchNode(string name)
{
	if (!anker)
	{
		cout << "+ Leerer Baum.\n";
		return false;
	}
	else
	{
		int count = 0;
		searchPreorder(name, anker, count);
		if (count == 0)
		{
			cout << "+ Kein Vorkommen von '" << name << "'.\n";
			return false;
		}
		else
		{
			cout << "+ Insgesamt " << count << " Eintraege mit '" << name << "' gefunden.\n";
			return true;
		}
	}
}

void Tree::searchPreorder(string name, TreeNode* ptr, int &count)
{
	if (ptr->getName() == name)
	{
		ptr->print();
		++count;
	}
	if (ptr->getLeft())
		searchPreorder(name, ptr->getLeft(), count);
	if (ptr->getRight())
		searchPreorder(name, ptr->getRight(), count);
}

void Tree::printAll()
{
	if (!anker)
	{
		cout << "+ Leerer Baum.\n";
		return;
	}
	cout << "ID |    Name    | Alter | Einkommen |  PLZ  | Pos  " << endl
		<< "---+------------+-------+-----------+-------+------" << endl;

	printPreorder(anker);

	cout << "---+------------+-------+-----------+-------+------" << endl;
}

void Tree::printPreorder(TreeNode* ptr)
{
	cout << setw(3) << right << ptr->getNodeID() << "|" << setw(12) << ptr->getName() << "|" << setw(7) << ptr->getAlter()
		<< "|" << setw(11) << ptr->getEinkommen() << "|" << setw(7) << ptr->getPLZ() << "|" << left << ptr->getNodePosID() << endl;
	if (ptr->getLeft())
		printPreorder(ptr->getLeft());
	if (ptr->getRight())
		printPreorder(ptr->getRight());
}