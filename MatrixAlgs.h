#pragma once
#include <math.h>
#include "Matrix2d.h"
#include "Matrix1d.h"

namespace MatrixAlgs
{
	long double norm(const Matrix1d& res);
	long double jacobi(const Matrix2d& A, Matrix1d& x, const Matrix1d& b, long double limit, int& iterations);
	long double gaussSeidl(const Matrix2d& A, Matrix1d& x, const Matrix1d& b, long double limit, int& iterations);
	long double LUDecomposition(const Matrix2d& A, Matrix1d& x, const Matrix1d& b);
};

