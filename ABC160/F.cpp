#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

static constexpr int64_t MOD = 1000000007;

inline int64_t add_mod(int64_t a, int64_t b) { return (a + b) % MOD; }
inline int64_t sub_mod(int64_t a, int64_t b) { return (a - b + MOD) % MOD; }
inline int64_t mul_mod(int64_t a, int64_t b) { return (a * b) % MOD; }

// 以下を満たすような (x, y) を返す。
//   ax + by = gcd(a, b)
pair<int64_t, int64_t> exgcd(int64_t a, int64_t b) noexcept {
    if (b == 0) return {1, 0};
    auto [x, y] = exgcd(b, a%b);
    return {y, x-(a/b)*y};
}

// a の逆元(>=0)を返す。a は MOD と互いに素でなければならない。
inline int64_t inverse(int64_t a) noexcept {
    auto x = exgcd(MOD, a).second % MOD;
    return x < 0 ? x + MOD : x;
}

//-----------------------------------------------------------------------------

vector<vector<int>> tree;
vector<bool> visited;
vector<int64_t> dp;
vector<int> subtree_size;
vector<int64_t> fact;
vector<int64_t> ans;

vector<int64_t> make_factorials(int n) {
    vector<int64_t> ret(n+1);
    ret[0] = 1;
    for (int i = 1; i <= n; ++i)
        ret[i] = mul_mod(ret[i-1], i);
    return ret;
}

void dfs1(int v) {
    visited[v] = true;
    subtree_size[v] = 1;
    int64_t a = 1;
    int64_t c = 1;

    for (int child : tree[v]) if (!visited[child]) {
        dfs1(child);
        subtree_size[v] += subtree_size[child];
        a = mul_mod(a, dp[child]);
        c = mul_mod(c, fact[subtree_size[child]]);
    }

    int64_t b = fact[subtree_size[v] - 1];

    // dp[v] = (Π dp[child]) * (Σ subtree_size[child])! / Π subtree_size[child]!
    dp[v] = mul_mod(a, mul_mod(b, inverse(c)));
}

void dfs2(int v, int64_t parent_dp, int64_t parent_subtree_size) {
    visited[v] = true;
    int64_t a = 1;
    int64_t c = 1;
    int subtree_size_v = 1;

    for (int child : tree[v]) if (!visited[child]) {
        subtree_size_v += subtree_size[child];
        a = mul_mod(a, dp[child]);
        c = mul_mod(c, fact[subtree_size[child]]);
    }
    subtree_size_v += parent_subtree_size;
    a = mul_mod(a, parent_dp);
    c = mul_mod(c, fact[parent_subtree_size]);

    int64_t b = fact[subtree_size_v - 1];

    ans[v] = mul_mod(a, mul_mod(b, inverse(c)));

    for (int child : tree[v]) if (!visited[child]) {
        int parent_subtree_size = subtree_size_v - subtree_size[child];
        int64_t parent_dp = a;
        parent_dp = mul_mod(parent_dp, inverse(dp[child]));
        parent_dp = mul_mod(parent_dp, fact[parent_subtree_size - 1]);
        parent_dp = mul_mod(parent_dp, inverse(c));
        parent_dp = mul_mod(parent_dp, fact[subtree_size[child]]);
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
    dfs2(0, 1, 0);

    REP(k, N) cout << ans[k] << '\n';
}
