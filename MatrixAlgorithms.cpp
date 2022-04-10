#include "MatrixAlgorithms.h"

#include <corecrt_math.h>
#include <stdexcept>

long double MatrixAlgorithms::Norm(const Matrix1d& res)
{
	long double result = 0;
	for (size_t i = 0; i < res.Size(); ++i)
	{
		result += res.matrix[i] * res.matrix[i];
	}

	return sqrtl(result);
}

long double MatrixAlgorithms::Jacobi(const Matrix2d& a, Matrix1d& x, const Matrix1d& b, long double limit, int& iterations)
{
	iterations = 0;
	const int upperLimit = b.Size();

	long double mNorm = 0;

	do
	{
		const Matrix1d newX = x;
		for (size_t i = 0; i < a.rows; ++i)
		{
			newX.matrix[i] = b.matrix[i];

			for (size_t j = 0; j < a.cols; ++j)
			{
				if (j == i)
				{
					continue;
				}

				newX.matrix[i] -= a.matrix[i][j] * x.matrix[j];
			}
			newX.matrix[i] /= a.matrix[i][i];
		}

		x = newX;
		mNorm = Norm(a * x - b);
	}
	while (!(mNorm < limit) && ++iterations < upperLimit);

	return (iterations < upperLimit) ? mNorm : 0;
}

long double MatrixAlgorithms::GaussSeidl(const Matrix2d& a, Matrix1d& x, const Matrix1d& b, long double limit,
                                   int& iterations)
{
	iterations = 0;
	const int upperLimit = b.Size();

	long double mNorm;

	do
	{
		for (size_t i = 0; i < a.rows; ++i)
		{
			x.matrix[i] = b.matrix[i];

			for (size_t j = 0; j < a.cols; ++j)
			{
				if (j == i) continue;

				x.matrix[i] -= a.matrix[i][j] * x.matrix[j];
			}
			x.matrix[i] /= a.matrix[i][i];
		}
		mNorm = Norm(a * x - b);
	}
	while (!(mNorm < limit) && ++iterations < upperLimit);

	return (iterations < upperLimit) ? mNorm : 0;
}

long double MatrixAlgorithms::LUDecomposition(const Matrix2d& a, Matrix1d& x, Matrix1d b)
{
	const auto l = Matrix2d(a.ToIdentity());
	const auto u = Matrix2d(a);

	if (a.HasNullOnDiagonal())
	{
		// Do the pivoting
		const auto p = Matrix2d(l);

		for (size_t i = 0; i < a.rows - 1; ++i)
		{
			auto pivotIndex = u.Column(i).Trunc(i, u.rows).Abs().IndexOfMax();
			pivotIndex = pivotIndex + i;

			u.SwapRows(i, pivotIndex, i, u.cols);
			l.SwapRows(i, pivotIndex, 0, i);
			p.SwapRows(i, pivotIndex, 0, p.cols);

			// LU decomposition
			for (size_t j = i + 1; j < a.cols; ++j)
			{
				l.matrix[j][i] = u.matrix[j][i] / u.matrix[i][i];

				for (size_t k = i; k < a.cols; ++k)
				{
					u.matrix[j][k] -= l.matrix[j][i] * u.matrix[i][k];
				}
			}
		}

		b = p * b;
	}
	else
	{
		// LU decomposition
		for (size_t i = 0; i < a.rows - 1; ++i)
		{
			for (size_t j = i + 1; j < a.cols; ++j)
			{
				l.matrix[j][i] = u.matrix[j][i] / u.matrix[i][i];

				for (size_t k = i; k < a.cols; ++k)
				{
					u.matrix[j][k] -= l.matrix[j][i] * u.matrix[i][k];
				}
			}
		}
	}

	const auto y = Matrix1d(x);

	// forward substitution
	for (size_t i = 0; i < a.rows; ++i)
	{
		// calculate y_i
		y.matrix[i] = b.matrix[i];

		for (size_t j = 0; j < i; ++j)
		{
			y.matrix[i] -= l.matrix[i][j] * y.matrix[j];
		}

		y.matrix[i] /= l.matrix[i][i];
	}

	// back substitution
	for (size_t i = a.rows; i > 0; --i)
	{
		// calculate y_i
		x.matrix[i - 1] = y.matrix[i - 1];

		for (size_t j = a.cols - 1; j >= i; --j)
		{
			x.matrix[i - 1] -= u.matrix[i - 1][j] * x.matrix[j];
		}

		x.matrix[i - 1] /= u.matrix[i - 1][i - 1];
	}

	return Norm(a * x - b);
}

