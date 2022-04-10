#include "Matrix1d.h"

#include <algorithm>
#include <corecrt_math.h>

Matrix1d::Matrix1d(const size_t n) : matrix(new long double[n])
{
	this->rows = 1;
	this->cols = n;
}

Matrix1d::Matrix1d(const Matrix1d& matrix) : Matrix1d(matrix.Size())
{
	for (size_t i = 0; i < this->Matrix::Size(); ++i)
	{
		this->matrix[i] = matrix.matrix[i];
	}
}

Matrix1d::Matrix1d(const long double* arr, const size_t n) : Matrix1d(n)
{
	for (size_t i = 0; i < n; ++i)
	{
		matrix[i] = arr[i];
	}
}

void Matrix1d::Fill(const long double value)
{
	for (size_t i = 0; i < this->cols; ++i)
	{
		this->matrix[i] = value;
	}
}

Matrix1d Matrix1d::Abs() const
{
	const auto matrix1d = Matrix1d(*this);
	for (size_t i = 0; i < this->cols; ++i)
	{
		matrix1d.matrix[i] = fabsl(matrix1d.matrix[i]);
	}

	return Matrix1d{matrix1d};
}

Matrix1d Matrix1d::Trunc(const unsigned from, const unsigned to) const
{
	const auto matrix1d = Matrix1d(to - from);
	for (size_t i = from; i < to; ++i)
	{
		matrix1d.matrix[i - from] = this->matrix[i];
	}

	return Matrix1d{matrix1d};
}

/**
 * Find maximum value in matrix and return index of it.
 *
 * @return index of maximum value in matrix.
 */
unsigned Matrix1d::IndexOfMax() const
{
	unsigned index = 0;
	for (size_t i = 1; i < this->cols; ++i)
	{
		if (this->matrix[i] > this->matrix[index])
		{
			index = i;
		}
	}

	return index;
}

Matrix1d& Matrix1d::operator=(const Matrix1d& matrix)
{
	if (this == &matrix)
	{
		return *this;
	}

	delete[] this->matrix;

	this->rows = matrix.rows;
	this->cols = matrix.cols;
	this->matrix = new long double[matrix.Size()];

	std::copy_n(matrix.matrix, matrix.Size(), this->matrix);
	
	return *this;
}

Matrix1d& Matrix1d::operator=(Matrix1d&& matrix1d) noexcept
{
	std::swap(this->cols, matrix1d.cols);
	std::swap(this->rows, matrix1d.rows);
	std::swap(this->matrix, matrix1d.matrix);

	return *this;
}

Matrix1d Matrix1d::operator-(const Matrix1d& matrix1d) const
{
	const auto result = Matrix1d(*this);
	for (size_t i = 0; i < this->Size(); ++i)
	{
		result.matrix[i] = this->matrix[i] - matrix1d.matrix[i];
	}

	return Matrix1d{result};
}

Matrix1d::~Matrix1d()
{
	delete[] matrix;
}
