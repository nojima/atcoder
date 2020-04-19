#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

// n_C_2
inline long long combo2(long long n) {
    return n * (n-1) / 2;
}

int main() {
    int N; cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    // 各整数iの出現回数v
    vector<int> freq(N+1);
    for (int i = 0; i < N; ++i) {
        freq[A[i]]++;
    }

    // 何も取り除かない場合、何通りあるか
    long long all = 0;
    for (int i = 1; i < N+1; ++i) {
        all += combo2(freq[i]);
    }

    //cout << "all = " << all << endl;
    for (int k = 1; k <= N; ++k) {
        int i = A[k-1];
        long long ans = all - combo2(freq[i]) + combo2(freq[i]-1);
        cout << ans << "\n";
    }
}
