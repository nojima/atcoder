#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

bool is_palindrome(string_view prefix, string_view suffix) {
    string_view s = prefix.empty() ? suffix : prefix;
    REP(i, s.size()/2) {
        if (s[i] != s[s.length()-i-1]) {
            return false;
        }
    }
    return true;
}

int common_length(string_view prefix, string_view suffix) {
    int i = 0, j = suffix.length() - 1;
    while (i < (int)prefix.length() && j >= 0 && prefix[i] == suffix[j]) {
        ++i; --j;
    }
    return i;
}

int main() {
    int N; cin >> N;
    vector<string> S(N);
    vector<int64_t> C(N);
    REP(i, N) cin >> S[i] >> C[i];

    // (prefix, suffix) を状態として持つ。
    // ただし prefix == "" || suffix == "" でなければならない。
    struct State {
        string_view prefix;
        string_view suffix;
        bool start;
        int64_t weight;
        bool operator<(const State& rhs) const noexcept {
            return weight > rhs.weight;
        }
    };

    priority_queue<State> Q;
    set<tuple<string_view, string_view, bool>> visited;
    map<tuple<string_view, string_view, bool>, int64_t> dist;

    Q.push({"", "", true, 0});
    dist.insert({{"", "", true}, 0});

    int64_t ans = numeric_limits<int64_t>::max();
    while (!Q.empty()) {
        auto [prefix, suffix, start, _] = Q.top(); Q.pop();

        if (auto it = visited.find({prefix, suffix, start}); it != visited.end()) {
            continue;
        }
        visited.insert({prefix, suffix, start});
        if (!start && is_palindrome(prefix, suffix)) {
            ans = dist[{prefix, suffix, start}];
            break;
        }

        REP(i, N) {
            string_view new_prefix = prefix.empty() ? S[i] : prefix;
            string_view new_suffix = prefix.empty() ? suffix : S[i];
            int l = common_length(new_prefix, new_suffix);
            if (l != (int)new_prefix.length() && l != (int)new_suffix.length()) {
                continue;
            }
            new_prefix = new_prefix.substr(l);
            new_suffix = new_suffix.substr(0, new_suffix.length() - l);
            int64_t new_dist = dist[{prefix, suffix, start}] + C[i];
            if (auto it = dist.find({new_prefix, new_suffix, false}); it != dist.end() && new_dist >= it->second) {
                continue;
            }
            dist[{new_prefix, new_suffix, false}] = new_dist;
            Q.push({new_prefix, new_suffix, false, new_dist});
        }
    }

    if (ans == numeric_limits<int64_t>::max()) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}
