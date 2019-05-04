/*************************************************
* ADS Praktikum 2.1
* Unit-Testdatei
*
* �nderungen f�rs Praktikum untersagt!
*************************************************/
#include "catch.hpp"
#include "Ring.h"
#include "RingNode.h"
#include <string>

using namespace std;

// Friend-Methode fuer Testroutine
RingNode * get_anker(Ring& r) {
	return r.anker;
}

int get_AnzahlNodes(Ring& r) {
	return r.AnzahlNodes;
}

TEST_CASE("Ring Testing", "[Ring]" ) {
	
	Ring rloop;	
	
	SECTION("Hinzufuegen von Nodes und Suche - simple"){
	
		rloop.addNode("Alpha","Data");	
		rloop.addNode("Beta","Data");
		rloop.addNode("Gamma","Data");

		REQUIRE(get_AnzahlNodes(rloop) == 3);
		
		REQUIRE (rloop.search("Data") == true);
		REQUIRE (rloop.search("FAIL") == false);	
		REQUIRE (rloop.search("Alpha") == false);	
		REQUIRE (rloop.search("Data") == true);
	}
	
	SECTION("Hinzufuegen von Nodes - Rotaionsgrenze"){
		rloop.addNode("Alpha","Data1");	
		rloop.addNode("Beta","Data2");
		rloop.addNode("Gamma","Data3");
		rloop.addNode("Delta","Data4");	
		rloop.addNode("Phi","Data5");
		rloop.addNode("Sept","Data6");
		rloop.addNode("Gamma","Data7");
		rloop.addNode("Gamma","Data8");
		rloop.addNode("Gamma","Data9");

		REQUIRE(get_AnzahlNodes(rloop) == 6);
		
		REQUIRE (rloop.search("Data1")== false);	
		REQUIRE (rloop.search("Data2")== false);	
		REQUIRE (rloop.search("Data7")== true);	
		REQUIRE (rloop.search("Data5")== true);	
	} 
	
	SECTION("Hinzufuegen von Nodes - Rotaionsperformance"){

		for (int i = 0; i < 1024; i++ )
		{			
			string info = "Info"+to_string(i);
			string data = "Data"+to_string(i);
			rloop.addNode(info,data);	
		}

		REQUIRE(get_AnzahlNodes(rloop) == 6);
	
		REQUIRE (rloop.search("Data1")== false);	
		REQUIRE (rloop.search("Data2")== false);	
		REQUIRE (rloop.search("Data1020")== true);	
		REQUIRE (rloop.search("Data1023")== true);	
	} 
	
	SECTION("Ringarchitektur - Verkettungspruefung 1") {

		for (int i = 0; i < 3; i++)
		{
			string info = "Info" + to_string(i);
			string data = "Data" + to_string(i);
			rloop.addNode(info, data);
		}

		RingNode * ref = get_anker(rloop);
		REQUIRE(get_AnzahlNodes(rloop) == 3);
		REQUIRE(ref->getData() == "Data2");
		ref = ref->getNext();
		REQUIRE(ref->getData() == "Data0");
		ref = ref->getNext();
		REQUIRE(ref->getData() == "Data1");		
		ref = ref->getNext();
		REQUIRE(ref == get_anker(rloop));		
	}
	SECTION("Ringarchitektur - Verkettungspruefung 2"){
	
		for (int i = 0; i < 10; i++ )
		{			
			string info = "Info"+to_string(i);
			string data = "Data"+to_string(i);
			rloop.addNode(info,data);	
		}
		
		RingNode * ref = get_anker(rloop);
		REQUIRE(get_AnzahlNodes(rloop) == 6);		
		REQUIRE(ref->getData() == "Data9");
		ref = ref->getNext();
		REQUIRE(ref->getData() == "Data4");
		ref = ref->getNext();
		REQUIRE(ref->getData() == "Data5");
		ref = ref->getNext();
		REQUIRE(ref->getData() == "Data6");
		ref = ref->getNext();
		REQUIRE(ref->getData() == "Data7");
		ref = ref->getNext();
		REQUIRE(ref->getData() == "Data8");
		ref = ref->getNext();
		REQUIRE(ref->getData() == "Data9");
		REQUIRE(ref == get_anker(rloop));

		//Fail-Test:		
		//REQUIRE(get_anker(rloop)->getData() == "Data4");	
	} 	
}

TEST_CASE("RingNode Testing", "[RingNode]" ) {
		
	SECTION("Get/Setter von RingNode - simple"){
	
		RingNode * node = new RingNode(1,"Info","Data");
		REQUIRE(node->getAge() == 1);
		REQUIRE(node->getDescription() =="Info");
		REQUIRE(node->getData() == "Data");
		REQUIRE(node->getNext() == nullptr);
		
		node->setAge(5);
		REQUIRE(node->getAge() == 5);
		
		node->setDescription("newInfo");
		REQUIRE(node->getDescription() == "newInfo");

		node->setData("newData");
		REQUIRE(node->getData() == "newData");

		RingNode * node2 = new RingNode(2, "Info2", "Data2");
		node->setNext(node2);
		REQUIRE(node->getNext() == node2);

		delete node;
		delete node2;
	}	
}
