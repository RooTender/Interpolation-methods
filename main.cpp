#include <iostream>
#include "Loader.h"
#include "MatrixAlgs.h"


int main() {
	Loader loader = Loader("input", "output");

	int limit, interval;
	std::cout << "Lagrange interpolation max points (15 recommended): ";
	std::cin >> limit;

	std::cout << "Distance between points for interval spline: ";
	std::cin >> interval;

	std::cout << std::endl;

	for (const auto& path : loader.getPaths()) {
		std::cout << "Processing " << path << "..." << std::endl;

		PointArray points = loader.load(path);
		Matrix1d fullSplineMatrix = MatrixAlgs::splineInterpolation(points);

		// Truncated array for optimal results (avoiding factors underflows)
		PointArray truncatedPoints = points.trunc(0, limit);
		Matrix1d lagrangeMatrix = MatrixAlgs::lagrangeInterpolation(truncatedPoints);
		Matrix1d splineMatrix = MatrixAlgs::splineInterpolation(truncatedPoints);

		PointArray noMiddlePoints = points.removeMidpoints(interval);
		Matrix1d intervalSplineMatrix = MatrixAlgs::splineInterpolation(noMiddlePoints);

		loader.updateFunctionsDatabase(path);
		loader.unload(truncatedPoints, lagrangeMatrix, "lagrange", path);
		loader.unload(truncatedPoints, splineMatrix, "spline", path);
		loader.unload(noMiddlePoints, intervalSplineMatrix, "interval_spline", path);
		loader.unload(points, fullSplineMatrix, "full_spline", path);
	}
	std::cout << "Done!" << std::endl;

	return 0;
}
