#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <random>
using namespace std;

const int RANDOM_HIGH = 100000;
const int RANDOM_LOW = 1;
const long int ARRAY_SIZE = 10000;

#pragma region
void print(int numbers[], int size);
void printHeader(int currentSort);
void copyArray(int dest[], int source[]);
void runSort(int numbers[], int master[], int size, int currentSort);

class record
{
private:
	string line;
	int num;
public:
	record()
	{
		this->line = "";
		this->num = 0;
	}

	record(string line, int num)
	{
		this->line = line;
		this->num = num;
	}

	string getLine()
	{
		return this->line;
	}
	
	int getNum()
	{
		return this->num;
	}
};

//XOR Swap function
void _swap(int &a, int &b);

//bubbleSort
//int[] - source array
//int - length of the array
void bubbleSort(int numbers[], int size);

//selectionSort
//int[] - source array
//int - length of the array
void selectionSort(int numbers[], int size);

//insertionSort
//int[] - source array
//int - length of the array
void insertionSort(int numbers[], int size);

//mergeSort
//int[] - source array
//int - length of the array
void mergeSort(int numbers[], int size);
//This is the actual split, sort, and merge function
//int[] - source array
//int - leftmost boundary, initially 0
//int - rightmost boundary, initial array length
//int[] - array of similar dimensions for temp sorting
void mergeSplit(int numbers[], int left, int right, int sorted[]);

//quickSort
//int[] - source array
//int - leftmost boundary, initially 0
//int - rightmost boundary, initial array length
void quickSort(int numbers[], int left, int right);
void recordQuickSort(record numbers[], int left, int right);

//partialInsertion
//Insertion sort with left and right walls instead of sorting from 0 - size
//Used in an idea for a partial insertion sort after quicksort => right - left <= 100 elements
//int[] - source array
//int - length of the array
void partialInsertion(int numbers[], int left, int right);

void externalMergeSort();

int getNum(string line);
string getLine(string line);

enum SORT_TYPES {NONE = 0, BUBBLE, SELECT, INSERT, MERGE, QUICK, EXTMERGE, LAST_MARKER};
#pragma endregion defs
int main()
{
	int masterArray[ARRAY_SIZE];
	int numbers[ARRAY_SIZE];
	int currentSort = NONE;

	ofstream extMerge = ofstream("extmerge.txt");
	//Prep the master array for this sort
	
	default_random_engine generator;
	uniform_int_distribution<int> distribution(RANDOM_LOW, RANDOM_HIGH); 
	generator.seed((unsigned int)time(0));
	for(int i = 0; i < ARRAY_SIZE; i++)
	{
		masterArray[i] = distribution(generator);
		extMerge << "Line " << i + 1 << "," << masterArray[i] << endl;
	}

	extMerge.close();

	//Loop through all the sort methods in SORT_TYPES and run them
	for(int i = 1; i < LAST_MARKER; i++)
	{
		currentSort = i;
		runSort(numbers, masterArray, ARRAY_SIZE, currentSort);
	}

	/*currentSort = EXTMERGE;
	runSort(numbers, masterArray, ARRAY_SIZE, currentSort);*/
	cin.ignore();
}

#pragma region
void runSort(int numbers[], int master[], int size, int currentSort)
{
	clock_t startTime = 0;
	clock_t endTime = 0;
	double totalTime = 0;
	long milli = 0;

	//Print sorting info
	printHeader(currentSort);
	//Prep numbers for sorting from the master array
	copyArray(numbers, master);

	//Set the clock for timing, and pick the right sort, then call it.
	startTime = clock();
	switch(currentSort)
	{
		case BUBBLE: bubbleSort(numbers, size); break;
		case SELECT: selectionSort(numbers, size); break;
		case INSERT: insertionSort(numbers, size); break;
		case MERGE: mergeSort(numbers, size); break;
		case QUICK: quickSort(numbers, 0, size - 1); break;
		case EXTMERGE: externalMergeSort(); break;
	}
	endTime = clock();

	try
	{
		totalTime = double(endTime - startTime);
		//print(numbers, ARRAY_SIZE);
	}
	catch(exception e)
	{
		perror(strcat("Could not calulate time for this sort!\r\n", e.what()));
	}

	cout << "---" << endl;
	cout << "Sorted " << ARRAY_SIZE << " numbers in " << totalTime << "ms" << endl << endl;
}

