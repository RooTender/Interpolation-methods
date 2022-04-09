#pragma once
struct Point
{
	Point()
	{
	}

	Point(long double x, long double y)
	{
		this->x = x;
		this->y = y;
	}

	long double x = 0, y = 0;
};
