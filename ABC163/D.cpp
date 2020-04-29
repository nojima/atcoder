#include <iostream>
#include <cstdint>
using namespace std;

int main() {
    int64_t N, K; cin >> N >> K;

    int64_t ans = 0;
    for (int64_t k = K; k <= N+1; ++k) {
        ans += (N-k+1)*k+1;
        ans %= 1000000007;
    }
    cout << ans << "\n";
}