Matrix1d MatrixAlgorithms::MultiplyPolynomials(const Matrix1d& a, const Matrix1d& b)
{
	auto matrix = Matrix1d(a.Size() + b.Size() - 1);
	matrix.Fill(0);

	for (size_t i = 0; i < a.Size(); ++i)
	{
		for (size_t j = 0; j < b.Size(); ++j)
		{
			matrix.matrix[i + j] += a.matrix[i] * b.matrix[j];
		}
	}

	return Matrix1d{matrix};
}

Matrix1d MatrixAlgorithms::LagrangeInterpolation(const PointArray& points)
{
	const auto lagrangeFunctions = new Matrix1d*[points.GetAmount()]{};

	for (size_t i = 0; i < points.GetAmount(); ++i)
	{
		for (size_t j = 0; j < points.GetAmount(); ++j)
		{
			if (i == j)
			{
				continue;
			}

			const long double arr[2] = {1.0l, -points.arr[j].x};
			if (lagrangeFunctions[i] == nullptr)
			{
				lagrangeFunctions[i] = new Matrix1d(2);
				lagrangeFunctions[i]->matrix[0] = arr[0];
				lagrangeFunctions[i]->matrix[1] = arr[1];
			}
			else
			{
				*lagrangeFunctions[i] = MultiplyPolynomials(
					*lagrangeFunctions[i], Matrix1d(arr, 2)
				);
			}

			for (size_t k = 0; k < lagrangeFunctions[i]->Size(); ++k)
			{
				lagrangeFunctions[i]->matrix[k] /= points.arr[i].x - points.arr[j].x;
			}
		}
	}

	auto result = Matrix1d(points.GetAmount());
	result.Fill(0);

	for (size_t i = 0; i < points.GetAmount(); ++i)
	{
		if (points.GetAmount() > 1)
		{
			for (size_t j = 0; j < lagrangeFunctions[i]->Size(); ++j)
			{
				result.matrix[j] += lagrangeFunctions[i]->matrix[j] * points.arr[i].y;
			}

			delete lagrangeFunctions[i];
		}
		else
		{
			result.matrix[0] = points.arr[0].y;
		}
	}

	delete[] lagrangeFunctions;

	return Matrix1d{result};
}

Matrix1d MatrixAlgorithms::SplineInterpolation(const PointArray& points)
{
	auto m = Matrix2d((points.GetAmount() - 1) * 4);
	auto x = Matrix1d(m.rows);
	auto y = Matrix1d(m.rows);

	m.Fill(0);
	y.Fill(0);

	auto shift = points.GetAmount() - 1;
	for (size_t i = 0; i < points.GetAmount() - 1; ++i)
	{
		m.matrix[i][i * 4] = 1.0l;

		const auto h = points.arr[i + 1].x - points.arr[i].x;
		m.matrix[i + shift][i * 4] = 1.0l;
		m.matrix[i + shift][i * 4 + 1] = h;
		m.matrix[i + shift][i * 4 + 2] = h * h;
		m.matrix[i + shift][i * 4 + 3] = h * h * h;

		y.matrix[i] = points.arr[i].y;
		y.matrix[i + shift] = points.arr[i + 1].y;
	}

	shift *= 2;
	for (size_t i = 0; i < points.GetAmount() - 2; ++i)
	{
		const auto row = i * 2 + shift;

		const auto h = points.arr[i + 1].x - points.arr[i].x;
		m.matrix[row][i * 4 + 1] = 1.0l;
		m.matrix[row][i * 4 + 2] = 2.0l * h;
		m.matrix[row][i * 4 + 3] = 3.0l * h * h;
		m.matrix[row][i * 4 + 5] = -1.0l;

		m.matrix[row + 1][i * 4 + 2] = 2.0l;
		m.matrix[row + 1][i * 4 + 3] = 6.0l * h;
		m.matrix[row + 1][i * 4 + 6] = -2.0l;
	}

	const auto h = points.arr[points.GetAmount() - 1].x - points.arr[points.GetAmount() - 2].x;
	shift = (points.GetAmount() - 1) * 4 - 2;
	m.matrix[shift][2] = 2.0l;
	m.matrix[shift + 1][shift] = 2.0l;
	m.matrix[shift + 1][shift + 1] = 6.0l * h;

	LUDecomposition(m, x, y);

	return Matrix1d{x};
}
