/*************************************************
* ADS Praktikum 2.1
* Ring.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring .h
#pragma once
#include<string>
#include "catch.hpp"
#include"RingNode.h"

class Ring{
	
	private:
		int AnzahlNodes;
		RingNode* anker;
		// Hilfsmethode f�r rekursives Drucken
		void printNode(RingNode* ptr);
	public:
		Ring();
		void addNode(std::string descr, std::string data);
		bool search(std::string data);
		void print();

		////////////////////////////////////
		// friend Funktionen m�ssen unangetastet bleiben! 
		friend RingNode * get_anker(Ring& r);
		friend int get_AnzahlNodes(Ring& r);
};
