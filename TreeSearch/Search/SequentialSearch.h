#ifndef _SEQUENTIAL_SEARCH_H_
#define _SEQUENTIAL_SEARCH_H_

#include <iostream>
#include "ASearch.h"
using namespace std;

class SequentialSearch : public ASearch
{
public:
	SequentialSearch();
	int run(int target, int numbers[], int size);
};
#endif