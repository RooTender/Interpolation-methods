#include "Matrix2d.h"

Matrix2d::Matrix2d(int n)
{
	this->rows = n;
	this->cols = n;

	matrix = new long double* [n];
	for (int i = 0; i < n; ++i) {
		matrix[i] = new long double[n];
	}
}

Matrix2d::Matrix2d(const Matrix2d& M) : Matrix2d(M.cols)
{
	for (int i = 0; i < this->rows; ++i) {
		for (int j = 0; j < this->cols; ++j) {
			this->matrix[i][j] = M.matrix[i][j];
		}
	}
}

void Matrix2d::fill(long double value)
{
	for (int i = 0; i < this->rows; ++i) {
		for (int j = 0; j < this->cols; ++j) {
			this->matrix[i][j] = value;
		}
	}
}

bool Matrix2d::hasNullOnDiagonal() const
{
	for (int i = 0; i < this->cols; ++i) {
		if (matrix[i][i] == 0) {
			return true;
		}
	}

	return false;
}

Matrix2d Matrix2d::toIdentity() const
{
	Matrix2d I = Matrix2d(*this);
	for (int i = 0; i < this->rows; ++i) {
		for (int j = 0; j < this->cols; ++j) {
			I.matrix[i][j] = (i == j) ? 1 : 0;
		}
	}
	return Matrix2d(I);
}

Matrix2d Matrix2d::transpose()
{
	Matrix2d trM(*this);

	for (int i = 0; i < this->cols; ++i) {
		for (int j = 0; j < i; ++j) {
			
			// swap algorithm
			auto tmp = trM.matrix[i][j];
			trM.matrix[i][j] = trM.matrix[j][i];
			trM.matrix[j][i] = tmp;
		}
	}

	return Matrix2d(trM);
}

Matrix1d Matrix2d::column(int index)
{
	Matrix1d M = Matrix1d(this->rows);
	for (int i = 0; i < this->rows; ++i) {
		M.matrix[i] = this->matrix[i][index];
	}

	return Matrix1d(M);
}

Matrix1d Matrix2d::row(int index)
{
	Matrix1d M = Matrix1d(this->cols);
	for (int i = 0; i < this->cols; ++i) {
		M.matrix[i] = this->matrix[index][i];
	}

	return Matrix1d(M);
}

void Matrix2d::swapColumns(int row1, int row2, int from, int to)
{
	for (int i = from; i < to; ++i) {
		long double tmp = this->matrix[i][row1];
		this->matrix[i][row1] = this->matrix[i][row2];
		this->matrix[i][row2] = tmp;
	}
}

void Matrix2d::swapRows(int col1, int col2, int from, int to)
{
	for (int i = from; i < to; ++i) {
		long double tmp = this->matrix[col1][i];
		this->matrix[col1][i] = this->matrix[col2][i];
		this->matrix[col2][i] = tmp;
	}
}

Matrix2d Matrix2d::operator=(const Matrix2d& M)
{
	for (int i = 0; i < this->size(); ++i) {
		this->matrix[i] = M.matrix[i];
	}
	return *this;
}

Matrix1d Matrix2d::operator*(const Matrix1d& M) const
{
	Matrix1d R = Matrix1d(M);
	for (int i = 0; i < this->rows; ++i) {
		R.matrix[i] = 0;

		for (int j = 0; j < this->cols; ++j) {
			R.matrix[i] += this->matrix[i][j] * M.matrix[j];
		}
	}

	return Matrix1d(R);
}

Matrix2d::~Matrix2d()
{
	for (int i = 0; i < this->rows; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
}
