#include "Matrix.h"

size_t Matrix::Size()
{
	return this->cols * this->rows;
}

size_t Matrix::Size() const
{
	return this->cols * this->rows;
}
