#include "lib/prelude.hpp"
#include "lib/modint.hpp"

using mint = ModInt<998244353>;

int bit_ceil(int n) {
    int ret = 1;
    while (ret < n) ret *= 2;
    return ret;
}

struct LazySegmentTree {
    LazySegmentTree(int size, vector<vector<mint>>&& A):
        n(bit_ceil(size)), data(2*n-1), delayed(2*n-1, nullopt), A(A) {}

    // [lo, hi) の区間のすべての要素を update(*, value) によって更新する
    void range_update(int lo, int hi, int d) {
        range_update_(lo, hi, d, 0, 0, n);
    }

    mint query_all() {
        force(0, 0, n);
        return data[0];
    }

private:
    void range_update_(int lo, int hi, int d, int index, int left, int right) {
        force(index, left, right);
        if (hi <= left || right <= lo) { // この区間と更新区間が全く重ならないとき
            return;
        }
        if (lo <= left && right <= hi) { // この区間が更新区間に完全に包含されているとき
            data[index] = A[d][right-left];
            delayed[index] = d;
            return;
        }
        // この区間の一部が更新区間とオーバーラップしているとき
        int middle = (left + right) / 2;
        range_update_(lo, hi, d, index*2+1, left, middle);
        range_update_(lo, hi, d, index*2+2, middle, right);

        mint a = data[index*2+1];
        mint b = data[index*2+2];
        data[index] = a + b * mint(10).pow(right-middle);
        //cout << index << " " << data[index] << endl;
    }

    void force(int index, int left, int right) {
        if (!delayed[index]) return;
        if (index < n-1) {
            int middle = (left + right) / 2;
            force_child(index*2+1, *delayed[index], left, middle);
            force_child(index*2+2, *delayed[index], middle, right);
        }
        delayed[index] = nullopt;
    }

    void force_child(int index, int d, int left, int right) {
        data[index] = A[d][right-left];
        delayed[index] = d;
    }

private:
    int n;
    vector<mint> data;
    vector<optional<int>> delayed;
    vector<vector<mint>> A;
};

int main() {
    int N = read_int();
    int Q = read_int();

    int M = bit_ceil(N);
    vector A(10, vector(M+1, mint()));
    REP(i, 10) {
        A[i][0] = 0;
        FOR(j, 1, M+1) {
            A[i][j] = A[i][j-1]*10 + i;
        }
    }

    LazySegmentTree st(N, move(A));
    st.range_update(0, N, 1);

    REP(i, Q) {
        int l = read_int() - 1;
        int r = read_int() - 1;
        int d = read_int();
        st.range_update(N-r-1, N-l, d);
        cout << st.query_all() << LF;
    }
}
