#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);

    int X, Y, A, B, C; cin >> X >> Y >> A >> B >> C;
    vector<int64_t> valueA(A), valueB(B), valueC(C);
    REP(i, A) cin >> valueA[i];
    REP(i, B) cin >> valueB[i];
    REP(i, C) cin >> valueC[i];
    sort(ALL(valueA), greater());
    sort(ALL(valueB), greater());
    sort(ALL(valueC), greater());

    vector<int64_t> v;
    v.insert(v.end(), valueA.begin(), valueA.begin() + X);
    v.insert(v.end(), valueB.begin(), valueB.begin() + Y);
    v.insert(v.end(), valueC.begin(), valueC.end());
    sort(ALL(v), greater());

    int64_t ans = 0;
    REP(i, X+Y) ans += v[i];
    cout << ans << '\n';
}
