#pragma once
#include "Matrix.h"
#include "Matrix1d.h"

class Matrix2d final : public Matrix
{
public:
	long double** matrix;

	explicit Matrix2d(size_t n);
	Matrix2d(const Matrix2d& matrix);
	Matrix2d(Matrix2d&& matrix2d) noexcept;

	void Fill(long double value) override;

	[[nodiscard]] bool HasNullOnDiagonal() const;
	[[nodiscard]] Matrix2d ToIdentity() const;
	[[nodiscard]] Matrix2d Transpose() const;
	[[nodiscard]] Matrix1d Column(unsigned index) const;
	[[nodiscard]] Matrix1d Row(unsigned index) const;

	void SwapColumns(unsigned row1, unsigned row2, unsigned from, unsigned to) const;
	void SwapRows(unsigned col1, unsigned col2, unsigned from, unsigned to) const;

	Matrix2d& operator=(const Matrix2d& matrix2d);
	Matrix2d& operator=(Matrix2d&& matrix2d) noexcept;
	Matrix1d operator*(const Matrix1d& matrix1d) const;

	~Matrix2d() override;
};
