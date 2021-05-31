#include "PointArray.h"

PointArray::PointArray(size_t n)
{
	this->length = n;
	this->arr = new Point[n];
}

PointArray::PointArray(const PointArray& pointArray) : PointArray(pointArray.getLength())
{
	for (size_t i = 0; i < this->length; ++i) {
		this->arr[i] = pointArray.arr[i];
	}
}

PointArray::~PointArray()
{
	delete arr;
}

size_t PointArray::getLength() const
{
	return this->length;
}

PointArray PointArray::trunc(size_t begin, size_t end)
{
	PointArray truncatedArray = PointArray(end - begin);
	for (int i = begin; i < end; ++i) {
		truncatedArray.arr[i - begin] = this->arr[i];
	}

	return truncatedArray;
}
