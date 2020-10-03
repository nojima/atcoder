#include "lib/prelude.hpp"

/*
C[i] = B[i] - A[i]

人iと人jが同時にエレベーターに乗っていない
    B[j] < A[i] || B[i] < A[j]
人iと人jが同時にエレベーターに乗っている
    A[i] < B[j] && A[j] < B[i]
    このとき B[i]-A[i] = B[j]-A[j]
           -A[i]-B[j] = -A[j]-B[i]
           A[i]+B[j] = A[j]+B[i]
    を満たさないといけない
*/

int main() {
}
