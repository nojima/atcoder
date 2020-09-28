#include "lib/prelude.hpp"
#include "lib/io/string.hpp"

int main() {
    auto N = read_int();
    vector<string> S(N);
    REP(i, N) S[i] = read_word();

    int total_open = 0, total_close = 0;
    vector<pair<int, int>> items(N);
    REP(i, N) {
        // 対応する括弧を削除して残る括弧の数を数える
        int n_open = 0, n_close_unmatched = 0;
        for (char ch : S[i]) {
            if (ch == '(') {
                n_open++;
                total_open++;
            } else {
                if (n_open > 0) { n_open--; }
                else { n_close_unmatched++; }
                total_close++;
            }
        }
        int n_open_unmatched = n_open;
        items[i] = {n_open_unmatched, n_close_unmatched};
    }

    if (total_open != total_close) {
        cout << "No" << LF;
        return 0;
    }

    // (開き括弧の数)>=(閉じ括弧の数) であるようなitemは使えば使うほど得するので、先に全部使う
    // 閉じ括弧の数が少ないほど使える条件が緩いので、閉じ括弧の数が少ない順に使う
    vector<pair<int, int>> A, B;
    REP(i, N) {
        auto [n_open, n_close] = items[i];
        if (n_open >= n_close) { A.emplace_back(n_open, n_close); }
        else { B.emplace_back(n_open, n_close); }
    }
    sort(ALL(A), [](auto p1, auto p2){ return p1.second < p2.second; });
    int current_open = 0;
    REP(i, A.size()) {
        auto [n_open, n_close] = A[i];
        current_open -= n_close;
        if (current_open < 0) {
            cout << "No" << LF;
            return 0;
        }
        current_open += n_open;
    }

    // (開き括弧の数) < (閉じ括弧の数) であるようなitemは (開き括弧の数) が大きい順に使うのが最適
    // [proof]
    // 開き括弧の数を O[i]、閉じ括弧の数を C[i] と書く。
    // ある i, k (k = i+1) について O[i] < O[k] であったとする。
    // このとき i と k の順番を入れ替えても条件が悪くならないことを示す。
    // つまり、以下の「入れ替え前」の条件が成り立つならば「入れ替え後」の条件も成り立つことを示す。
    // 入れ替え前:
    //   T - C[i] >= 0
    //   T - C[i] + O[i] - C[k] >= 0
    // 入れ替え後:
    //   T - C[k] >= 0
    //   T - C[k] + O[k] - C[i] >= 0
    // まず、-C[i] + O[i] < 0 であるため
    //   0 <= T - C[i] + O[i] - C[k] < T - C[k]
    // よって１番目の条件が示された。
    // また、O[k] > O[i] より
    //   T - C[k] + O[k] - C[i] > T - C[k] + O[i] - C[i] = T - C[i] + O[i] - C[k] >= 0
    // よって２番目の条件も示された。
    sort(ALL(B), [](auto p1, auto p2) { return p1.first > p2.first; });
    REP(i, B.size()) {
        auto [n_open, n_close] = B[i];
        current_open -= n_close;
        if (current_open < 0) {
            cout << "No" << LF;
            return 0;
        }
        current_open += n_open;
    }

    cout << "Yes" << LF;
    return 0;
}
