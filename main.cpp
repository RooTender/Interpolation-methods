#include <iostream>
#include "Loader.h"
#include "MatrixAlgs.h"


int main() {
	Loader loader = Loader("input", "output");
	PointArray points = loader.load(loader.getPaths()[0]);

	// Truncated array for optimal results (avoiding factors underflows)
	PointArray lagrangePoints = points.trunc(0, 20);
	Matrix1d matrix = MatrixAlgs::lagrangeInterpolation(lagrangePoints);

	Matrix1d** splines = nullptr;
	MatrixAlgs::splineInterpolation(points, splines);

	loader.unload(matrix, lagrangePoints, splines, points, loader.getPaths()[0]);

	for (int i = 0; i < points.getLength() - 2; ++i) {
		delete splines[i];
	}
	delete[] splines;

	return 0;
}
