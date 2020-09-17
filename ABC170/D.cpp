#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

int main() {
    int N; cin >> N;
    vector<int> A(N);
    REP(i, N) cin >> A[i];

    sort(ALL(A));
    int Amax = *max_element(ALL(A));

    set<int> dups;
    int prev = -1;
    for (int a : A) {
        if (a == prev) dups.insert(a);
        prev = a;
    }

    int ans = 0;
    vector<bool> sieve(Amax+1);
    for (int a : A) {
        if (!sieve[a] && dups.count(a) == 0) { ++ans; }
        for (int i = 1; a*i <= Amax; ++i) {
            sieve[a*i] = true;
        }
    }

    cout << ans << '\n';
}
