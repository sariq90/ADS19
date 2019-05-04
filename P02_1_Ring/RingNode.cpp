/*************************************************
* ADS Praktikum 2.1
* RingNode.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "RingNode.h"



RingNode::RingNode() : OldAge{ 0 }, next{ nullptr } {}

RingNode::RingNode(int age, std::string descr, std::string data) : OldAge{ age },
Description{ descr }, SymbolicData{ data }, next{ nullptr } {}

int RingNode::getAge(){	return OldAge; }

void RingNode::setAge(int age){	OldAge = age; }

std::string RingNode::getDescription() { return Description; }

void RingNode::setDescription(std::string descr) { Description = descr; }

std::string RingNode::getData() { return SymbolicData; }

void RingNode::setData(std::string data) { SymbolicData = data; }

RingNode* RingNode::getNext() { return next; }

void RingNode::setNext(RingNode* n) { next = n; }
