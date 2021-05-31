#include "MatrixAlgs.h"

long double MatrixAlgs::norm(const Matrix1d& res)
{
    long double result = 0;
    for (size_t i = 0; i < res.size(); ++i) {
        result += res.matrix[i] * res.matrix[i];
    }

    return sqrtl(result);
}

long double MatrixAlgs::jacobi(const Matrix2d& A, Matrix1d& x, const Matrix1d& b, long double limit, int& iterations)
{
    iterations = 0;
    int upperLimit = b.size();

    long double mNorm = 0;

    do {
        Matrix1d xNew = x;
        for (size_t i = 0; i < A.rows; ++i) {
            xNew.matrix[i] = b.matrix[i];

            for (size_t j = 0; j < A.cols; ++j) {
                if (j == i) continue;

                xNew.matrix[i] -= A.matrix[i][j] * x.matrix[j];
            }
            xNew.matrix[i] /= A.matrix[i][i];
        }
        
        x = xNew;
        mNorm = norm(A * x - b);

    } while (!(mNorm < limit) && ++iterations < upperLimit);

    return (iterations < upperLimit) ? mNorm : 0;
}

long double MatrixAlgs::gaussSeidl(const Matrix2d& A, Matrix1d& x, const Matrix1d& b, long double limit, int& iterations)
{
    iterations = 0;
    int upperLimit = b.size();

    long double mNorm = 0;

    do {
        for (size_t i = 0; i < A.rows; ++i) {
            x.matrix[i] = b.matrix[i];

            for (size_t j = 0; j < A.cols; ++j) {
                if (j == i) continue;

                x.matrix[i] -= A.matrix[i][j] * x.matrix[j];
            }
            x.matrix[i] /= A.matrix[i][i];
        }
        mNorm = norm(A * x - b);

    } while (!(mNorm < limit) && ++iterations < upperLimit);

    return (iterations < upperLimit) ? mNorm : 0;
}

long double MatrixAlgs::LUDecomposition(const Matrix2d& A, Matrix1d& x, Matrix1d b)
{
    Matrix2d L = Matrix2d(A.toIdentity());
    Matrix2d U = Matrix2d(A);

    if (A.hasNullOnDiagonal()) {

        // Do the pivoting
        Matrix2d P = Matrix2d(L);

        for (size_t i = 0; i < A.rows; ++i) {
            auto pivotIndex = U.column(i).trunc(i, U.rows).abs().indexOf_max();
            pivotIndex = pivotIndex + i;

            U.swapRows(i, pivotIndex, i, U.cols);
            L.swapRows(i, pivotIndex, 0, i - 1);
            P.swapRows(i, pivotIndex, 0, P.cols);

            // LU decomposition
            for (size_t j = i + 1; j < A.cols; ++j) {
                L.matrix[j][i] = U.matrix[j][i] / U.matrix[i][i];

                for (size_t k = i; k < A.cols; ++k) {
                    U.matrix[j][k] -= L.matrix[j][i] * U.matrix[i][k];
                }
            }
        }

        b = P * b;
    }
    else {

        // LU decomposition
        for (size_t i = 0; i < A.rows - 1; ++i) {
            for (size_t j = i + 1; j < A.cols; ++j) {
                L.matrix[j][i] = U.matrix[j][i] / U.matrix[i][i];

                for (size_t k = i; k < A.cols; ++k) {
                    U.matrix[j][k] -= L.matrix[j][i] * U.matrix[i][k];
                }
            }
        }
    }

    Matrix1d y = Matrix1d(x);

    // forward subtitution
    for (size_t i = 0; i < A.rows; ++i) {

        // calculate y_i
        y.matrix[i] = b.matrix[i];
        
        for (size_t j = 0; j < i; ++j) {
            y.matrix[i] -= L.matrix[i][j] * y.matrix[j];
        }
        
        y.matrix[i] /= L.matrix[i][i];
    }

    // back subtitution
    for (size_t i = A.rows; i > 0; --i) {

        // calculate y_i
        x.matrix[i - 1] = y.matrix[i - 1];

        for (size_t j = A.cols - 1; j > i; --j) {
            x.matrix[i - 1] -= U.matrix[i - 1][j] * x.matrix[j];
        }

        x.matrix[i - 1] /= U.matrix[i - 1][i - 1];
    }

    return norm(A * x - b);
}

Matrix1d MatrixAlgs::multiplyPolynomials(const Matrix1d& A, const Matrix1d& B)
{
    Matrix1d M = Matrix1d(A.size() + B.size() - 1);
    M.fill(0);
    
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < B.size(); ++j) {
            M.matrix[i + j] += A.matrix[i] * B.matrix[j];
        }
    }

    return Matrix1d(M);
}

Matrix1d MatrixAlgs::lagrangeInterpolation(Point*& points, size_t pointsCount, size_t limit)
{
    Matrix1d** lagrangeBase = new Matrix1d*[pointsCount];
    long double arr[2] = { 0 };

    if (pointsCount > limit) {
        pointsCount = limit;
    }

    for (size_t i = 0; i < pointsCount; ++i) {
        Matrix1d *polynomial = nullptr;

        for (size_t j = 0; j < pointsCount; ++j) {
            if (i == j) {
                continue;
            }

            arr[0] = 1.0l;
            arr[1] = -points[j].x;

            if (polynomial == nullptr) {
                polynomial = new Matrix1d(2);
                (*polynomial).matrix[0] = arr[0];
                (*polynomial).matrix[1] = arr[1];
            }
            else {
                *polynomial = multiplyPolynomials(
                    *polynomial, Matrix1d(arr, 2)
                );
            }

            for (size_t k = 0; k < (*polynomial).size(); ++k) {
                (*polynomial).matrix[k] /= (points[i].x - points[j].x);
            }
        }

        if (polynomial != nullptr) {
            lagrangeBase[i] = new Matrix1d(*polynomial);
            delete polynomial;
        }
    }

    Matrix1d result = Matrix1d(pointsCount);
    result.fill(0);

    for (size_t i = 0; i < pointsCount; ++i) {
        for (size_t j = 0; j < lagrangeBase[i]->size(); ++j) {
            result.matrix[j] += lagrangeBase[i]->matrix[j] * points[i].y;
        }
    }

    return Matrix1d(result);
}
