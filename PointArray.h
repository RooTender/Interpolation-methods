#pragma once
#include "Point.h"

class PointArray
{
private:
	int length;

public:
	Point* arr;

	PointArray(int n);
	PointArray(const PointArray& pointArray);
	
	int getLength() const;
	PointArray trunc(int begin, int end);
	PointArray removeMidpoints(int amount);

	~PointArray();
};

