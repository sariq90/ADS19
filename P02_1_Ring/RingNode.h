/*************************************************
* ADS Praktikum 2.1
* RingNode.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#pragma once
#include <string>

class RingNode{
	
private:

	int OldAge = 0;
	std::string Description;
	std::string SymbolicData;
	RingNode* next;

public:

	RingNode();
	RingNode(int age, std::string descr, std::string data);
	int getAge();
	void setAge(int age);
	std::string getDescription();
	void setDescription(std::string descr);
	std::string getData();
	void setData(std::string data);
	RingNode* getNext();
	void setNext(RingNode* n);


};
