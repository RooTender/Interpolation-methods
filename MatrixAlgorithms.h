#pragma once
#include "Matrix2d.h"
#include "Matrix1d.h"
#include "PointArray.h"

namespace MatrixAlgorithms
{
	long double Norm(const Matrix1d& res);
	long double Jacobi(const Matrix2d& a, Matrix1d& x, const Matrix1d& b, long double limit, unsigned& iterations);
	long double GaussSeidl(const Matrix2d& a, Matrix1d& x, const Matrix1d& b, long double limit, unsigned& iterations);
	long double LUDecomposition(const Matrix2d& a, Matrix1d& x, Matrix1d b);
	Matrix1d MultiplyPolynomials(const Matrix1d& a, const Matrix1d& b);
	Matrix1d LagrangeInterpolation(const PointArray& points);
	Matrix1d SplineInterpolation(const PointArray& points);
};
