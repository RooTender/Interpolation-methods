#pragma once
#include "Matrix.h"

class Matrix1d final : public Matrix
{
public:
	long double* matrix;

	explicit Matrix1d(int n);
	Matrix1d(const Matrix1d& matrix);
	Matrix1d(const long double* arr, int n);

	Matrix1d(Matrix1d&&) = delete;

	void Fill(long double value) override;

	[[nodiscard]] int IndexOfMax() const;
	[[nodiscard]] Matrix1d Abs() const;
	[[nodiscard]] Matrix1d Trunc(int from, int to) const;

	Matrix1d& operator=(const Matrix1d& matrix);
	Matrix1d& operator=(Matrix1d&& matrix) noexcept;
	Matrix1d operator-(const Matrix1d& matrix) const;

	~Matrix1d() override;
};
