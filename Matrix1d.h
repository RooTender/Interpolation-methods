#pragma once
#include "Matrix.h"

class Matrix1d : public Matrix
{
public:
	long double* matrix;

	Matrix1d(int n);
	Matrix1d(const Matrix1d& M);
	Matrix1d(long double* arr, int n);

	void fill(long double value) override;

	int indexOf_max();
	Matrix1d abs();
	Matrix1d trunc(int from, int to);

	Matrix1d operator= (const Matrix1d& M);
	Matrix1d operator- (const Matrix1d& M) const;

	~Matrix1d();
};