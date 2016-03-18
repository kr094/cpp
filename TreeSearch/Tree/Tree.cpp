#include "Tree.h"

Tree::Tree()
{
	this->root = 0;
	this->length = 0;
}

Tree::Tree(string value)
{
	this->root = 0;
	this->length = 0;
	this->insert(value, this->root);
}

Tree::Tree(string *dictionaryArray, int wordCount)
{
	this->root = 0;
	this->length = 0;
	for(int i = 0; i < wordCount; i++)
	{
		this->insert(dictionaryArray[i], this->root);
	}	
}

int Tree::getLength()
{
	return this->length;
}

int Tree::getHeight(NodePtr node)
{
	/*
	 * Magic
	 * 
	 * call recursively until node == NULL and return 0
	 * add the height (initially set by return 0) + 1 for each level of recursion (call stack pop)
	 */
	if(node == NULL)
		return 0;
	else
		return max(getHeight(node->left), getHeight(node->right)) + 1;
}

NodePtr Tree::getRoot()
{
	return this->root;
}

void Tree::insert(string value)
{
	this->insert(value, this->root);
	this->length++;
}

void Tree::insert(string value, NodePtr &node)
{
	if(node == NULL)
	{
		node = new Node(value);
	}
	//insert below left
	else if(value < node->getValue())
	{
		this->insert(value, node->left);
	}
	//insert below right
	else if(value > node->getValue())
	{
		this->insert(value, node->right);
	}
	else
	{
		cout << value << " Already exists." << endl;
	}

	//rebalance
	//this is called all the way back up the stack
	if(getHeight(node->left) - getHeight(node->right) >= 2)
	{
		if(value < node->left->getValue())
		{
			this->rotateLeft(node);
		}
		else
		{
			this->doubleRotateLeft(node);
		}
	}
	else if(getHeight(node->right) - getHeight(node->left) >= 2)
	{
		if(value > node->right->getValue())
		{
			this->rotateRight(node);
		}
		else
		{
			this->doubleRotateRight(node);
		}
	}
}

void Tree::inTree(string value, bool &result)
{
	this->inTree(value, this->root, result);
}

void Tree::inTree(string value, NodePtr node, bool &result)
{
	if (node == NULL)
	{
		result = false;
	}
	else
	{
		if (value < node->getValue())
		{
			this->inTree(value, node->left, result);
		}
		else if (value > node->getValue())
		{
			this->inTree(value, node->right, result);
		}
		else
		{
			result = true;
		}
	}
}

void Tree::rotateRight(NodePtr &node)
{
	NodePtr tempNode;
	tempNode = node->right;
	node->right = tempNode->left;
	tempNode->left = node;
	node = tempNode;
}

void Tree::rotateLeft(NodePtr &node)
{	
	NodePtr tempNode;
	tempNode = node->left;
	node->left = tempNode->right;
	tempNode->right = node;
	node = tempNode;
}


void Tree::doubleRotateRight(NodePtr &node)
{
	rotateLeft(node->right);
	rotateRight(node);
}


void Tree::doubleRotateLeft(NodePtr &node)
{
	rotateRight(node->left);
	rotateLeft(node);
}

void Tree::printTree(ostream &output, NodePtr node, int indent)
{
	if(node != NULL)
    {
		this->printTree(output, node->right, indent + 12);

		output << string(indent, ' ');

		output << node->getValue() << endl;     

		this->printTree(output, node->left, indent + 12);
    }
}

void Tree::printTree(ostream &output)
{
	this->printTree(output, this->root, 0);
}

void Tree::printTreeInOrder(ostream &output, NodePtr node)
{
	if(node != NULL)
	{
		this->printTreeInOrder(output, node->left);

		output << node->getValue() << endl;

		this->printTreeInOrder(output, node->right);
	}
}

ostream& operator<<(ostream &output, Tree &tree)
{
	//output << endl << endl << "Printing tree in-order:" << endl << endl;
	//tree.printTreeInOrder(output, tree.getRoot());

	output << endl << "Printing tree:" << endl << endl;
	tree.printTree(output, tree.getRoot(), 0);    

    return output << endl;
}
