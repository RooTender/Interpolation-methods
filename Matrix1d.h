#pragma once
#include "Matrix.h"
class Matrix1d : public Matrix
{
public:
	long double* matrix;

	Matrix1d(int n);
	Matrix1d(const Matrix1d& M);

	void fill(long double value) override;

	Matrix1d operator= (const Matrix1d& M);
	Matrix1d operator- (const Matrix1d& M) const;

	~Matrix1d();
};