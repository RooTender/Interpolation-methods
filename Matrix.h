#pragma once
#include <math.h>

class Matrix
{
protected:
	Matrix()
	{
	};

public:
	int rows = 0;
	int cols = 0;

	virtual int size();
	virtual int size() const;
	virtual void fill(long double value) = 0;
};
