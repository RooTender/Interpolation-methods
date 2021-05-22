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

void Matrix2d::generateValues(int a1, int a2, int a3)
{
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {

			switch (abs(i - j)) {
			case 0:
				matrix[i][j] = a1;
				break;

			case 1:
				matrix[i][j] = a2;
				break;

			case 2:
				matrix[i][j] = a3;
				break;

			default:
				matrix[i][j] = 0;
				break;
			}
		}
	}
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
