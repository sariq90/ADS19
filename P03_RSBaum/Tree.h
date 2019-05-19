/*************************************************
* ADS Praktikum 2.2
* Tree.h
* Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
*************************************************/
#pragma once
#include <string>
#include "TreeNode.h"
#include "catch.h"

using namespace std;

class Tree{
	
	private: 

		TreeNode* anker;
		int NodeIDCounter;
	
		// Rekursive Hilfsfunktionen
		void searchPreorder(string name, TreeNode* ptr, int &count);
		void printPreorder(TreeNode* ptr);

		bool rotateTreeRight(TreeNode* pnode, TreeNode* cnode);
		bool rotateTreeLeft(TreeNode* pnode, TreeNode* cnode);

	public:

		Tree();
		void addNode(string name, int alter, double eink, int plz);
		bool searchNode(string name);
		void printAll();

		bool balanceTree(TreeNode* node);
		void printLevelOrder();
			   
		////////////////////////////////////
		// friend-Funktionen sind für die Tests erforderlich und müssen unangetastet bleiben! 
		friend TreeNode * get_anker(Tree& TN);
};
