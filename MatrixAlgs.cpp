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

long double MatrixAlgs::LUDecomposition(const Matrix2d& A, Matrix1d& x, Matrix1d b)
{
    Matrix2d L = Matrix2d(A.toIdentity());
    Matrix2d U = Matrix2d(A);

    if (A.hasNullOnDiagonal()) {

        // Do the pivoting
        Matrix2d P = Matrix2d(L);

        for (int i = 0; i < A.rows - 1; ++i) {
            auto pivotIndex = U.column(i).trunc(i, U.rows).abs().indexOf_max();
            pivotIndex = pivotIndex + i;

            U.swapRows(i, pivotIndex, i, U.cols);
            L.swapRows(i, pivotIndex, 0, i);
            P.swapRows(i, pivotIndex, 0, P.cols);

            // LU decomposition
            for (int j = i + 1; j < A.cols; ++j) {
                L.matrix[j][i] = U.matrix[j][i] / U.matrix[i][i];

                for (int k = i; k < A.cols; ++k) {
                    U.matrix[j][k] -= L.matrix[j][i] * U.matrix[i][k];
                }
            }
        }

        b = P * b;
    }
    else {

        // LU decomposition
        for (int i = 0; i < A.rows - 1; ++i) {
            for (int j = i + 1; j < A.cols; ++j) {
                L.matrix[j][i] = U.matrix[j][i] / U.matrix[i][i];

                for (int k = i; k < A.cols; ++k) {
                    U.matrix[j][k] -= L.matrix[j][i] * U.matrix[i][k];
                }
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
    for (int i = A.rows; i > 0; --i) {

        // calculate y_i
        x.matrix[i - 1] = y.matrix[i - 1];

        for (int j = A.cols - 1; j >= i; --j) {
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
    
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < B.size(); ++j) {
            M.matrix[i + j] += A.matrix[i] * B.matrix[j];
        }
    }

    return Matrix1d(M);
}

Matrix1d MatrixAlgs::lagrangeInterpolation(const PointArray& points)
{
    Matrix1d** lagrangeBase = new Matrix1d*[points.getLength()];

    for (int i = 0; i < points.getLength(); ++i) {
        Matrix1d *polynomial = nullptr;

        for (int j = 0; j < points.getLength(); ++j) {
            if (i == j) {
                continue;
            }

            long double arr[2] = { 1.0l, -points.arr[j].x };
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

            for (int k = 0; k < (*polynomial).size(); ++k) {
                (*polynomial).matrix[k] /= points.arr[i].x - points.arr[j].x;
            }
        }

        if (polynomial != nullptr) {
            lagrangeBase[i] = new Matrix1d(*polynomial);

            delete polynomial;
        }
    }

    Matrix1d result = Matrix1d(points.getLength());
    result.fill(0);

    for (int i = 0; i < points.getLength(); ++i) {
        for (int j = 0; j < lagrangeBase[i]->size(); ++j) {
            result.matrix[j] += lagrangeBase[i]->matrix[j] * points.arr[i].y;
        }
    }

    return Matrix1d(result);
}

void MatrixAlgs::splineInterpolation(const PointArray& points, Matrix1d**& splines)
{
    Matrix2d M = Matrix2d(8);
    M.fill(0);

    // hardcoded matrix2d
    M.matrix[0][0] =  1.0l;  // { 1, 0, 0, 0, 0, 0, 0, 0 }
    M.matrix[1][4] =  1.0l;  // { 0, 0, 0, 0, 1, 0, 0, 0 }
    M.matrix[2][0] =  1.0l;  // { 1, x, x, x, 0, 0, 0, 0 }
    M.matrix[3][4] =  1.0l;  // { 0, 0, 0, 0, 1, x, x, x }
    M.matrix[4][1] =  1.0l;  // { 0, 1, x, x, 0,-1, 0, 0 }
    M.matrix[4][5] = -1.0l;
    M.matrix[5][2] =  2.0l;  // { 0, 0, 2, x, 0, 0,-2, 0 }
    M.matrix[5][6] = -2.0l;
    M.matrix[6][2] =  1.0l;  // { 0, 0, 1, 0, 0, 0, 0, 0 }
    M.matrix[7][6] =  2.0l;  // { 0, 0, 1, 0, 0, 0, 2, x }

    Matrix1d y = Matrix1d(8);
    y.fill(0);

    splines = new Matrix1d* [points.getLength() - 2];
    for (int i = 0; i < points.getLength() - 2; ++i) {
        auto h = points.arr[i + 1].x - points.arr[i].x;

        M.matrix[2][1] = M.matrix[3][5] = h;
        M.matrix[2][2] = M.matrix[3][6] = h * h;
        M.matrix[2][3] = M.matrix[3][7] = h * h * h;
        M.matrix[4][2] = 2.0l * h;
        M.matrix[4][3] = 3.0l * h * h;
        M.matrix[5][3] = M.matrix[7][7] = 6.0l * h;

        y.matrix[0] = points.arr[i].y;
        y.matrix[1] = points.arr[i + 1].y;
        y.matrix[2] = points.arr[i + 1].y;
        y.matrix[3] = points.arr[i + 2].y;

        splines[i] = new Matrix1d(8);
        LUDecomposition(M, *splines[i], y);
    }
}
