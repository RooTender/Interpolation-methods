#include <iostream>
#include "Loader.h"
#include "MatrixAlgs.h"


int main() {
	Loader loader = Loader("input", "output");
	PointArray points = loader.load(loader.getPaths()[0]);

	// Truncated array for optimal results (avoiding factors underflows)
	PointArray lagrangePoints = points.trunc(0, 20);

	Matrix1d matrix = MatrixAlgs::lagrangeInterpolation(lagrangePoints);
	loader.unload(matrix, lagrangePoints, loader.getPaths()[0]);

	return 0;
}
