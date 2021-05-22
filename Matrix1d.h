#pragma once
#include "Matrix.h"
class Matrix1d : public Matrix
{
public:
	long double* matrix;

	Matrix1d(int n);
	Matrix1d(const Matrix1d& M);

	template<typename func>
	void generateValues(func function, int arg);
	void fill(long double value) override;

	Matrix1d operator= (const Matrix1d& M);
	Matrix1d operator- (const Matrix1d& M) const;

	~Matrix1d();
};

template<typename func>
inline void Matrix1d::generateValues(func function, int arg)
{
	for (int i = 0; i < cols; i++) {
		matrix[i] = function(i, arg);
	}
}