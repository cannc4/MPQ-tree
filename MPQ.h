/*
Can Ince
14241
Homework 4 - MPQ
*/


#ifndef _MPQ_H
#define _MPQ_H

#include <vector>
using namespace std;

template <class Comparable>
class MPQ
{
    public:

	MPQ(int inputSize, Comparable initial); //Parametrized Constructor
	~MPQ();//destructor
    bool IsEmpty() const; //checks if the heap is empty
	bool IsFull() const; //checks if the heap is full
    Comparable GetMax(); //Returns the maximum value in HeapArray
    void insert(  const int & label,  Comparable  value); //inserts a new entry.
	Comparable Remove(int label); //Removes the element with specified label
	

    private:

	struct MPQ_Obj 
	{
		Comparable value;
		int label;
		MPQ_Obj(Comparable value, int label) : value(value), label(label)
		{}
	};
    int currentSize; // Number of elements currently in the heap
	int *Location;// Dynamic ocation array
    vector<MPQ_Obj> HeapArray; // The heap array of structs
	
	

};



template <class Comparable>
MPQ<Comparable>::~MPQ() //Default Destructor
{ }

template <class Comparable>
MPQ<Comparable>::MPQ(int inputSize, Comparable initial)
{
	currentSize = 0;
	
	//initialize heap vector
	for (int i = 0; i < inputSize + 1; i++)
	{
		MPQ_Obj temp(initial, 0);
		HeapArray.push_back(temp);
	}
	//initialize location array
	Location = new int[inputSize + 1];
}

// Returns true if Empty
template <class Comparable>
bool MPQ<Comparable>::IsEmpty() const
{
	return currentSize == 0 ? true: false;
}

// Returns true if Full
template <class Comparable>
bool MPQ<Comparable>::IsFull() const
{
	return currentSize == HeapArray.size() ? true: false;
}

//the item with the max. value is stored at the beginning of the heap
template <class Comparable>
Comparable MPQ<Comparable>::GetMax()
{
	return HeapArray[1].value;
}
// Insertion by moving the hole up and updating location array at the same time.
template <class Comparable>
void MPQ<Comparable>::insert(const int & label, const Comparable value)
{
	if(IsFull())
		throw "Full";

	// Percolate up, instead of swap we move the hole up
	int hole = ++currentSize;
    for( ; hole > 1 && value > HeapArray[hole/2].value ; hole /= 2 )
	{
        HeapArray[hole] = HeapArray[hole/2];
		Location[HeapArray[hole/2].label] = hole; //update location array
	}
	MPQ_Obj temp(value, label);
	Location[label] = hole;
    HeapArray[hole] = temp;
	
}

template <class Comparable>
Comparable MPQ<Comparable>::Remove(int label)
{
	int hole = Location[label];
	Comparable removedEntry = HeapArray[hole].value;

	//Replace the deleted index 
	HeapArray[hole] = HeapArray[currentSize--];
	Location[HeapArray[hole].label] = hole;

	//Percolate down function
	int child;
	MPQ_Obj temp = HeapArray[hole];

	for( ; hole * 2 <= currentSize; hole = child )
	{
		child = hole * 2;
		if( child != currentSize && HeapArray[child + 1].value > HeapArray[child].value)
			child++;
		if( HeapArray[child].value > temp.value )
		{
			HeapArray[hole] = HeapArray[child];
			Location[HeapArray[hole].label] = hole; 
		}
		else
			break;
	}
	HeapArray[hole] = temp;
	Location[HeapArray[hole].label] = hole;

	return removedEntry;
}


#endif