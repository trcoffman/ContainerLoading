#pragma once
#include <list>
#include <iostream>
#include <stdexcept>
using namespace std;

class BoxException : public logic_error
{
public:
	BoxException();
	BoxException(int x);

	const static int NegativeLoad = 0;
};

class BoxData
{

	int seqNum;
	double load;
	list<double> loads;

public:
	BoxData();
	BoxData(int);

	int getSeqNum() const;

	list<double> getLoads() const;
	void addLoad(const double& _load);
	double getLoad() const;
	bool willFill(const double& _load) const;
	bool willFit(const double& _load) const;
	bool isFull() const;

	bool operator < (const BoxData&) const;
	bool operator <= (const BoxData&) const;
	bool operator > (const BoxData&) const;
	bool operator >= (const BoxData&) const;
};

class BoxPointerLoadGreater
{
public:
	bool operator () (BoxData* x, BoxData* y);
};



ostream & operator << (ostream& os, const BoxData& box);

