#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

int main() {
    int64_t a, b, c, d; cin >> a >> b >> c >> d;
    int64_t m = max({
        a * c,
        a * d,
        b * c,
        b * d,
    });
    cout << m << endl;
}
