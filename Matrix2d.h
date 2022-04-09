#pragma once
#include "Matrix.h"
#include "Matrix1d.h"

class Matrix2d final : public Matrix
{
public:
	long double** matrix;

	explicit Matrix2d(int n);
	Matrix2d(const Matrix2d& matrix);
	Matrix2d(Matrix2d&& matrix2d) noexcept;

	void Fill(long double value) override;

	[[nodiscard]] bool HasNullOnDiagonal() const;
	[[nodiscard]] Matrix2d ToIdentity() const;
	[[nodiscard]] Matrix2d Transpose() const;
	[[nodiscard]] Matrix1d Column(int index) const;
	[[nodiscard]] Matrix1d Row(int index) const;

	void SwapColumns(int row1, int row2, int from, int to) const;
	void SwapRows(int col1, int col2, int from, int to) const;

	Matrix2d& operator=(const Matrix2d& matrix2d);
	Matrix2d& operator=(Matrix2d&& matrix2d) noexcept;
	Matrix1d operator*(const Matrix1d& matrix1d) const;

	~Matrix2d() override;
};
