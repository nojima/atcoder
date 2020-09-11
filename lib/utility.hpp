#include <algorithm>
#include <vector>
using namespace std;

//-------------------------------------------------------------------------------------------------

template <typename T> inline void assign_max(T& x, const T& value) noexcept { x = max(x, value); }
template <typename T> inline void assign_min(T& x, const T& value) noexcept { x = min(x, value); }

//-------------------------------------------------------------------------------------------------

template <typename Int>
vector<int64_t> make_cumsum(const vector<Int>& v) {
    vector<int64_t> cumsum(v.size()+1);
    for (size_t i = 1; i < cumsum.size(); ++i) {
        cumsum[i] = cumsum[i-1] + v[i-1];
    }
    return cumsum;
}

// [first, last) の和を返す
inline int64_t sum_of(const vector<int64_t>& cumsum, int first, int last) noexcept {
    return cumsum[last] - cumsum[first];
}
