#include "Matrix.h"

int Matrix::Size()
{
	return this->cols * this->rows;
}

int Matrix::Size() const
{
	return this->cols * this->rows;
}
