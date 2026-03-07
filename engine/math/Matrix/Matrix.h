//
// Created by Zachary on 3/5/26.
//

#ifndef LAVENDERENGINE_MATRIX_H
#define LAVENDERENGINE_MATRIX_H
#include <cstring>

#include "math/Vector/Vector.h"

namespace lavender::math {
    struct Matrix4 {
    float matrix[4][4]{};

    Matrix4() {
        identity();
    }

    void identity() {
        std::memset(matrix, 0, sizeof(float) * 16);
        matrix[0][0] = 1.0f;
        matrix[1][1] = 1.0f;
        matrix[2][2] = 1.0f;
        matrix[3][3] = 1.0f;
    }

    Matrix4 operator*(const Matrix4& other) const {
        Matrix4 result;
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                result.matrix[row][col] =
                    matrix[row][0] * other.matrix[0][col] +
                    matrix[row][1] * other.matrix[1][col] +
                    matrix[row][2] * other.matrix[2][col] +
                    matrix[row][3] * other.matrix[3][col];
            }
        }
        return result;
    }

    Vector4 operator*(const Vector4& v) const {
        Vector4 result;
        result.x = (matrix[0][0] * v.x) + (matrix[0][1] * v.y) + (matrix[0][2] * v.z) + (matrix[0][3] * v.w);
        result.y = (matrix[1][0] * v.x) + (matrix[1][1] * v.y) + (matrix[1][2] * v.z) + (matrix[1][3] * v.w);
        result.z = (matrix[2][0] * v.x) + (matrix[2][1] * v.y) + (matrix[2][2] * v.z) + (matrix[2][3] * v.w);
        result.w = (matrix[3][0] * v.x) + (matrix[3][1] * v.y) + (matrix[3][2] * v.z) + (matrix[3][3] * v.w);
        return result;
    }

    void transpose() {
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                std::swap(matrix[row][col], matrix[col][row]);
            }
        }
    }

    static Matrix4 inverse(const Matrix4& other) {
        Matrix4 input = other;
        Matrix4 result; // Starts as identity

        int n = 4;
        float epsilon = 1e-6f;

        for (int col = 0; col < n; col++) {
            // Partial pivot
            int pivotRow = col;
            for (int k = col + 1; k < n; k++) {
                if (std::abs(input.matrix[k][col]) > std::abs(input.matrix[pivotRow][col])) {
                    pivotRow = k;
                }
            }

            // Swap rows in both input and result matrices
            if (pivotRow != col) {
                for (int k = 0; k < n; k++) {
                    std::swap(input.matrix[col][k], input.matrix[pivotRow][k]);
                    std::swap(result.matrix[col][k], result.matrix[pivotRow][k]);
                }
            }

            // Check singularity
            float divisor = input.matrix[col][col];
            if (std::abs(divisor) < epsilon) {
                // and log an error and identity
                return Matrix4();
            }

            // Normalize the pivot row
            for (int k = 0; k < n; k++) {
                input.matrix[col][k] /= divisor;
                result.matrix[col][k] /= divisor;
            }

            // Eliminate other entries in column
            for (int row = 0; row < n; row++) {
                if (row != col) {
                    float factor = input.matrix[row][col];
                    for (int k = 0; k < n; k++) {
                        input.matrix[row][k] -= factor * input.matrix[col][k];
                        result.matrix[row][k] -= factor * result.matrix[col][k];
                    }
                }
            }
        }
        return result;
    }

    // Later RHI code
    // Addition and subtraction for lerping
    // Scalar Multiplication
    // QOL *= ad += -=
    // Accessor Operators [] () , matrix(row, col) to get specific value
    // Data pointer return &matrix[0][0]
    // Equality operators == !=; small epsilon since using floats

};

class Matrix {
};
}


#endif //LAVENDERENGINE_MATRIX_H