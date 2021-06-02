#include "PointArray.h"

PointArray::PointArray(int n)
{
	this->length = n;
	this->arr = new Point[n];
}

PointArray::PointArray(const PointArray& pointArray) : PointArray(pointArray.getLength())
{
	for (int i = 0; i < this->length; ++i) {
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
	PointArray truncatedArray = PointArray(end - begin);
	for (int i = begin; i < end; ++i) {
		truncatedArray.arr[i - begin] = this->arr[i];
	}

	return truncatedArray;
}
