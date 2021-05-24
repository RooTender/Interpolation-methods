#include "Matrix.h"
size_t Matrix::size()
{
	return this->cols * this->rows;
}

size_t Matrix::size() const
{
	return this->cols * this->rows;
}
