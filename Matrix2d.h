#pragma once
#include "Matrix.h"
#include "Matrix1d.h"

class Matrix2d : public Matrix
{
public:
	long double** matrix;

	Matrix2d(size_t n);
	Matrix2d(const Matrix2d& M);

	void fill(long double value) override;

	bool hasNullOnDiagonal() const;
	Matrix2d toIdentity() const;
	Matrix2d transpose();
	Matrix1d column(int index);
	Matrix1d row(int index);

	void swapColumns(int row1, int row2, size_t from, size_t to);
	void swapRows(int col1, int col2, size_t from, size_t to);

	Matrix2d operator= (const Matrix2d& M);
	Matrix1d operator* (const Matrix1d& M) const;

	~Matrix2d();
};