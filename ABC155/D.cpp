#include "lib/prelude.hpp"
#include "lib/binary_search.hpp"

int main() {
    auto N = read_int();
    auto K = read_int();
    vector<int64_t> A(N);
    REP(i, N) { A[i] = read_int(); }
    sort(ALL(A));

    auto ans = find_maximum_solution(
        -1'000'000'000'000'000'010, 1'000'000'000'000'000'010,
        [&](int64_t x){
            // xがK番目未満の積である
            // ⇔ x以下の積がK個未満である
            int64_t cnt = 0;
            REP(i, N) {
                // j = i+1, i+2, ..., N-1 の中で
                //   A[i]*A[j] <= x
                // となる j を数える。
                if(A[i] == 0) {
                    if(0 <= x) {
                        // i+1 <= j < N
                        cnt += N-i-1;
                    } else {
                        // zero
                    }
                } else if (A[i] > 0) {
                    // A[i]*A[j] <= x
                    // 左辺はjに関して単調増加
                    int max_j = find_maximum_solution(i, N-1, [&](int j){
                        return A[i]*A[j] <= x;
                    });
                    cnt += max_j - i;
                } else {
                    // A[i]*A[j] <= x
                    // 左辺はjに関して単調減少
                    int min_j = find_minimum_solution(i+1, N, [&](int j){
                        return A[i]*A[j] <= x;
                    });
                    cnt += N - min_j;
                }
            }
            return cnt < K;
        }
    );
    cout << ans+1 << LF;
}
