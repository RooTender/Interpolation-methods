#pragma once

class Matrix
{
public:
	size_t rows = 0;
	size_t cols = 0;

	Matrix() = default;
	Matrix(const Matrix&) = delete;
	Matrix& operator=(Matrix&&) = default;
	Matrix& operator=(const Matrix& other) = default;
	Matrix(Matrix&&) = default;

	virtual size_t Size();
	[[nodiscard]] virtual size_t Size() const;
	virtual void Fill(long double value) = 0;

	virtual ~Matrix() = default;
};
