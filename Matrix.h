#pragma once
#include <math.h>

class Matrix
{
protected:
	Matrix() {};

public:
	size_t rows = 0;
	size_t cols = 0;

	virtual size_t size();
	virtual size_t size() const;
	virtual void fill(long double value) = 0;
};

