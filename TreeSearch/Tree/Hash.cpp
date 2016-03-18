#include "Hash.h"

Hash::Hash()
{
	this->table[0] = new Tree();
}

Hash::Hash(string *dictionaryArray, int wordCount)
{
	this->length = wordCount;
	//create pointer to array of pointers
	this->table = new Tree *[this->length];
	for(int i = 0; i < this->length; i++)
	{
		//create new Tree for each array index
		this->table[i] = new Tree();
	}
	//insert each dictionary word
	for(int i = 0; i < this->length; i++)
	{		
		this->insert(dictionaryArray[i]);
	}
}

int Hash::getIndex(string value)
{
	int len = value.length();
	int total = 0;
	for(int i = 0; i < len; i++)
	{
		//character ascii value
		total += (int)value[i];
		//add the current pos
		total += i;
	}
	
	//get index
	int index = total % HASH_TABLE_SIZE;
	//resize if larger than array offset
	if(index >= 52)
		index = 51;
	return index;
}

void Hash::insert(string value)
{
	//hash value
	int index = this->getIndex(value);
	//get the tree
	Tree *tree = this->table[index];
	//insert value into tree at index
	tree->insert(value);
}

void Hash::inTable(string value, bool &result)
{
	//hash value
	int index = this->getIndex(value);
	//get the tree
	Tree *tree = this->table[index];
	//check for value in tree
	tree->inTree(value, result);
}

void Hash::printTable(ostream &output)
{
	int totalLength = 0;

	for(int i = 0; i < this->length; i++)
	{
		Tree *tree = this->table[i];
		if(tree->getRoot() != 0)
		{
			output << "Index: " << i << endl;
			output << "Length: " << tree->getLength() << endl;
			tree->printTree(output);
			output << endl << endl;
		}
		totalLength += tree->getLength();
	}
	output << "Total Length: " << totalLength << endl;
}

ostream& operator<<(ostream &output, Hash &hash)
{
	output << endl << "Printing Hash:" << endl << endl;
	hash.printTable(output);
	return output;
}

