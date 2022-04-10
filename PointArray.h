#pragma once
#include "Point.h"

class PointArray
{
	size_t length;

public:
	Point* arr;

	explicit PointArray(size_t n);
	PointArray(const PointArray& pointArray);
	PointArray(PointArray&& pointArray) noexcept;
	PointArray& operator=(const PointArray& pointArray);
	PointArray& operator=(PointArray&& pointArray) noexcept;

	[[nodiscard]] size_t GetAmount() const;
	[[nodiscard]] PointArray Trunc(unsigned begin, unsigned end) const;
	[[nodiscard]] PointArray RemoveMidpoints(unsigned amount) const;

	~PointArray();
};
