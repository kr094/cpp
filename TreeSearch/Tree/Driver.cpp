#include <iostream>
#include <ctime>
#include "Tree.h"
#include "Hash.h"
using namespace std;

#define DICTIONARY_FILE "dictionary.txt"
#define MISPELLED_FILE "mispelled.txt"
#define VERBOSE_COUT 1

int main()
{
	ifstream dictionaryFile(DICTIONARY_FILE);
	dictionaryFile.seekg(0, dictionaryFile.end);
	long dictionaryLength = dictionaryFile.tellg();
	dictionaryFile.seekg(0, dictionaryFile.beg);
	
	string *dictionaryArray = new string[dictionaryLength];

	int dictionaryWordCount = 0;
	string word = "";
	char c;

	if(dictionaryFile.good())
	{
		while( (c = dictionaryFile.get()) != EOF)
		{
			if(c == '\n')
			{
				std::transform(word.begin(), word.end(), word.begin(), ::tolower);
				dictionaryArray[dictionaryWordCount] = word;
				dictionaryWordCount++;
				word = "";
				continue;
			}
			word += c;
		}
	}
    dictionaryFile.close();
	
	ifstream mispelledFile(MISPELLED_FILE);
	mispelledFile.seekg(0, mispelledFile.end);
	long mispelledLength = mispelledFile.tellg();
	mispelledFile.seekg(0, mispelledFile.beg);

	string *mispelledArray = new string[mispelledLength]; 
	
	int mispelledWordCount = 0;
	word = "";
	c = 0;
	
	if(mispelledFile.good())
	{
		while( (c = mispelledFile.get()) != EOF)
		{
			if(c == '\n')
			{
				continue;
			}
			if(c == ' ')
			{
				if(word != "")
				{
					mispelledArray[mispelledWordCount] = word;
					mispelledWordCount++;
					word = "";
				}
				continue;
			}
			if(!isalpha(c))
			{
				continue;
			}
			word += c;
		}
	}
    mispelledFile.close();
	
	string tempValue = "";
	bool inTreeResult = false;

	unsigned int startTime = clock();
	Tree tree = Tree(dictionaryArray, dictionaryWordCount);
		
#if VERBOSE_COUT
	cout << tree << endl << "Mispelled Words:" << endl << endl;
#endif
	
	NodePtr root = tree.getRoot();
	for(int i = 0; i < mispelledWordCount; i++)
	{
		tempValue = mispelledArray[i];		
		std::transform(tempValue.begin(), tempValue.end(), tempValue.begin(), ::tolower);
		inTreeResult = false;
		tree.inTree(tempValue, root, inTreeResult);
		if(!inTreeResult)
		{
			cout << mispelledArray[i] << endl;
		}
	}
	
	unsigned int endTime = clock();
	cout << endl << "Completed in " << endTime - startTime << " microseconds" << endl << endl;
	
	
	startTime = clock();
	Hash hash = Hash(dictionaryArray, dictionaryWordCount);

#if VERBOSE_COUT
	cout << hash << endl << "Mispelled Words:" << endl << endl;
#endif

	for(int i = 0; i < mispelledWordCount; i++)
	{
		tempValue = mispelledArray[i];		
		std::transform(tempValue.begin(), tempValue.end(), tempValue.begin(), ::tolower);
		inTreeResult = false;
		hash.inTable(tempValue, inTreeResult);
		if(!inTreeResult)
		{
			cout << mispelledArray[i] << endl;
		}
	}

	endTime = clock();
	cout << endl << "Completed in " << endTime - startTime << " microseconds" << endl;
	cin.ignore();
	return 0;

}