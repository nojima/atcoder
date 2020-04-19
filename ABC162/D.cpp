#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <cassert>
using namespace std;

inline int rgb(char c) {
    switch (c) {
        case 'R': return 0;
        case 'G': return 1;
        case 'B': return 2;
    }
    assert(false);
}

int main() {
    long long N; cin >> N;
    string S; cin >> S;

    //cerr << "[" << S << "]" << endl;

    // !A && !B
    long long c1 = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N-1; ++j) {
            int k = j + (j - i);
            if (k >= N) continue;
            if (S[i] == S[j] || S[i] == S[k] || S[j] == S[k]) {
                ++c1;
            }
        }
    }

    // !A
    int freq[3] = {0, 0, 0};
    for (int i = 0; i < N; ++i) {
        freq[rgb(S[i])]++;
    }
    long long c2 = 0;
    // 同じ色×3
    for (int i = 0; i < 3; ++i) {
        long long n = freq[i];
        c2 += n * (n-1) * (n-2) / 6;
    }
    // 同じ色×2 + 別の色
    for (int i = 0; i < 3; ++i) {
        long long n = freq[i];
        long long m = 0;
        for (int j = 0; j < 3; ++j) {
            if (j != i) m += freq[j];
        }
        c2 += (n * (n-1) / 2) * m;
    }

    // !B
    long long c3 = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N-1; ++j) {
            int k = j + (j - i);
            if (k >= N) continue;
            //cerr << i << ", " << j << ", " << k << endl;
            ++c3;
        }
    }

    long long all = N * (N-1) * (N-2) / 6;

    //cerr << "c1 = " << c1 << "; c2 = " << c2 << "; c3 = " << c3 << "; all = " << all << endl;

    cout << all - c2 - c3 + c1 << endl;

    return 0;
}

