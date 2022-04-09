#include <iostream>
#include "Loader.h"
#include "MatrixAlgs.h"


int main()
{
	auto loader = Loader("input", "output");

	int limit, lagrangeInterval, splineInterval;
	std::cout << "Lagrange interpolation max points (15 recommended): ";
	std::cin >> limit;

	std::cout << "Distance between points for interval lagrange: ";
	std::cin >> lagrangeInterval;

	std::cout << "Distance between points for interval spline: ";
	std::cin >> splineInterval;

	std::cout << std::endl;


	for (const auto& path : loader.GetPaths())
	{
		std::cout << "Processing " << path << "..." << std::endl;

		PointArray points = loader.Load(path);
		Matrix1d fullSplineMatrix = MatrixAlgs::splineInterpolation(points);

		// Truncated array for optimal results (avoiding factors underflow)
		PointArray truncatedPoints = points.trunc(0, limit);
		Matrix1d lagrangeMatrix = MatrixAlgs::lagrangeInterpolation(truncatedPoints);
		Matrix1d splineMatrix = MatrixAlgs::splineInterpolation(truncatedPoints);

		PointArray noMiddlePointsLagrange = truncatedPoints.removeMidpoints(lagrangeInterval);
		Matrix1d intervalLagrangeMatrix = MatrixAlgs::lagrangeInterpolation(noMiddlePointsLagrange);

		PointArray noMiddlePointsSpline = points.removeMidpoints(splineInterval);
		Matrix1d intervalSplineMatrix = MatrixAlgs::splineInterpolation(noMiddlePointsSpline);

		loader.UpdateFunctionsDatabase(path);
		loader.Unload(truncatedPoints, lagrangeMatrix, "lagrange", path);
		loader.Unload(truncatedPoints, splineMatrix, "spline", path);
		loader.Unload(noMiddlePointsLagrange, intervalLagrangeMatrix, "interval_lagrange", path);
		loader.Unload(noMiddlePointsSpline, intervalSplineMatrix, "interval_spline", path);
		loader.Unload(points, fullSplineMatrix, "full_spline", path);
	}
	std::cout << "Done!" << std::endl;

	return 0;
}
