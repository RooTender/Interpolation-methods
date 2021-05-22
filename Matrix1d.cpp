#include "Matrix1d.h"

Matrix1d::Matrix1d(int n)
{
	this->rows = 1;
	this->cols = n;

	matrix = new long double[n];
}

Matrix1d::Matrix1d(const Matrix1d& M) : Matrix1d(M.size())
{
	for (int i = 0; i < this->size(); ++i) {
		this->matrix[i] = M.matrix[i];
	}
}

void Matrix1d::fill(long double value)
{
	for (int i = 0; i < this->cols; ++i) {
		this->matrix[i] = value;
	}
}

Matrix1d Matrix1d::operator=(const Matrix1d& M)
{
	for (int i = 0; i < this->size(); ++i) {
		this->matrix[i] = M.matrix[i];
	}
	return *this;
}

Matrix1d Matrix1d::operator-(const Matrix1d& M) const
{
	Matrix1d R = Matrix1d(*this);
	for (int i = 0; i < this->size(); ++i) {
		R.matrix[i] = this->matrix[i] - M.matrix[i];
	}

	return Matrix1d(R);
}

Matrix1d::~Matrix1d()
{
	delete[] matrix;
}
