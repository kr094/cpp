#include "Node.h"

Node::Node()
{
	this->left = 0;
	this->right = 0;
	this->value = "";
}

Node::Node(string value)
{
	this->left = 0;
	this->right = 0;
	this->value = value;
}

string Node::getValue()
{
	return this->value;
}