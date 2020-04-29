#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

int main() {
    int N; cin >> N;
    int M; cin >> M;

    vector<int> A(M);
    for (int i = 0; i < M; ++i) {
        cin >> A[i];
    }


    int sum = 0;
    for (int i = 0; i < M; ++i) {
        sum += A[i];
    }
    int ans = N - sum;
    if (ans < 0) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}

