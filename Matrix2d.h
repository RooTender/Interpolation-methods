#pragma once
#include "Matrix.h"
#include "Matrix1d.h"

class Matrix2d : public Matrix
{
public:
	long double** matrix;

	Matrix2d(int n);
	Matrix2d(const Matrix2d& M);

	void fill(long double value) override;

	bool hasNullOnDiagonal();
	Matrix2d toIdentity() const;
	Matrix2d transpose();

	Matrix2d operator= (const Matrix2d& M);
	Matrix1d operator* (const Matrix1d& M) const;

	~Matrix2d();
};