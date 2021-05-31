#pragma once
#include "Point.h"

class PointArray
{
private:
	size_t length;

public:
	Point* arr;

	PointArray(size_t n);
	PointArray(const PointArray& pointArray);
	
	size_t getLength() const;
	PointArray trunc(size_t begin, size_t end);

	~PointArray();
};

