#ifndef _NODE_H_
#define _NODE_H_
#include <string>
using namespace std;

class Node
{
private:
	string value;
	
public:
	Node *left;
	Node *right;

	Node();
	Node(string value);

	string getValue();
};

typedef Node* NodePtr;

#endif