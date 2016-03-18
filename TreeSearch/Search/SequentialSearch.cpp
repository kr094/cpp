#include "SequentialSearch.h"

SequentialSearch::SequentialSearch()
{

}

int SequentialSearch::run(int target, int numbers[], int size)
{
	int index = -1;

	for(int i = 0; i < size; i++)
	{
		if(numbers[i] == target)
			index = i;
	}

	return index;
}