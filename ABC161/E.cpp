#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, K, C; cin >> N >> K >> C;
    string days; cin >> days;

    for (int k = 0; k < N; ++k) {
        // k日目を選ばずに働くことができるか？

        int should_work = K;
        int rest = 0;
        for (int i = 0; i < N; ++i) {
            if (rest > 0) {
                --rest;
                continue;
            }
            if (i != k && days[i] != 'x') {
                // この日は働く
                should_work--;
                rest = C;
            }
        }
        if (should_work > 0) {
            // kを選ばざるを得ない
            cout << (k+1) << endl;
        }
    }
}
