#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

int bit_ceil(int n) {
    int ret = 1;
    while (ret < n) {
        ret *= 2;
    }
    return ret;
}

template <typename Num>
struct SingleUpdateAllMinSegmentTree {
    int n;
    vector<Num> data;

    explicit SingleUpdateAllMinSegmentTree(int size)
        : n(bit_ceil(size)), data(2*n-1, numeric_limits<Num>::max()) {}

    // i番目の要素を value に更新する
    void update(int i, Num value) { update_(i, value, 0, 0, n); }

    // 全体の min を返す
    Num all_min() { return data[0]; }

private:
    void update_(int i, Num value, int index, int left, int right) {
        if (i < left || i >= right) return;
        if (i == left && i+1 == right) {
            data[index] = value;
            return;
        }
        int middle = (left + right) / 2;
        update_(i, value, index*2+1, left, middle);
        update_(i, value, index*2+2, middle, right);
        data[index] = min(data[index*2+1], data[index*2+2]);
    }
};

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);

    int N, Q; cin >> N >> Q;
    vector<int> A(N), B(N);
    REP(i, N) {
        cin >> A[i] >> B[i]; --B[i];
    }
    vector<int> C(Q), D(Q);
    REP(i, Q) {
        cin >> C[i] >> D[i]; --C[i]; --D[i];
    }
    int M = 0;
    REP(i, N) M = max(M, B[i]);
    REP(i, Q) M = max(M, D[i]);

    vector<int> belongs_to(N);
    map<int, multiset<int>> box_values;
    SingleUpdateAllMinSegmentTree<int> st(M+1);
    REP(i, N) {
        belongs_to[i] = B[i];
        box_values[B[i]].insert(A[i]);
        int max_value = *box_values[B[i]].rbegin();
        st.update(B[i], max_value);
    }

    REP(i, Q) {
        int value = A[C[i]];
        int old_box = belongs_to[C[i]];
        int new_box = D[i];
        belongs_to[C[i]] = new_box;
        box_values[old_box].erase(box_values[old_box].find(value));
        box_values[new_box].insert(value);
        int old_box_max_value = box_values[old_box].empty() ?
            numeric_limits<int>::max() : *box_values[old_box].rbegin();
        int new_box_max_value = box_values[new_box].empty() ?
            numeric_limits<int>::max() : *box_values[new_box].rbegin();
        st.update(old_box, old_box_max_value);
        st.update(new_box, new_box_max_value);
        cout << st.all_min() << '\n';
    }
}
