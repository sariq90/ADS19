/*************************************************
* ADS Praktikum 2.2
* Tree.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

Tree::Tree() : anker{ nullptr }, NodeIDCounter{ 0 } {}


void Tree::addNode(string name, int alter, double eink, int plz)
{
	int ndpos = alter + eink + plz;
	TreeNode* newnode = new TreeNode(ndpos, NodeIDCounter, name, alter, eink, plz);
	++NodeIDCounter;

	if (!anker)	//Erster Node bei leerem Baum
	{
		newnode->setRed(false);
		anker = newnode;
	}
	else
	{
		TreeNode* pnode = nullptr;
		TreeNode* ptrnode = anker;
		while (ptrnode)
		{
			pnode = ptrnode;
			if (newnode->getNodePosID() < ptrnode->getNodePosID())
				ptrnode = ptrnode->getLeft();
			else
				ptrnode = ptrnode->getRight();

			// Umfärben wenn R~B~R zu B~R~B
			if (pnode->getLeft() && pnode->getRight() &&
				pnode->getLeft()->getRed() && pnode->getRight()->getRed())
			{
				if (pnode != anker)
					pnode->setRed(true);
				pnode->getLeft()->setRed(false);
				pnode->getRight()->setRed(false);
			}
		}
		//Einfügen
		newnode->setParent(pnode);
		if (newnode->getNodePosID() < pnode->getNodePosID())
			pnode->setLeft(newnode);
		else
			pnode->setRight(newnode);
	}
	balanceTree(newnode);
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
	ptr->print();
	if (ptr->getLeft())
		printPreorder(ptr->getLeft());
	if (ptr->getRight())
		printPreorder(ptr->getRight());
}

bool Tree::rotateTreeRight(TreeNode* pnode, TreeNode* cnode)
{
	if (pnode && pnode->getParent() && pnode->getLeft() == cnode)
	{
		TreeNode* gpnode = pnode->getParent();
		gpnode->setLeft(pnode->getRight());
		if (gpnode->getLeft())
			gpnode->getLeft()->setParent(gpnode);
		pnode->setParent(gpnode->getParent());
		pnode->setRight(gpnode);
		pnode->setLeft(cnode);
		if (pnode->getParent())
		{
			if (pnode->getParent()->getLeft() == gpnode)
				pnode->getParent()->setLeft(pnode);
			else
				pnode->getParent()->setRight(pnode);
		}
		else
			anker = pnode;

		gpnode->setParent(pnode);
		return true;
	}
	return false;
}

bool Tree::rotateTreeLeft(TreeNode* pnode, TreeNode* cnode)
{
	if (pnode && pnode->getParent() && pnode->getRight() == cnode)
	{
		TreeNode* gpnode = pnode->getParent();
		gpnode->setRight(pnode->getLeft());
		if (gpnode->getRight())
			gpnode->getRight()->setParent(gpnode);
		pnode->setParent(gpnode->getParent());
		pnode->setLeft(gpnode);
		pnode->setRight(cnode);
		if (pnode->getParent())
		{	//GGP
			if (pnode->getParent()->getLeft() == gpnode)
				pnode->getParent()->setLeft(pnode);
			else
				pnode->getParent()->setRight(pnode);
		}
		else
			anker = pnode;

		gpnode->setParent(pnode);
		return true;
	}
	return false;
}

bool Tree::balanceTree(TreeNode* node)
{
	TreeNode* ptrnode = node;
	while (ptrnode != anker)
	{
		TreeNode* pnode = ptrnode->getParent();
		TreeNode* gpnode = pnode->getParent();
		if (ptrnode->getRed() && pnode->getRed())
		{	//R~R gefunden
			if (gpnode->getRight() == pnode)
			{	//G~P
				if (pnode->getRight() == ptrnode)
				{	//L
					rotateTreeLeft(pnode,ptrnode);
					pnode->setRed(false);
					gpnode->setRed(true);
				}
				else
				{	//RL
					rotateTreeRight(ptrnode, ptrnode->getLeft());
					rotateTreeLeft(ptrnode, pnode);
					gpnode->setRed(true);
					ptrnode->setRed(false);
				}
			}
			else
			{	//P~G
				if (pnode->getLeft() == ptrnode)
				{	//R
					rotateTreeRight(pnode, ptrnode);
					pnode->setRed(false);
					gpnode->setRed(true);
				}
				else
				{	//LR
					rotateTreeLeft(ptrnode, ptrnode->getRight());
					rotateTreeRight(ptrnode, pnode);
					gpnode->setRed(true);
					ptrnode->setRed(false);
				}
			}
		}
		ptrnode = pnode;
	}
	return true;
}

void Tree::printLevelOrder()
{
	if (!anker)
	{
		cout << "+ Leerer Baum.\n";
		return;
	}
	cout << "ID |    Name    | Alter | Einkommen |  PLZ  | Pos  " << endl
		<< "---+------------+-------+-----------+-------+------" << endl;

	std::queue<TreeNode*> q;
	q.push(anker);
	while (!q.empty())
	{
		TreeNode* ptrnode = q.front();
		q.pop();
		ptrnode->print();
		if (ptrnode->getLeft())
			q.push(ptrnode->getLeft());
		if (ptrnode->getRight())
			q.push(ptrnode->getRight());
	}

	cout << "---+------------+-------+-----------+-------+------" << endl;
}
