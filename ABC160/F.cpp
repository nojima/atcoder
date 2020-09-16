#include <algorithm>
#include <iostream>
#include <vector>
#include <boost/operators.hpp>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

constexpr int MOD = 1000000007;

// ax + by = gcd(a, b) を満たすような整数 x,y を返す。
pair<int64_t, int64_t> exgcd(int a, int b) noexcept {
    if (b == 0) return {1, 0};
    auto [x, y] = exgcd(b, a%b);
    return {y, x-(a/b)*y};
}

// a を m で割った余り(>=0)を返す。
constexpr inline int mod(int a, int m) noexcept {
    int r = a % m;
    return r < 0 ? r + m : r;
}

// a の逆元を返す。a は MOD と互いに素でなければならない。
inline int inverse(int a) noexcept {
    return mod(exgcd(MOD, a).second, MOD);
}

struct ModInt : private boost::operators<ModInt> {
    int value;
    constexpr ModInt() noexcept : value(0) {}
    constexpr explicit ModInt(int value) noexcept
        : value(mod(value, MOD)) {}
    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {
        value += rhs.value;
        if (value > MOD) value -= MOD;
        return *this;
    }
    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {
        value -= rhs.value;
        if (value < 0) value += MOD;
        return *this;
    }
    constexpr ModInt& operator*=(const ModInt& rhs) noexcept {
        value = ((int64_t)value * rhs.value) % MOD;
        return *this;
    }
    ModInt& operator/=(const ModInt& rhs) noexcept {
        value = ((int64_t)value * inverse(rhs.value)) % MOD;
        return *this;
    }
    constexpr bool operator<(const ModInt& rhs) const noexcept {
        return value < rhs.value;
    }
    constexpr bool operator==(const ModInt& rhs) const noexcept {
        return value == rhs.value;
    }
};
ostream& operator<<(ostream& os, const ModInt& rhs) {
    os << rhs.value;
    return os;
}
istream& operator>>(istream& is, ModInt& rhs) {
    int i; is >> i;
    rhs.value = mod(i, MOD);
    return is;
}
constexpr inline ModInt operator""_m(unsigned long long value) noexcept {
    return ModInt((int)value);
}

//-----------------------------------------------------------------------------

vector<vector<int>> tree;
vector<bool> visited;
vector<ModInt> dp;
vector<int> subtree_size;
vector<ModInt> fact;
vector<ModInt> ans;

vector<ModInt> make_factorials(int n) {
    vector<ModInt> ret(n+1);
    ret[0] = 1_m;
    for (int i = 1; i <= n; ++i)
        ret[i] = ret[i-1] * ModInt(i);
    return ret;
}

void dfs1(int v) {
    visited[v] = true;
    subtree_size[v] = 1;
    ModInt a = 1_m;
    ModInt c = 1_m;

    for (int child : tree[v]) if (!visited[child]) {
        dfs1(child);
        subtree_size[v] += subtree_size[child];
        a *= dp[child];
        c *= fact[subtree_size[child]];
    }

    ModInt b = fact[subtree_size[v] - 1];

    // dp[v] = (Π dp[child]) * (Σ subtree_size[child])! / Π subtree_size[child]!
    dp[v] = a * b / c;
}

void dfs2(int v, ModInt parent_dp, int parent_subtree_size) {
    visited[v] = true;
    ModInt a = 1_m;
    ModInt c = 1_m;
    int subtree_size_v = 1;

    for (int child : tree[v]) if (!visited[child]) {
        subtree_size_v += subtree_size[child];
        a *= dp[child];
        c *= fact[subtree_size[child]];
    }
    subtree_size_v += parent_subtree_size;
    a *= parent_dp;
    c *= fact[parent_subtree_size];

    ModInt b = fact[subtree_size_v - 1];

    ans[v] = a * b / c;

    for (int child : tree[v]) if (!visited[child]) {
        int parent_subtree_size = subtree_size_v - subtree_size[child];
        ModInt parent_dp = a;
        parent_dp /= dp[child];
        parent_dp *= fact[parent_subtree_size - 1];
        parent_dp /= c;
        parent_dp *= fact[subtree_size[child]];
        dfs2(child, parent_dp, parent_subtree_size);
    }
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);

    int N; cin >> N;
    tree.resize(N);
    visited.resize(N);
    dp.resize(N);
    subtree_size.resize(N);
    ans.resize(N);
    REP(i, N-1) {
        int a, b; cin >> a >> b; --a; --b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    fact = make_factorials(N);

    fill(ALL(visited), false);
    dfs1(0);
    fill(ALL(visited), false);
    dfs2(0, 1_m, 0);

    REP(k, N) cout << ans[k] << '\n';
}
