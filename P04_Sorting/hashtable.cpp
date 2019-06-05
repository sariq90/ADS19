#include "hashtable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int size) : size{ size }, collisionCount{ 0 }, elements{ 0 }
{
	hashTable = new vector<int>(size, -1);
}

HashTable::~HashTable()
{
	delete hashTable;
}

int HashTable::hashValue(int item)
{
	int index = -1; //dummy initializtation

	index = item % size;

	for (int i = 1; hashTable->at(index) != -1; ++i)
	{
		index = (item + i * i) % size;
		++collisionCount;
	}

	return index;
}

int HashTable::insert(int item)
{
	hashTable->at(hashValue(item)) = item;
	++elements;
	return 0; //dummy return
}


int HashTable::at(int i) {
	return hashTable->at(i);
}

int HashTable::getCollisionCount() {
	return this->collisionCount;
}

int HashTable::getSize() {
	return this->size;
}

int HashTable::getElements() {
	return this->elements;
}
