#include "Matrix2d.h"

#include <utility>

Matrix2d::Matrix2d(const size_t n) : matrix(new long double*[n])
{
	this->rows = n;
	this->cols = n;

	for (size_t i = 0; i < n; ++i)
	{
		matrix[i] = new long double[n];
	}
}

Matrix2d::Matrix2d(const Matrix2d& matrix) : Matrix2d(matrix.cols)
{
	for (size_t i = 0; i < this->rows; ++i)
	{
		for (size_t j = 0; j < this->cols; ++j)
		{
			this->matrix[i][j] = matrix.matrix[i][j];
		}
	}
}

Matrix2d::Matrix2d(Matrix2d&& matrix2d) noexcept
{
	const size_t n = matrix2d.cols;

	this->matrix = new long double*[n];
	for (size_t i = 0; i < n; ++i)
	{
		this->matrix[i] = new long double[n];
	}

	std::swap(this->cols, matrix2d.cols);
	std::swap(this->rows, matrix2d.rows);
	std::swap(this->matrix, matrix2d.matrix);
}

void Matrix2d::Fill(const long double value)
{
	for (size_t i = 0; i < this->rows; ++i)
	{
		for (size_t j = 0; j < this->cols; ++j)
		{
			this->matrix[i][j] = value;
		}
	}
}

bool Matrix2d::HasNullOnDiagonal() const
{
	for (size_t i = 0; i < this->cols; ++i)
	{
		if (matrix[i][i] == 0.0)
		{
			return true;
		}
	}

	return false;
}

Matrix2d Matrix2d::ToIdentity() const
{
	const auto identityMatrix = Matrix2d(*this);
	for (size_t i = 0; i < this->rows; ++i)
	{
		for (size_t j = 0; j < this->cols; ++j)
		{
			identityMatrix.matrix[i][j] = (i == j) ? 1 : 0;
		}
	}
	return Matrix2d{identityMatrix};
}

Matrix2d Matrix2d::Transpose() const
{
	const Matrix2d transposedMatrix(*this);

	for (size_t i = 0; i < this->cols; ++i)
	{
		for (size_t j = 0; j < i; ++j)
		{
			std::swap(transposedMatrix.matrix[i][j],  transposedMatrix.matrix[j][i]);
		}
	}

	return Matrix2d{transposedMatrix};
}

Matrix1d Matrix2d::Column(const unsigned index) const
{
	const auto matrix1d = Matrix1d(this->rows);
	for (size_t i = 0; i < this->rows; ++i)
	{
		matrix1d.matrix[i] = this->matrix[i][index];
	}

	return Matrix1d{matrix1d};
}

Matrix1d Matrix2d::Row(const unsigned index) const
{
	const auto matrix1d = Matrix1d(this->cols);
	for (size_t i = 0; i < this->cols; ++i)
	{
		matrix1d.matrix[i] = this->matrix[index][i];
	}

	return Matrix1d{matrix1d};
}

void Matrix2d::SwapColumns(const unsigned row1, const unsigned row2, const unsigned from, const unsigned to) const
{
	for (size_t i = from; i < to; ++i)
	{
		std::swap(this->matrix[i][row1], this->matrix[i][row2]);
	}
}

void Matrix2d::SwapRows(const unsigned col1, const unsigned col2, const unsigned from, const unsigned to) const
{
	for (size_t i = from; i < to; ++i)
	{
		std::swap(this->matrix[col1][i], this->matrix[col2][i]);
	}
}

Matrix2d& Matrix2d::operator=(const Matrix2d& matrix2d)
{
	if (this == &matrix2d)
	{
		return *this;
	}

	for (size_t i = 0; i < this->rows; ++i)
	{
		delete[] this->matrix[i];
	}
	delete[] this->matrix;

	this->rows = matrix2d.rows;
	this->cols = matrix2d.cols;
	this->matrix = new long double*[matrix2d.rows];

	for (size_t i = 0; i < matrix2d.rows; ++i)
	{
		this->matrix[i] = new long double[matrix2d.cols];
		
		for (size_t j = 0; j < this->cols; ++j)
		{
			this->matrix[i][j] = matrix2d.matrix[i][j];
		}
	}

	return *this;
}

Matrix2d& Matrix2d::operator=(Matrix2d&& matrix2d) noexcept
{
	std::swap(this->cols, matrix2d.cols);
	std::swap(this->rows, matrix2d.rows);
	std::swap(this->matrix, matrix2d.matrix);
	
	return *this;
}

Matrix1d Matrix2d::operator*(const Matrix1d& matrix1d) const
{
	const auto result = Matrix1d(matrix1d);
	for (size_t i = 0; i < this->rows; ++i)
	{
		result.matrix[i] = 0;

		for (size_t j = 0; j < this->cols; ++j)
		{
			result.matrix[i] += this->matrix[i][j] * matrix1d.matrix[j];
		}
	}

	return Matrix1d{result};
}

Matrix2d::~Matrix2d()
{
	for (size_t i = 0; i < this->rows; ++i)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}
