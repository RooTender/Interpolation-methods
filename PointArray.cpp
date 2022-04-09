#include "PointArray.h"

PointArray::PointArray(int n)
{
	this->length = n;
	this->arr = new Point[n];
}

PointArray::PointArray(const PointArray& pointArray) : PointArray(pointArray.getLength())
{
	for (int i = 0; i < this->length; ++i)
	{
		this->arr[i] = pointArray.arr[i];
	}
}

PointArray::~PointArray()
{
	delete arr;
}

int PointArray::getLength() const
{
	return this->length;
}

PointArray PointArray::trunc(int begin, int end)
{
	auto truncatedArray = PointArray(end - begin);
	for (int i = begin; i < end; ++i)
	{
		truncatedArray.arr[i - begin] = this->arr[i];
	}

	return truncatedArray;
}

PointArray PointArray::removeMidpoints(int amount)
{
	++amount;
	auto noMidpoints = PointArray(this->length / amount + 1);

	int iterator = 0;
	for (int i = 0; i <= this->length / 2; i += amount)
	{
		noMidpoints.arr[iterator] = this->arr[i];
		noMidpoints.arr[noMidpoints.getLength() - 1 - iterator++] = this->arr[this->length - 1 - i];
	}

	return noMidpoints;
}
