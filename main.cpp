/**********************************************

Tyler Coffman
Topic E Project
Fall 2011.

Program Status

My program works as intended!

Gives the same output as the given specification
program.

***********************************************/

#include <iostream>
#include <fstream>
#include <queue>
#include <list>
#include <vector>
#include <string>
#include "PriorityQueue.h"
#include "BoxData.h"
using namespace std;

const int initial_box_count = 80;


void processLoad(const double& load,
	BoxData*& boxes,
	const int& max_boxes,
	PriorityQueue<BoxData*, BoxPointerLoadGreater>& boxesNotFull, 
	list<BoxData*>& boxesTooFull,
	list<BoxData*>& fullBoxes,
	int& numBoxes);

ostream& operator << (ostream& os, const list<double>& q);
ostream& operator << (ostream& os, const list<BoxData*>& q);

void readFile(list<double>& loads);

int main()
{
	list<double> loads;
	BoxData* boxes;
	int max_boxes;
	PriorityQueue<BoxData*, BoxPointerLoadGreater> boxesNotFull;
	list<BoxData*> boxesTooFull;
	list<BoxData*> fullBoxes;
	double load;
	int numBoxes = 0;
	int numLoads;

	//read input from file
	readFile(loads);
	numLoads = loads.size();

	//Display the data entered
	cout << "Data entered is:\n" << loads << endl;
	cout << numLoads << " is the total number of data items\n\n";

	//create boxes!
	max_boxes = numLoads;
	boxes = new BoxData[max_boxes];
	for(; numBoxes < initial_box_count; numBoxes++)
	{
		boxes[numBoxes] = BoxData(numBoxes);
		boxesNotFull.push(&boxes[numBoxes]);
	}

	//Now we actually process all the loads and
	//put them into boxes
	while( loads.size() > 0 )
	{
		load = loads.front();
		loads.pop_front();
		processLoad(load,boxes,max_boxes,boxesNotFull,boxesTooFull,fullBoxes,numBoxes);
	}

	//display
	cout << "Boxes which are considered to be full:\n" << fullBoxes;
	cout << "\nThere are " << fullBoxes.size() 
		 << " boxes considered to be full\n\n";
	cout << "Boxes still in the heap:\n";

	//display the heap

	int numBoxesOnHeap = 1;
	while(!boxesNotFull.empty())
	{
		cout << numBoxesOnHeap++ << ".  " << *boxesNotFull.top() << " ";
		boxesNotFull.pop();
	}
	numBoxesOnHeap--;

	//display
	cout << "\nThere are " << numBoxesOnHeap << " boxes in the heap\n\n";
	cout << fullBoxes.size() + numBoxesOnHeap << " is the total number of boxes\n";
	cout << numLoads << " is the total number of items\n\nProgram Over\n\n";
	cout << "Press Enter to end -->";
	cin.ignore(80, '\n');

	return 0;
};


//This function adds a load into a box

void processLoad(const double& load,
	BoxData*& boxes,
	const int& max_boxes,
	PriorityQueue<BoxData*, BoxPointerLoadGreater>& boxesNotFull, 
	list<BoxData*>& boxesTooFull,
	list<BoxData*>& fullBoxes,
	int& numBoxes)
{
	BoxData* box;
	bool loadProcessed = false;
	while(!loadProcessed)
	{
		//process the load
		if(boxesNotFull.empty()) //out of boxes!
		{
			if(numBoxes >= max_boxes) //we need to double the capacity of boxes array
			{
				throw logic_error("out of boxes\n");
			}
			boxes[numBoxes] = BoxData(numBoxes); //make a box
			box = &boxes[numBoxes];
			numBoxes++;

			if( box->getSeqNum() < 0 || box->getSeqNum() > numBoxes+1 )
				cout << "Prob 1";
		}
		else //we have more boxes on the queue that aren't full
		{
			box = boxesNotFull.top();
			boxesNotFull.pop();

			if( box->getSeqNum() < 0 || box->getSeqNum() > numBoxes+1 )
				cout << "Prob 2";
		}
		

		if(box->willFit(load)) //load will fit in the box
		{
			box->addLoad(load);
			loadProcessed = true; //load has been added to box
			if(box->isFull())
			{
				fullBoxes.push_back(box); //put it on list of full boxes
			}
			else
			{
				boxesNotFull.push(box); //box still not full, put it back on heap
			}

			//now take all boxes that the load wouldn't fit in
			//and throw them back onto the heap of boxes not full
			while(boxesTooFull.size() > 0)
			{
				boxesNotFull.push(boxesTooFull.front());
				boxesTooFull.pop_front();
			}
		} 
		else //load will not fit into box
		{
			boxesTooFull.push_back(box); //put it in the list of boxes
											//that the load can't fit into
		}
	}
}


void readFile(list<double>& loads)
{
	bool good = true;
	double buffer;
	string filename = "TopicEIn.txt";
	ifstream file(filename.c_str());
	if( !file.is_open() || !file.good() )
		good = false; //the file isn't found, try asking for a different file
	

	while(!good)
	{
		cout << "Please enter a file name for input: ";
		getline(cin, filename, '\n');
		file.open(filename.c_str());
		good = file.is_open();
	}

	while( file >> buffer )
	{
		loads.push_back(buffer);
	}

	file.close();
}

ostream& operator << (ostream& os, const list<double>& q)
{
	for(list<double>::const_iterator it = q.begin(); it != q.end(); ++it)
	{
		os << *it << ' ';
	}
	return os;
}

ostream& operator << (ostream& os, const list<BoxData*>& q)
{
	for(list<BoxData*>::const_iterator it = q.begin(); it != q.end(); ++it)
	{
		os << **it;
	}
	return os;
}