void copyArray(int dest[], int source[])
{	
	for(int i = 0; i < ARRAY_SIZE; i++)
		dest[i] = source[i];
}

void printHeader(int currentSort)
{	
	cout << "Sorting " << ARRAY_SIZE << " numbers between " << RANDOM_LOW << " and " << RANDOM_HIGH << " with ";

	char  *sortType = "Bubble Sort";

	switch(currentSort)
	{
		case BUBBLE: sortType = "Bubble Sort"; break;
		case SELECT: sortType = "Selection Sort"; break;
		case INSERT: sortType = "Insertion Sort"; break;
		case MERGE: sortType = "Merge Sort"; break;
		case QUICK: sortType = "Quick Sort"; break;
		case EXTMERGE: sortType = "External Merge Sort"; break;
	}

	cout << sortType << endl;		
}

void print(int numbers[], int size)
{
	for(int i = 0; i < size; i++)
		cout << numbers[i] << endl;
}

void _swap(int &a, int &b)
{
	/*
	https://en.wikipedia.org/wiki/XOR_swap_algorithm
	*/
	a ^= b;
	b ^= a;
	a ^= b;
}

void bubbleSort(int numbers[], int size)
{
	int offsetSize = size - 1;
	//for each element in the array
	for(int i = 0; i < size; i++)
	{
		//bubble the array one time
		for(int j = 0; j < offsetSize; j++)
		{
			//if a > b
			if(numbers[j] > numbers[j+1])
			{
				_swap(numbers[j], numbers[j+1]);
			}
		}
	}
}

void insertionSort(int numbers[], int size)
{
	int offsetSize = size - 1;
	//for each element in the array
	for(int i = 0; i < size; i++)
	{
		//save this element
		int x = numbers[i];
		int j = i;
		//start pushing elements to the right
		//stop when the array was right shifted as far as possible
		//OR we have found where x belongs (X < j-1)
		while(j > 0 && numbers[j - 1] > x)
		{
			//ripple the array to make space
			numbers[j] = numbers[j - 1];
			j--;
		}
		//put the value where it belongs
		numbers[j] = x;
	}
}

void partialInsertion(int numbers[], int left, int right)
{
	int offsetSize = right - 1;
	//for each element in the array
	for(int i = left; i < right; i++)
	{
		//save this element
		int x = numbers[i];
		int j = i;
		//start pushing elements to the right
		//stop when the array was right shifted as far as possible
		//OR we have found where x belongs (X < j-1)
		while(j > 0 && numbers[j - 1] > x)
		{
			//ripple the array to make space
			numbers[j] = numbers[j - 1];
			j--;
		}
		//put the value where it belongs
		numbers[j] = x;
	}
}

void selectionSort(int numbers[], int size)
{
	int offsetSize = size - 1;
	//for each element in the array
	for (int i = 0; i < offsetSize; i++) 
	{
		//assume the min is the first unsorted element
		int minIndex = i;
		//test against elements after j to find the smallest
		for (int j = i+1; j < size; j++) 
		{
			//if this element is less, then it is the new minimum
			if (numbers[j] < numbers[minIndex]) 
			{
				minIndex = j;
			}
		}

		//swap the new minimum where it belongs
		if (minIndex != i) 
		{
			_swap(numbers[i], numbers[minIndex]);
		}
	}
}

void mergeSort(int numbers[], int size)
{
	int sorted[ARRAY_SIZE];
	mergeSplit(numbers, 0, size, sorted);
}

