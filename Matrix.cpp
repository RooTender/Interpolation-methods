#include "Matrix.h"
int Matrix::size()
{
	return this->cols * this->rows;
}

int Matrix::size() const
{
	return this->cols * this->rows;
}
