#include "PointArray.h"

#include <utility>

PointArray::PointArray(const size_t n) : length(n), arr(new Point[n])
{
}

PointArray::PointArray(const PointArray& pointArray) : PointArray(pointArray.GetAmount())
{
	for (size_t i = 0; i < this->length; ++i)
	{
		this->arr[i] = pointArray.arr[i];
	}
}

PointArray::PointArray(PointArray&& pointArray) noexcept : length(0), arr(new Point[pointArray.length])
{
	std::swap(this->length, pointArray.length);
	std::swap(this->arr, pointArray.arr);
}

PointArray& PointArray::operator=(const PointArray& pointArray)
{
	if (this == &pointArray)
	{
		return *this;
	}

	this->length = pointArray.length;
	this->arr = new Point[this->length];

	for (size_t i = 0; i < this->length; ++i)
	{
		this->arr[i] = pointArray.arr[i];
	}

	return *this;
}

PointArray& PointArray::operator=(PointArray&& pointArray) noexcept
{
	std::swap(this->length, pointArray.length);
	std::swap(this->arr, pointArray.arr);

	return *this;
}

PointArray::~PointArray()
{
	delete[] arr;
}

size_t PointArray::GetAmount() const
{
	return this->length;
}

PointArray PointArray::Trunc(const unsigned begin, const unsigned end) const
{
	auto truncatedArray = PointArray(end - begin);
	for (size_t i = begin; i < end; ++i)
	{
		truncatedArray.arr[i - begin] = this->arr[i];
	}

	return truncatedArray;
}

PointArray PointArray::RemoveMidpoints(unsigned amount) const
{
	++amount;
	auto noMidpoints = PointArray(this->length / amount + 1);

	int iterator = 0;
	for (size_t i = 0; i <= this->length / 2; i += amount)
	{
		noMidpoints.arr[iterator] = this->arr[i];
		noMidpoints.arr[noMidpoints.GetAmount() - 1 - iterator++] = this->arr[this->length - 1 - i];
	}

	return noMidpoints;
}
