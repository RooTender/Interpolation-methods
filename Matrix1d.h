#pragma once
#include "Matrix.h"

class Matrix1d final : public Matrix
{
public:
	long double* matrix;

	explicit Matrix1d(size_t n);
	Matrix1d(const Matrix1d& matrix);
	Matrix1d(const long double* arr, size_t n);

	Matrix1d(Matrix1d&&) = delete;

	void Fill(long double value) override;

	[[nodiscard]] unsigned IndexOfMax() const;
	[[nodiscard]] Matrix1d Abs() const;
	[[nodiscard]] Matrix1d Trunc(unsigned from, unsigned to) const;

	Matrix1d& operator=(const Matrix1d& matrix1d);
	Matrix1d& operator=(Matrix1d&& matrix1d) noexcept;
	Matrix1d operator-(const Matrix1d& matrix1d) const;

	~Matrix1d() override;
};
