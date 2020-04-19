#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
    int K; cin >> K;

    long long sum = 0;
    for (int a = 1; a <= K; ++a) {
        for (int b = 1; b <= K; ++b) {
            int g1 = __gcd(a, b);
            for (int c = 1; c <= K; ++c) {
                int g2 = __gcd(g1, c);
                sum += g2;
            }
        }
    }

    cout << sum << endl;

    return 0;
}
