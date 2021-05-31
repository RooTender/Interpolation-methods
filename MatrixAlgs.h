#pragma once
#include <math.h>
#include "Matrix2d.h"
#include "Matrix1d.h"
#include "PointArray.h"

namespace MatrixAlgs
{
	long double norm(const Matrix1d& res);
	long double jacobi(const Matrix2d& A, Matrix1d& x, const Matrix1d& b, long double limit, int& iterations);
	long double gaussSeidl(const Matrix2d& A, Matrix1d& x, const Matrix1d& b, long double limit, int& iterations);
	long double LUDecomposition(const Matrix2d& A, Matrix1d& x, Matrix1d b);
	Matrix1d multiplyPolynomials(const Matrix1d& A, const Matrix1d& B);
	Matrix1d lagrangeInterpolation(const PointArray& points);
};

