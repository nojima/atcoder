#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> As;
    int total = 0;
    for (int i = 0; i < N; ++i) {
        int A; cin >> A;
        As.push_back(A);
        total += A;
    }

    int ok = 0;
    for (int i = 0; i < N; ++i) {
        if ((4*M)*As[i] >= total) {
            ++ok;
        }
    }
    if (ok >= M) {
        puts("Yes");
    } else {
        puts("No");
    }
}
