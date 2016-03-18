#include <iostream>
#include <ctime>
#include <time.h>
#include <random>
#include "SequentialSearch.h"
#include "BinarySearch.h"

int main()
{
	const int ARRAY_SIZE = 10000;
	int numbers[ARRAY_SIZE];
	unsigned int ssearchTime = 0;
	unsigned int bsearchTime = 0;
	
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, 999);
	generator.seed((unsigned int)time(0));
	
	for(int i = 0; i < ARRAY_SIZE; i++)
	{
		numbers[i] = i + 1;
	}

	cout << "Randomizing array" << endl;

	for(int j = 0; j < 100; j++)
	{
		for(int i = 0; i < ARRAY_SIZE; i++)
		{
			int rand = distribution(generator);
			int temp = numbers[i];
			numbers[i] = numbers[rand];
			numbers[rand] = temp;
		}
	}

	ASearch *search;
	search = new SequentialSearch();
	int index = -1;

	cout << "Sequential Search Starting..." << endl;

	clock_t start = clock();
	for(int i = 0; i < ARRAY_SIZE; i++)
	{
		index = search->run(i + 1, numbers, ARRAY_SIZE);
	}
	clock_t end = clock();
	ssearchTime = (unsigned int) (end - start);	

	cout << endl << "\t! Sequential Search Completed in " << ssearchTime << " microseconds" << endl << endl;

	cout << "Re-ordering array" << endl;

	for(int i = 0; i < ARRAY_SIZE; i++)
	{
		numbers[i] = i + 1;
	}

	search = new BinarySearch();

	cout << "Binary Search Starting..." << endl;
	start = clock();
	for(int i = 0; i < ARRAY_SIZE; i++)
	{
		index = search->run(i + 1, numbers, ARRAY_SIZE);
	}
	end = clock();
	bsearchTime = (unsigned int) (end - start);
	cout << endl << "\t! Binary Search Completed in " << bsearchTime << " microseconds" << endl << endl;
	cin.ignore();
	
	return 0;
}