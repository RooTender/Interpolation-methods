#pragma once
struct Point
{
	long double x = 0, y = 0;

	Point() = default;
	Point(const long double x, const long double y) : x(x), y(y)
	{
	}
};
