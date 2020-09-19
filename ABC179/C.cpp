#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

int main() {
    int N; cin >> N;

    int ans = 0;
    for (int A = 1; A <= N; ++A) {
        for (int B = 1; A*B < N; ++B) {
            ans++;
        }
    }
    cout << ans << endl;
}
