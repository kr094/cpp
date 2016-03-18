#ifndef _HASH_H
#define _HASH_H
#include <iostream>
#include <string>
#include "Tree.h"
using namespace std;

#define HASH_TABLE_SIZE 53

class Hash
{
private:
	int length;
	Tree **table;
	
public:
	Hash();
	Hash(string *dictionaryArray, int wordCount);

	void insert(string value);
	int getIndex(string value);
	void inTable(string value, bool &result);
	
	void printTable(ostream &output);
    friend ostream& operator<<(ostream &output, Hash &hash);
};

#endif