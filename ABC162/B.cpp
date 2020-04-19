#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
    int N; cin >> N;

    long long sum = 0;
    for (int i = 1; i <= N; ++i) {
        if (i % 3 == 0 || i % 5 == 0) continue;
        sum += i;
    }

    cout << sum << endl;

    return 0;
}

