#include "Matrix2d.h"

#include <utility>

Matrix2d::Matrix2d(const int n) : matrix(new long double*[n])
{
	this->rows = n;
	this->cols = n;

	for (int i = 0; i < n; ++i)
	{
		matrix[i] = new long double[n];
	}
}

Matrix2d::Matrix2d(const Matrix2d& matrix) : Matrix2d(matrix.cols)
{
	for (int i = 0; i < this->rows; ++i)
	{
		for (int j = 0; j < this->cols; ++j)
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
	for (int i = 0; i < this->rows; ++i)
	{
		for (int j = 0; j < this->cols; ++j)
		{
			this->matrix[i][j] = value;
		}
	}
}

bool Matrix2d::HasNullOnDiagonal() const
{
	for (int i = 0; i < this->cols; ++i)
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
	for (int i = 0; i < this->rows; ++i)
	{
		for (int j = 0; j < this->cols; ++j)
		{
			identityMatrix.matrix[i][j] = (i == j) ? 1 : 0;
		}
	}
	return Matrix2d{identityMatrix};
}

Matrix2d Matrix2d::Transpose() const
{
	const Matrix2d transposedMatrix(*this);

	for (int i = 0; i < this->cols; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			std::swap(transposedMatrix.matrix[i][j],  transposedMatrix.matrix[j][i]);
		}
	}

	return Matrix2d{transposedMatrix};
}

Matrix1d Matrix2d::Column(const int index) const
{
	const auto matrix1d = Matrix1d(this->rows);
	for (int i = 0; i < this->rows; ++i)
	{
		matrix1d.matrix[i] = this->matrix[i][index];
	}

	return Matrix1d{matrix1d};
}

Matrix1d Matrix2d::Row(const int index) const
{
	const auto matrix1d = Matrix1d(this->cols);
	for (int i = 0; i < this->cols; ++i)
	{
		matrix1d.matrix[i] = this->matrix[index][i];
	}

	return Matrix1d{matrix1d};
}

void Matrix2d::SwapColumns(const int row1, const int row2, const int from, const int to) const
{
	for (int i = from; i < to; ++i)
	{
		std::swap(this->matrix[i][row1], this->matrix[i][row2]);
	}
}

void Matrix2d::SwapRows(const int col1, const int col2, const int from, const int to) const
{
	for (int i = from; i < to; ++i)
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

	for (int i = 0; i < this->rows; ++i)
	{
		delete[] this->matrix[i];
	}
	delete[] this->matrix;

	this->rows = matrix2d.rows;
	this->cols = matrix2d.cols;
	this->matrix = new long double*[matrix2d.rows];

	for (int i = 0; i < matrix2d.rows; ++i)
	{
		this->matrix[i] = new long double[matrix2d.cols];
		
		for (int j = 0; j < this->cols; ++j)
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
	for (int i = 0; i < this->rows; ++i)
	{
		result.matrix[i] = 0;

		for (int j = 0; j < this->cols; ++j)
		{
			result.matrix[i] += this->matrix[i][j] * matrix1d.matrix[j];
		}
	}

	return Matrix1d{result};
}

Matrix2d::~Matrix2d()
{
	for (int i = 0; i < this->rows; ++i)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}
