#pragma once
#include "lib/std.hpp"

template <class T>
using Matrix = vector<vector<T>>;

template <class T>
Matrix<T> matrix_mul(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    assert(lhs[0].size() == rhs.size());
    size_t m = lhs.size();
    size_t n = rhs.size();
    size_t p = rhs[0].size();
    Matrix<T> ret(m, vector<T>(p));
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < p; ++j) {
            for (size_t k = 0; k < n; ++k) {
                ret[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
    }
    return ret;
}

template <class T>
vector<T> matrix_vector_mul(const Matrix<T>& lhs, const vector<T>& rhs) {
    assert(lhs[0].size() == rhs.size());
    size_t m = lhs.size();
    size_t n = rhs.size();
    vector<T> ret(m);
    for (size_t i = 0; i < m; ++i) {
        for (size_t k = 0; k < n; ++k) {
            ret[i] += lhs[i][k] * rhs[k];
        }
    }
    return ret;
}

// n×n の単位行列を返す。
template <class T>
Matrix<T> identity_matrix(size_t n) {
    Matrix<T> ret(n, vector<T>(n));
    for (size_t i = 0; i < n; ++i) {
        ret[i][i] = 1;
    }
    return ret;
}
