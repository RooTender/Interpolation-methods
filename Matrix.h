#pragma once

class Matrix
{
protected:
	Matrix() = default;
	~Matrix() = default;

public:
	int rows = 0;
	int cols = 0;

	Matrix(const Matrix&) = delete;
	Matrix& operator=(Matrix&&) = default;
	Matrix& operator=(const Matrix& other) = default;
	Matrix(Matrix&&) = delete;

	virtual int Size();
	[[nodiscard]] virtual int Size() const;
	virtual void Fill(long double value) = 0;
};
