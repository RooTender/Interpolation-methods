#include <iostream>
#include "Loader.h"
#include "MatrixAlgorithms.h"


int main()
{
	auto loader = Loader("input", "output");

	int limit, lagrangeInterval, splineInterval;
	std::cout << "Lagrange interpolation max points (15 recommended): ";
	std::cin >> limit;

	std::cout << "Distance between points for interval lagrange: ";
	std::cin >> lagrangeInterval;

	if (limit < lagrangeInterval)
	{
		throw std::runtime_error("Distance cannot be greater than maximum!");
	}

	std::cout << "Distance between points for interval spline: ";
	std::cin >> splineInterval;

	std::cout << std::endl;


	for (const auto& path : loader.GetPaths())
	{
		std::cout << "Processing " << path << "..." << std::endl;

		PointArray points = loader.Load(path);
		Matrix1d fullSplineMatrix = MatrixAlgorithms::SplineInterpolation(points);

		// Truncated array for optimal results (avoiding factors underflow)
		PointArray truncatedPoints = points.Trunc(0, limit);
		Matrix1d lagrangeMatrix = MatrixAlgorithms::LagrangeInterpolation(truncatedPoints);
		Matrix1d splineMatrix = MatrixAlgorithms::SplineInterpolation(truncatedPoints);

		PointArray noMiddlePointsLagrange = truncatedPoints.RemoveMidpoints(lagrangeInterval);
		Matrix1d intervalLagrangeMatrix = MatrixAlgorithms::LagrangeInterpolation(noMiddlePointsLagrange);

		PointArray noMiddlePointsSpline = points.RemoveMidpoints(splineInterval);
		Matrix1d intervalSplineMatrix = MatrixAlgorithms::SplineInterpolation(noMiddlePointsSpline);

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
