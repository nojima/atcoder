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
    vector<int> A(N-1);
    for (int i = 0; i < N-1; ++i) {
        cin >> A[i];
        A[i]--;
    }

    vector<int> ans(N);
    for (int i = 0; i < N-1; ++i) {
        ans[A[i]]++;
    }

    for (int i = 0; i < N; ++i) {
        cout << ans[i] << "\n";
    }
}