void mergeSplit(int numbers[], int left, int right, int B[])
{
	if(right - left <= 1)
		return;
	int mid = (right + left) / 2;
	//Split the left side
	mergeSplit(numbers, left, mid, B);
	//Split the right side
	mergeSplit(numbers, mid, right, B);
	
	int iLeft = left, iRight = mid;
 
	//Start at the left and work to the right
    for (int j = left; j < right; j++) 
	{
		//if the left isnt past the middle
		if(iLeft < mid)
		{
			//catch up the left pointer
			//small number(s)
			if(iRight >= right)
				B[j] = numbers[iLeft++];
			//the primary check/sort
			//small number
			else if(numbers[iLeft] <= numbers[iRight])								
				B[j] = numbers[iLeft++];
			//large number
			else				
				B[j] = numbers[iRight++];
		}
		//largest number
		else
			B[j] = numbers[iRight++];
    }
	
	//move sorted array back into original pointer
	for(int i = left; i < right; i++)
		numbers[i] = B[i];
}

void quickSort(int numbers[], int left, int right)
{
	int i = left, j = right;

	int one = numbers[left]
		,two = numbers[abs((left + right) / 2)]
		,three = numbers[right];
	int pivot = (one + two + three) / 3;

	//start sorting around the pivot
	//move in from both sides
	//stop when left <= right (cross)
	while (i <= j) 
	{
		//start looking at the array from the left
		//stop when an element is greater than pivot
		for(i; numbers[i] < pivot; i++);
		//start looking backwards from the right
		//stop when an element is less than the pivot
		for(j; numbers[j] > pivot; j--);

		//we have two elements on either side that are 'out of place'
		
		//if i and j are respective to the order of the array (while i <= j)
		//without this check the biggest element would unswap
		if (i <= j) 
		{
			//don't xorswap if we're swapping something with itself
			if(numbers[i] != numbers[j])
				//swap the two 'out of place' elements
				_swap(numbers[i], numbers[j]);
			//move on
			i++;
			j--;
		}
	}
	//the whole array has been divided into two roughly pivot sorted halves
	//quicksort the 2 halves, recursively
	if (left < j)
	quickSort(numbers, left, j);

	if (i < right)
	quickSort(numbers, i, right);
}

#pragma endregion Sort methods

void recordQuickSort(record numbers[], int left, int right)
{
	int i = left, j = right;

	int one = numbers[left].getNum()
		,two = numbers[abs((left + right) / 2)].getNum()
		,three = numbers[right].getNum();
	int pivot = (one + two + three) / 3;

	//start sorting around the pivot
	//move in from both sides
	//stop when left <= right (cross)
	while (i <= j) 
	{
		//start looking at the array from the left
		//stop when an element is greater than pivot
		for(i; numbers[i].getNum() < pivot; i++);
		//start looking backwards from the right
		//stop when an element is less than the pivot
		for(j; numbers[j].getNum() > pivot; j--);

		//we have two elements on either side that are 'out of place'
		
		//if i and j are respective to the order of the array (while i <= j)
		//without this check the biggest element would unswap
		if (i <= j) 
		{
			//don't xorswap if we're swapping something with itself
			if(numbers[i].getNum() != numbers[j].getNum())
			{
				record temp = numbers[i];
				numbers[i] = numbers[j];
				numbers[j] = temp;
			}
			//move on
			i++;
			j--;
		}
	}
	//the whole array has been divided into two roughly pivot sorted halves
	//quicksort the 2 halves, recursively
	if (left < j)
	recordQuickSort(numbers, left, j);

	if (i < right)
	recordQuickSort(numbers, i, right);
}

int getNum(string line)
{
	int len = line.length();
	string tempNum = "";
	string numStr = "";
	for(int i = len - 1; i > 0; i--)
	{
		if(line[i] == ',')
			break;
		else
		{
			tempNum += (char) line[i];
		}
	}

	len = tempNum.length();
	for(int i = len - 1; i >= 0; i--)
	{
		numStr += (char) tempNum[i];
	}

	return atoi(numStr.c_str());
}

