#include "Matrix1d.h"

Matrix1d::Matrix1d(int n)
{
	this->rows = 1;
	this->cols = n;

	matrix = new long double[n];
}

Matrix1d::Matrix1d(const Matrix1d& M) : Matrix1d(M.size())
{
	for (size_t i = 0; i < this->size(); ++i) {
		this->matrix[i] = M.matrix[i];
	}
}

Matrix1d::Matrix1d(long double* arr, size_t n) : Matrix1d(n)
{
	for (size_t i = 0; i < n; ++i) {
		matrix[i] = arr[i];
	}
}

void Matrix1d::fill(long double value)
{
	for (size_t i = 0; i < this->cols; ++i) {
		this->matrix[i] = value;
	}
}

Matrix1d Matrix1d::abs()
{
	Matrix1d M = Matrix1d(*this);
	for (size_t i = 0; i < this->cols; ++i) {
		M.matrix[i] = fabsl(M.matrix[i]);
	}
	
	return Matrix1d(M);
}

Matrix1d Matrix1d::trunc(size_t from, size_t to)
{
	Matrix1d M = Matrix1d(to - from);
	for (size_t i = from; i < to; ++i) {
		M.matrix[i - from] = this->matrix[i];
	}

	return M;
}

/**
 * Find maximum value in matrix and return index of it.
 *
 * @return index of maximum value in matrix.
 */
int Matrix1d::indexOf_max()
{
	int index = 0;
	for (size_t i = 1; i < this->cols; ++i) {
		if (this->matrix[i] > this->matrix[index]) {
			index = i;
		}
	}

	return index;
}

Matrix1d Matrix1d::operator=(const Matrix1d& M)
{
	delete[] this->matrix;

	this->rows = M.rows;
	this->cols = M.cols;
	this->matrix = new long double[M.size()];

	for (size_t i = 0; i < this->size(); ++i) {
		this->matrix[i] = M.matrix[i];
	}
	return *this;
}

Matrix1d Matrix1d::operator-(const Matrix1d& M) const
{
	Matrix1d R = Matrix1d(*this);
	for (size_t i = 0; i < this->size(); ++i) {
		R.matrix[i] = this->matrix[i] - M.matrix[i];
	}

	return Matrix1d(R);
}

Matrix1d::~Matrix1d()
{
	delete[] matrix;
}
