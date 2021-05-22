#include <iostream>
#include "Loader.h"
#include "MatrixAlgs.h"


int main() {
	Loader loader = Loader("input");
	
	Point* points;
	size_t pointsCount;

	pointsCount = loader.load(points, loader.getPaths()[0]);
}
