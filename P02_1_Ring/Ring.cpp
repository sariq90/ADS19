/*************************************************
* ADS Praktikum 2.1
* Ring.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring .cpp
#include "Ring.h"
#include <iostream>

// Ihr Code hier:


Ring::Ring() : AnzahlNodes{ 0 }, anker{ nullptr } {}

void Ring::addNode(std::string descr, std::string data)
{
	RingNode* newnode = new RingNode(0, descr, data);
	++AnzahlNodes;
	if (AnzahlNodes == 1)
	{	// Erster Node
		anker = newnode;
		newnode->setNext(anker);
	}
	else
	{	// Alle weiteren Nodes
		newnode->setNext(anker->getNext());
		RingNode* tmp = anker;
		do
		{	// Aktualisiere OldAge
			tmp->setAge(tmp->getAge() + 1);
			if (tmp->getAge() == 6)
			{	// Falls TTL überschritten, lösche Node
				newnode->setNext(tmp->getNext());
				delete tmp;
				--AnzahlNodes;
				tmp = newnode;
			}
			tmp = tmp->getNext();
		} while (tmp != anker);
		anker->setNext(newnode);
		anker = newnode;
	}
}

bool Ring::search(std::string data)
{
	if (AnzahlNodes == 0)
		return false;
	RingNode* tmp = anker;
	do
	{
		if (tmp->getData() == data)
		{
			std::cout << "Back-up found:\n" << "OldAge: " << tmp->getAge()
				<< ", Description: " << tmp->getDescription()
				<< ", Data: " << tmp->getData() << std::endl <<std::endl;
			return true;
		}
		tmp = tmp->getNext();
	} while (tmp != anker);
	std::cout << "Back-up not found.\n\n";
	return false;
}

void Ring::print()
{
	if (AnzahlNodes == 0)
		return;
	RingNode* tmp = anker;
	printNode(tmp->getNext());
}

void Ring::printNode(RingNode* ptr)
{
	if (ptr != anker)
	{	
		printNode(ptr->getNext());
	}
	std::cout << "OldAge: " << ptr->getAge()
		<< ", Description: " << ptr->getDescription()
		<< ", Data: " << ptr->getData() << std::endl
		<< "----------------------------------------------------------------"
		<< std::endl;
}


//
////////////////////////////////////
