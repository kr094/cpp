#ifndef _TREE_H_
#define _TREE_H_
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include "Node.h"
using namespace std;

class Tree
{
private:
	int length;
	NodePtr root;
	
public:
	Tree();
	Tree(string value);
	Tree(string *dictionaryArray, int wordCount);
	int getLength();

	NodePtr getRoot();
	int getHeight(NodePtr node);
	void insert(string value);
	void insert(string value, NodePtr &node);
	void inTree(string value, bool &result);
	void inTree(string value, NodePtr node, bool &result);

	void rotateRight(NodePtr &node);
	void rotateLeft(NodePtr &node);
	void doubleRotateRight(NodePtr &node);
	void doubleRotateLeft(NodePtr &node);

	void printTree(ostream &output);
	void printTreeInOrder(ostream &output, NodePtr node);
	void printTree(ostream &output, NodePtr node, int indent);
    friend ostream& operator<<(ostream &output, Tree &tree);
};

#endif