string getLine(string line)
{
	int len = line.length();
	string str = "";
	for(int i = 0; i < len; i++)
	{
		if(line[i] == ',')
			break;
		else
		{
			str += line[i];
		}
	}

	return str;
}

void externalMergeSort()
{
	const int readLines = ARRAY_SIZE / 10;
	ifstream extFile = ifstream("extmerge.txt");
	ofstream temp1 = ofstream("1.tmp", ios::out);
	ofstream temp2 = ofstream("2.tmp", ios::out);
	int i = 0;
	bool file1Write = false;
	while(i < ARRAY_SIZE / 2)
	{
		int end = i + readLines;
		int tempI = 0;
		record numbers[readLines];
		string line = "";
		for(i; i < end; i++)
		{
			getline(extFile, line);
			numbers[tempI++] = record(getLine(line), getNum(line));
		}

		recordQuickSort(numbers, 0, readLines - 1);
		record temp;

		file1Write = (file1Write ? false : true);
		for(int j = 0; j < readLines; j++)
		{
			temp = numbers[j];
			if(file1Write)
				temp1 << temp.getLine() << ',' << temp.getNum() << endl;
			else
				temp2 << temp.getLine() << ',' << temp.getNum() << endl;
		}
	}
	temp1.close();
	temp2.close();

	ifstream file1 = ifstream("1.tmp");
	ifstream file2 = ifstream("2.tmp");
	ofstream temp3 = ofstream("3.tmp");
	ofstream temp4 = ofstream("4.tmp");
	string line = "";
	string line2 = "";
	record r;
	record r2;
	record rtemp;
	i = 0;
	int read = 0;
	bool end = false;
	while(i < ARRAY_SIZE)
	{
		int file1P = 0;
		int file2P = 0;
		file1Write = (file1Write ? false : true);
		int numsort = 0;
		
		getline(file1, line);
		getline(file2, line2);
		r = record(getLine(line), getNum(line));
		r2 = record(getLine(line2), getNum(line2));

		while(numsort < readLines * 2)
		{			
			if(r.getNum() < r2.getNum())
			{
				rtemp = r;
				getline(file1, line);
				r = record(getLine(line), getNum(line));
				file1P++;
			}
			else
			{
				rtemp = r2;	
				getline(file2, line2);
				r2 = record(getLine(line2), getNum(line2));
				file2P++;
			}			
			
			if(file1P == readLines)
			{
				rtemp = r2;	
			}
			else if(file2P == readLines)
			{
				rtemp = r;
			}
			
			if(file1Write)
				temp3 << rtemp.getLine() << ',' << rtemp.getNum() << endl;
			else						
				temp4 << rtemp.getLine() << ',' << rtemp.getNum() << endl;

			numsort++;
		}
		i += numsort;
	}
}

	//*keep track of i
	//*if file not eof
	//*read i < (end = i + 1000) lines
	//*into object array record(line, num)
	//*pivot sort the array by num
	//*write 1000 rows to file temp1 OR temp2
	//*file 1 and file2 both have 5000 sorted 1000 groupings
	//*open temp1 and temp2
	//*set up file line size
	//*set up file line pointers
	//*for(i <= 1000; i++)
	//*read one record(line, num) from each file; filePointerX++;
	//*if temp3 is being written to, or temp4 is being written to
	//*write the smaller one to tempX
	//*temp3 and temp 4 now have groupings of 2000, one has 2000 more. 
	//open temp3 and temp4
	//set file pointers to end
	//for(i <= 1000; i++)
	//read one record(line, num) from each file
	//put the smaller one into file5 OR file 6
	//file5 and file6 each have 5000 sorted 1000 groupings
	//final sort merge them into sorted file