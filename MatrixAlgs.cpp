#include "MatrixAlgs.h"

long double MatrixAlgs::norm(const Matrix1d& res)
{
    long double result = 0;
    for (int i = 0; i < res.size(); ++i) {
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
        for (int i = 0; i < A.rows; ++i) {
            xNew.matrix[i] = b.matrix[i];

            for (int j = 0; j < A.cols; ++j) {
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
        for (int i = 0; i < A.rows; ++i) {
            x.matrix[i] = b.matrix[i];

            for (int j = 0; j < A.cols; ++j) {
                if (j == i) continue;

                x.matrix[i] -= A.matrix[i][j] * x.matrix[j];
            }
            x.matrix[i] /= A.matrix[i][i];
        }
        mNorm = norm(A * x - b);

    } while (!(mNorm < limit) && ++iterations < upperLimit);

    return (iterations < upperLimit) ? mNorm : 0;
}

long double MatrixAlgs::LUDecomposition(const Matrix2d& A, Matrix1d& x, const Matrix1d& b)
{
    Matrix2d L = Matrix2d(A.toIdentity());
    Matrix2d U = Matrix2d(A);

    // LU decomposition
    for (int i = 0; i < A.rows - 1; ++i) {
        for (int j = i + 1; j < A.cols; ++j) {
            L.matrix[j][i] = U.matrix[j][i] / U.matrix[i][i];
            
            for (int k = i; k < A.cols; ++k) {
                U.matrix[j][k] -= L.matrix[j][i] * U.matrix[i][k];
            }
        }
    }

    Matrix1d y = Matrix1d(x);

    // forward subtitution
    for (int i = 0; i < A.rows; ++i) {

        // calculate y_i
        y.matrix[i] = b.matrix[i];
        
        for (int j = 0; j < i; ++j) {
            y.matrix[i] -= L.matrix[i][j] * y.matrix[j];
        }
        
        y.matrix[i] /= L.matrix[i][i];
    }

    // back subtitution
    for (int i = A.rows - 1; i >= 0; --i) {

        // calculate y_i
        x.matrix[i] = y.matrix[i];

        for (int j = A.cols - 1; j > i; --j) {
            x.matrix[i] -= U.matrix[i][j] * x.matrix[j];
        }

        x.matrix[i] /= U.matrix[i][i];
    }

    return norm(A * x - b);
}
