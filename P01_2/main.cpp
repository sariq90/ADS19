#include <iostream>
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "List.h"
using namespace std;

int main(void)
{
	int result = Catch::Session().run();
	int i;
	List<int> MyList;

	for (i = 0; i < 10; i++) {
		MyList.insertFront(i + 1);
		MyList.insertBack(i + 100);
	}

	cout << MyList;

	cout << "100: " << (MyList.search(100) ? "gefunden" : "nicht gefunden") << endl;
	cout << "99: " << (MyList.search(99) ? "gefunden" : "nicht gefunden") << endl << endl;

	while (MyList.getBack(i))
		cout << i << " ";
	cout << endl << endl;

	List<int> MyList1, MyList2, MyList3;
	List<int> * MyList_dyn = new List<int>;

	for (i = 0; i < 10; i++) {
		MyList1.insertFront(i + 1);
		MyList2.insertBack(i + 100);
	}

	MyList1.format("MyList1\n<<", ", ", ">>\n\n");
	cout << MyList1;

	MyList_dyn->format("MyList_dyn\n<<", ", ", ">>\n\n");
	MyList_dyn->insertFront(-111);
	cout << MyList_dyn;

	MyList2.format("MyList2\n<<", ", ", ">>\n\n");
	cout << MyList2;

	MyList3 = MyList1 + MyList_dyn + MyList2;

	delete MyList_dyn;

	cout << "Groesse von MyList3: " << MyList3.size() << endl << endl;

	MyList3.format("MyList3\n<<", ", ", ">>\n\n");
	cout << MyList3 << endl;

	MyList3.swap(8, 103);

	cout << MyList3;

	if (MyList3.test())
		cout << "MyList3: Zeiger OK\n\n";
	else
		cout << "MyList3: Zeiger ******Error\n\n";

	system("PAUSE");
	return 0;
}

TEST_CASE("Eigene", "")
{

	SECTION("Deskonstruktor-Test")
	{
		List<int>* TestList1 = new List<int>;
		Node<int>* NodeHT = get_anker(*TestList1);
		TestList1->insertFront(2);
		TestList1->insertFront(1);
		TestList1->insertBack(3);
		Node<int>* Node1 = NodeHT->next;
		Node<int>* Node2 = NodeHT->next->next;
		Node<int>* Node3 = NodeHT->prev;
		delete TestList1;
	}
	SECTION("Inserts")
	{
		List<int>* TestList1d = new List<int>;
		List<int>* TestList2d = new List<int>;
		List<int>* TestList3d = new List<int>;
		List<int> TestList4, TestList5;

		TestList1d->insertFront(1);
		TestList2d->insertFront(2);
		TestList2d->insertFront(3);
		TestList3d->insertBack(-1);
		TestList3d->insertBack(-2);
		TestList4.insertFront(4);
		TestList4.insertFront(5);
		TestList5.insertBack(-3);
		TestList5.insertBack(-4);
		//cout << TestList1d;
		//cout << TestList2d;
		//cout << TestList3d;
		//cout << TestList4;
		//cout << TestList5;
		TestList1d->insertFront(TestList2d);
		//cout << "1+2F: " << TestList1d << "2: " << TestList2d << endl;
		TestList1d->insertBack(TestList3d);
		//cout << "1+2F+3B: " << TestList1d << "3: " << TestList3d << endl;
		TestList1d->insertFront(TestList4);
		//cout << "1+2F+3B+4F: " << TestList1d << "4: " << TestList4 << endl;
		TestList1d->insertBack(TestList5);
		//cout << "1+2F+3B+4F+5B: " << TestList1d << "5: " << TestList5 << endl;
		Node<int>* tmp = get_anker(*TestList1d)->next;
		REQUIRE(tmp->key == 5);
		tmp = tmp->next;
		REQUIRE(tmp->key == 4);
		tmp = tmp->next;
		REQUIRE(tmp->key == 3);
		tmp = tmp->next;
		REQUIRE(tmp->key == 2);
		tmp = tmp->next;
		REQUIRE(tmp->key == 1);
		tmp = tmp->next;
		REQUIRE(tmp->key == -1);
		tmp = tmp->next;
		REQUIRE(tmp->key == -2);
		tmp = tmp->next;
		REQUIRE(tmp->key == -3);
		tmp = tmp->next;
		REQUIRE(tmp->key == -4);
	}
}