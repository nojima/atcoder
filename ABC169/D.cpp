#include "lib/prelude.hpp"
#include "lib/prime.hpp"
#include "lib/binary_search.hpp"

int main() {
    auto N = read_int();
    auto primes = primes_under(sqrt(N)+1);
    auto factors = prime_factorization(primes, N);
    int64_t ans = 0;
    for(auto [f, cnt] : factors) {
        // 1 + 2 + 3 + .. <= cnt
        // n(n+1)/2 <= cnt
        auto max_n = find_maximum_solution(0, cnt, [cnt=cnt](int64_t n){
            return n * (n+1) <= 2 * cnt;
        });
        ans += max_n;
    }
    cout << ans << LF;
}
