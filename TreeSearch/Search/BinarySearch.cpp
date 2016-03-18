#include "BinarySearch.h"

BinarySearch::BinarySearch()
{

}

int BinarySearch::run(int target, int numbers[], int size)
{
	int index = -1;
	int imin = 0;
	int imax = size;
	// continue searching while [imin,imax] is not empty
	while (imax >= imin)
	{
		// calculate the midpoint for roughly equal partition
		int imid = (imin + imax) / 2;

		if(numbers[imid] == target)
		{
			index = imid;
			break;
		}
		else if (numbers[imid] < target)
		// change min index to search upper subarray
		imin = imid + 1;
		else         
		// change max index to search lower subarray
		imax = imid - 1;
	}

	return index;
}