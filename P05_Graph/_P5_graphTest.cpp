/*************************************************
* ADS Praktikum 2.1
* Unit-Testdatei
* Stand: 05.03.2019
*
*************************************************
* �nderungen untersagt!
*************************************************/
#include "catch.h"
#include "Graph.h"
#include "GraphNode.h"
#include <string>
#include <iostream>

using namespace std;

// Friend-Methode fuer Testroutine
/*TreeNode * get_anker(Tree& Tr) {
	return Tr.anker;
}*/

/***********************************************
 * Testroutine des Graphen:
	- Tiefensuche mit zusammenh�ngenden Graphen
	- Tiefensuche mit nicht zusammenh�ngenden Graphen
	- Breitensuche mit zusammenh�ngenden Graphen
	- Breitensuche mit nicht zusammenh�ngenden Graphen
	- Prim mit bestimmten Ergebnissen
	- Kruskal mit bestimmten Ergebnissen
 */
TEST_CASE("Graph Testing", "[Graph]" ) {
	
	Graph* test1 = new Graph();
	Graph* test2 = new Graph();
	Graph* test3 = new Graph();

	test1->init("graph1.txt");
	test2->init("graph2.txt");
	test3->init("graph3.txt");
	
	SECTION("Tiefensuche mit erstem Graphen") {
		
		for (int i = 0; i < test1->getAnzKnoten(); i++) {
			bool test = test1->depthSearchRek(i);

			REQUIRE(test == true);
		}
	}

	SECTION("Tiefensuche mit zweitem Graphen") {

		for (int i = 0; i < test2->getAnzKnoten(); i++) {
			bool test = test2->depthSearchRek(i);

			REQUIRE(test == true);
		}
	}

	SECTION("Tiefensuche mit drittem Graphen") {

		for (int i = 0; i < test3->getAnzKnoten(); i++) {
			bool test = test3->depthSearchRek(i);

			REQUIRE(test == false);
		}
	}

	SECTION("Prim mit erstem Graph") {
		for (int i = 0; i < test1->getAnzKnoten(); i++) {
			int value = test1->prim(0);

			REQUIRE(value == 39);
		}
	}

	SECTION("Prim mit zweitem Graph") {
		for (int i = 0; i < test2->getAnzKnoten(); i++) {
			int value = test2->prim(0);

			REQUIRE(value == 150);
		}
	}

	SECTION("Kruskal mit erstem Graph") {
		for (int i = 0; i < test1->getAnzKnoten(); i++) {
			int value = test1->kruskal();

			REQUIRE(value == 39);
		}
	}
	
	SECTION("Kruskal mit zweitem Graph") {
		for (int i = 0; i < test2->getAnzKnoten(); i++) {
			int value = test2->kruskal();

			REQUIRE(value == 150);
		}
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// http://www.hashemall.com/
// Zeile 1-291 hat den SHA 256 Hashwert: 131B33B1910C8097CB5E431FF1058E1388580D875B14BAEF47DC4E44ED43A576
