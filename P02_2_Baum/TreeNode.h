/*************************************************
* ADS Praktikum 2.2
* TreeNode.h
* Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
*************************************************/
#pragma once
#include <string>

using namespace std;

class TreeNode{
	
	private:

		int NodePosID;
		int NodeID;
		string Name;
		int Alter;
		double Einkommen;
		int PLZ;
		TreeNode* left;
		TreeNode* right;
	
	public:

		TreeNode(int ndpos, int ndid, string name, int alter, double eink, int plz);
		int getNodePosID();
		int getNodeID();
		string getName();
		void setName(string name);
		int getAlter();
		void setAlter(int alter);
		double getEinkommen();
		void setEinkommen(double eink);
		int getPLZ();
		void setPLZ(int plz);

		TreeNode* getLeft();
		TreeNode* getRight();
		void setLeft(TreeNode* node);
		void setRight(TreeNode* node);
		void print();


};

