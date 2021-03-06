/*************************************************
* ADS Praktikum 2.2
* TreeNode.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <iomanip>

TreeNode::TreeNode(int ndpos, int ndid, string name, int alter, double eink, int plz) :
	NodePosID{ ndpos }, NodeID{ ndid }, Name{ name }, Alter{ alter },
	Einkommen{ eink }, PLZ{ plz }, left{ nullptr }, right{ nullptr },
	parent{ nullptr }, red{ true } {}

int TreeNode::getNodePosID() { return NodePosID; }
int TreeNode::getNodeID() { return NodeID; }
string TreeNode::getName() { return Name; }
void TreeNode::setName(string name) { Name = name; }
int TreeNode::getAlter() { return Alter; }
void TreeNode::setAlter(int alter) { Alter = alter; }
double TreeNode::getEinkommen() { return Einkommen; }
void TreeNode::setEinkommen(double eink) { Einkommen = eink; }
int TreeNode::getPLZ() { return PLZ; }
void TreeNode::setPLZ(int plz) { PLZ = plz; }

TreeNode* TreeNode::getLeft() { return left; }
TreeNode* TreeNode::getRight() { return right; }
void TreeNode::setLeft(TreeNode* node) { left = node; }
void TreeNode::setRight(TreeNode* node) { right = node; }

void TreeNode::print()
{
	std::cout << std::setw(3) << std::right << getNodeID() << "|" << std::setw(12) << getName() << "|" << std::setw(7) << getAlter()
		<< "|" << std::setw(11) << getEinkommen() << "|" << std::setw(7) << getPLZ() << "|" << std::left << getNodePosID() << std::endl;
}

TreeNode* TreeNode::getParent() { return parent; }
void TreeNode::setParent(TreeNode* node) { parent = node; }
bool TreeNode::getRed() { return red; }
void TreeNode::setRed(bool r) { red = r; }