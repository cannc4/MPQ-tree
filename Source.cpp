/*
Can Ince
14241
Homework 4 - MPQ
*/

#include <iostream>
#include <fstream>
#include <string>
#include "MPQ.h"
#include <sstream>

using namespace std;

struct Sky_Line 
{
	int xVal; //actual x value
	int label; // number of the building
	bool side; // 1 for left , 0 for right
	
	//Constructor
	Sky_Line()	{}
	Sky_Line(int x, int label, bool side)
		:xVal(x), label(label), side(side)	{}

};

// Merge sort functions
template <class Comparable>
void merge( vector<Comparable> & a, vector<Comparable> & tempArray,int leftPos, int rightPos, int rightEnd )
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;
	while( leftPos <= leftEnd && rightPos <= rightEnd )
		if( a[ leftPos ].xVal <= a[ rightPos ].xVal )
			tempArray[ tmpPos++ ] = a[ leftPos++ ];
		else
			tempArray[ tmpPos++ ] = a[ rightPos++ ];


	// Copy the left side
	while( leftPos <= leftEnd )    
		tempArray[ tmpPos++ ] = a[ leftPos++ ];

	 // Copy the right side
	while( rightPos <= rightEnd ) 
		tempArray[ tmpPos++ ] = a[ rightPos++ ];

	// Copy array back to original array
	for( int i = 0; i < numElements; i++, rightEnd-- )
		a[ rightEnd ] = tempArray[ rightEnd ];
}
template <class Comparable>
void mergeSort( vector<Comparable> & a, vector<Comparable> & tempArray, int left, int right )
{
	if( left < right )
	{
		int center = ( left + right ) / 2;
		mergeSort( a, tempArray, left, center );
		mergeSort( a, tempArray, center + 1, right );
		merge( a, tempArray, left, center + 1, right );
	}
}
template <class Comparable>
void mergeSort( vector<Comparable> & a )
{
	vector<Comparable> tempArray( a.size( ) );
	mergeSort( a, tempArray, 1, a.size( ) - 1 );
}

int main()
{
	ifstream input("input.txt");

	if (input.fail())
	{
		cout << "Wrong input file, exiting..." << endl;
		return 0;
	}
	//Reading the number of buildings
	int buildingNumber;
	string line;
	getline(input, line);
	istringstream iss1(line);
	iss1 >> buildingNumber;

	MPQ<int> Skyline(buildingNumber+1, 0);
	vector <Sky_Line> x;	// vector containing building's X coords, side and label.
	vector <int > y;		// vector containing building's Y coords.


	//Reading coordinates
	string line2;
	int i = 0;
	while(getline(input, line2))
	{
		int x1, x2,y1;
		istringstream iss(line2);
		iss >> x1 >> y1>> x2;
		y.push_back(y1);
		x.push_back(Sky_Line(x1, i,true));
		x.push_back(Sky_Line(x2, i,false));
		i++;
	}


	mergeSort(x);
	//X coords are now sorted

	ofstream output("output.txt");
	if (x[0].xVal != 0){
		output << 0 <<" " << 0 << endl;}

	int currentMax = 0;
	int currentX;
	int j=0;
	while( j < 2 * buildingNumber )
	{
		currentX = x[j].xVal;
		while (j < 2 * buildingNumber && currentX == x[j].xVal) //proccesing values
		{
			if (x[j].side == true)// If the side is true then the building can be added to the MPQ
				Skyline.insert(x[j].label,y[x[j].label] );
			
			else{ //Else the side is false, it means the building is on the right side 
			
				Skyline.Remove(x[j].label);
			}
			j++;
			
		}
		if (Skyline.IsEmpty()) // there remains no buildings in MPQ for the current point x
		{
			output << x[j-1].xVal << " " << 0 << endl;
			currentMax = 0;
		}
		else
		{
			int height = Skyline.GetMax();
			if  (height != currentMax){ //if the maximum height changes-> output
					
				//set max height to its new value
				currentMax = height;
				output << x[j-1].xVal << " " << currentMax << endl;

			}
		}
	}
	cout << "Output file is ready -> 'output.txt '" << endl;
	cin.get();
	cin.ignore();
	system("Pause");
	return 0;
	}
