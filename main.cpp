#include <iostream>
#include "Loader.h"
#include "MatrixAlgs.h"


int main() {
	Loader loader = Loader("input", "output");

	int limit, lagrangeInterval, splineInterval;
	std::cout << "Lagrange interpolation max points (15 recommended): ";
	std::cin >> limit;

	std::cout << "Distance between points for interval lagrange: ";
	std::cin >> lagrangeInterval;

	std::cout << "Distance between points for interval spline: ";
	std::cin >> splineInterval;

	std::cout << std::endl;


	for (const auto& path : loader.getPaths()) {
		std::cout << "Processing " << path << "..." << std::endl;

		PointArray points = loader.load(path);
		Matrix1d fullSplineMatrix = MatrixAlgs::splineInterpolation(points);

		// Truncated array for optimal results (avoiding factors underflows)
		PointArray truncatedPoints = points.trunc(0, limit);
		Matrix1d lagrangeMatrix = MatrixAlgs::lagrangeInterpolation(truncatedPoints);
		Matrix1d splineMatrix = MatrixAlgs::splineInterpolation(truncatedPoints);

		PointArray noMiddlePointsLagrange = truncatedPoints.removeMidpoints(lagrangeInterval);
		Matrix1d intervalLagrangeMatrix = MatrixAlgs::lagrangeInterpolation(noMiddlePointsLagrange);

		PointArray noMiddlePointsSpline = points.removeMidpoints(splineInterval);
		Matrix1d intervalSplineMatrix = MatrixAlgs::splineInterpolation(noMiddlePointsSpline);

		loader.updateFunctionsDatabase(path);
		loader.unload(truncatedPoints, lagrangeMatrix, "lagrange", path);
		loader.unload(truncatedPoints, splineMatrix, "spline", path);
		loader.unload(noMiddlePointsLagrange, intervalLagrangeMatrix, "interval_lagrange", path);
		loader.unload(noMiddlePointsSpline, intervalSplineMatrix, "interval_spline", path);
		loader.unload(points, fullSplineMatrix, "full_spline", path);
	}
	std::cout << "Done!" << std::endl;

	return 0;
}
