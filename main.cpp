#include <iostream>
#include "Loader.h"
#include "MatrixAlgs.h"


int main() {
	Loader loader = Loader("input");
	
	Point* points;
	size_t pointsCount;

	pointsCount = loader.load(points, loader.getPaths()[0]);
	Matrix1d matrix = MatrixAlgs::lagrangeInterpolation(points, pointsCount);

	loader.unload(matrix, "out", loader.getPaths()[0]);

	return 0;
}
