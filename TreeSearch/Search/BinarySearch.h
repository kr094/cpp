#ifndef _BINARY_SEARCH_H_
#define _BINARY_SEARCH_H_

#include <iostream>
#include "ASearch.h"
using namespace std;

class BinarySearch : public ASearch
{
public:
	BinarySearch();
	int run(int target, int numbers[], int size);
};
#endif