#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    long long N, K; cin >> N >> K;
    long long answer = N;

    N = N % K;
    answer = min(answer, N);

    for (int i = 0; i < 10000; ++i) {
        N = abs(N - K);
        answer = min(answer, N);
    }

    cout << answer << endl;
}

