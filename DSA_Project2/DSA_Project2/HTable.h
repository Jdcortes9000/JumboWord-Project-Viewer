#pragma once

#include <iostream>
#include "SLList.h"
using namespace std;


template<typename Type> class HTable
{
	unsigned int buckets;
	SLList<Type>* HashTable;
	unsigned int(*IndexFunc)(const Type &v);
public:
	/////////////////////////////////////////////////////////////////////////////
	// Function : Constructor 
	// Parameters : numOfBuckets - the number of buckets
	//              hFunction - pointer to the hash function for this table
	// Notes : constructs an empty hash table
	/////////////////////////////////////////////////////////////////////////////
	HTable(unsigned int numOfBuckets, unsigned int(*hFunction) (const Type &v))
	{
		buckets = numOfBuckets;
		HashTable = new SLList<Type>[numOfBuckets];
		IndexFunc = hFunction;

	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : Destructor
	// Notes : destroys a hash table
	/////////////////////////////////////////////////////////////////////////////
	~HTable()
	{
		clear();
		delete[] HashTable;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : Assignment Operator
	/////////////////////////////////////////////////////////////////////////////
	HTable<Type>& operator=(const HTable<Type>& that)
	{
		if (this != &that)
		{
			clear();
			IndexFunc = that.IndexFunc;
			buckets = that.buckets;
			HashTable = new SLList<Type>[buckets];
			for (unsigned int i = 0; i < buckets; i++)
			{
				HashTable[i] = that.HashTable[i];
			}

		}
		return *this;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : Copy Constructor
	/////////////////////////////////////////////////////////////////////////////
	HTable(const HTable<Type>& that)
	{
		//clear();
		IndexFunc = that.IndexFunc;
		buckets = that.buckets;
		HashTable = new SLList<Type>[buckets];
		for (unsigned int i = 0; i < buckets; i++)
		{
			HashTable[i] = that.HashTable[i];	
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : insert
	// Parameters : v - the item to insert into the hash table
	/////////////////////////////////////////////////////////////////////////////
	void insert(const Type& v)
	{
		unsigned int idx = IndexFunc(v);
		HashTable[idx].addHead(v);
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : findAndRemove
	// Parameters : v - the item to remove(if it is found)
	/////////////////////////////////////////////////////////////////////////////
	bool findAndRemove(const Type& v)
	{
		unsigned int idx = IndexFunc(v);
		SLLIter<Type> Iter = HashTable[idx];
		for (unsigned int i = 0; i < HashTable[idx].size(); i++)
		{
			if (Iter.current() == v)
			{
				HashTable[idx].remove(Iter);
				return true;
			}
			else
			{
				++Iter;
			}
		}
		return false;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : clear
	// Notes : clears the hash table
	/////////////////////////////////////////////////////////////////////////////
	void clear()
	{
		for (unsigned int i = 0; i < buckets; i++)
		{
			HashTable[i].clear();
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : find
	// Parameters : v - the item to look for
	// Return : the bucket we found the item in or -1 if we didn’t find the item.
	/////////////////////////////////////////////////////////////////////////////
	int find(const Type& v) const
	{
		unsigned int idx = IndexFunc(v);
		SLLIter<Type> Iter = HashTable[idx];
		for (unsigned int i = 0; i < HashTable[idx].size(); i++)
		{
			if (Iter.current() == v)
			{
				return idx;
			}
			else
			{
				++Iter;
			}
		}
		return -1;
	}
	string GetWord(unsigned int index) 
	{
		bool check = true;
		bool loop = true;
		unsigned int idx;
		srand((unsigned int)time(NULL));
		while (check)
		{
			loop = true;
			while (true)
			{
				idx = rand() % index;
				if (HashTable[idx].size() > 0)
					break;
			}
			while (loop)
			{
				SLLIter<Type> Iter = HashTable[idx];
				unsigned int stop = HashTable[idx].size() & rand();
				for (unsigned int i = 0; i < stop; i++)
				{
					string result = Iter.current();
					if (result.length() >5 && result.length() < 7)
					{
						check = false;
						return result;
					}
					if (i == stop - 1)
					{
						if (check == false)
						{
							if (result.length() == 6)
							{
								result = Iter.current();
								return result;
							}
						}
						else
						{
							loop = false;
							check = true;
							break;
						}

					}
					else
					{
						++Iter;
					}
				}
			}
		}
		return 0;
	}
	void HTable<Type>::printSomeStuff(const char* filePath = "hashdata.txt")
	{
		// we're gonna need to open a file for all this data
		ofstream outFile(filePath);

		// let's make sure the file got opened
		if (outFile.is_open())
		{
			// number of empty buckets, total count of elements, index of emptiest bucket, index of fullest bucket
			unsigned int empty = 0;
			unsigned int totalCount = 0;
			unsigned int loIndex = 0;
			unsigned int hiIndex = 0;

			// loop through all the buckets
			for (unsigned int i = 0; i < buckets; ++i)
			{
				// add the number of elements in each bucket to the total count
				totalCount += HashTable[i].size();
				// print the index of this bucket and its size to the file
				outFile << i << " : " << HashTable[i].size() << '\n';

				// if this list is empty, increment the empty count
				if (HashTable[i].size() == 0)
					++empty;

				// if this list has less elements than the lowest one recorded so far, store this as the new lowest
				if (HashTable[i].size() < HashTable[loIndex].size())
					loIndex = i;
				// else, if this list has more elements than the highest one recorded so far, store this as the new highest
				else if (HashTable[i].size() > HashTable[hiIndex].size())
					hiIndex = i;
			}

			// print the total count of items and number of buckets to the file
			outFile << '\n' << totalCount << " Total items stored in " << buckets << " buckets\n";
			// print the number of empty buckets
			outFile << '\n' << empty << " Buckets are empty\n\n";
			// get the number of elements in the emptiest bucket
			unsigned int Low = HashTable[loIndex].size();
			// get the range fullest-emptiest+1
			unsigned int range = HashTable[hiIndex].size() - Low + 1;
			// print this info to the file
			outFile << "each bucket contains between " << Low << " and " << Low + range - 1 << " items.\n\n";

			// make a new array to count how many buckets contain each number of items between the emptiest and fullest
			// and initialize each cell to 0
			unsigned int* arr = new unsigned int[range];
			for (unsigned int j = 0; j < range; ++j)
				arr[j] = 0;

			// now we go through and count how many buckets contain each number of items...
			// 3 buckets have 15 items
			// 5 buckets have 16 items
			// etc.
			for (unsigned int k = 0; k < buckets; ++k)
				++arr[HashTable[k].size() - Low];

			// now print this data to the file
			for (unsigned int p = 0; p < range; ++p)
				outFile << arr[p] << " buckets have " << p + Low << " items\n";

			// delete the array we made a minute ago, we are done with it
			delete[] arr;
		}
	}
};