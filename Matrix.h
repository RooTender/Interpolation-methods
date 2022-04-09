#pragma once

class Matrix
{
public:
	int rows = 0;
	int cols = 0;

	Matrix() = default;
	Matrix(const Matrix&) = delete;
	Matrix& operator=(Matrix&&) = default;
	Matrix& operator=(const Matrix& other) = default;
	Matrix(Matrix&&) = default;

	virtual int Size();
	[[nodiscard]] virtual int Size() const;
	virtual void Fill(long double value) = 0;

	virtual ~Matrix() = default;
};
