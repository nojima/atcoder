#include <iostream>
#include <vector>
#include <optional>

namespace std {
    template <typename T, typename U>
    ostream& operator<<(ostream& os, const pair<T, U>& p) {
        os << "(" << p.first << ", " << p.second << ")";
        return os;
    }

    template <typename T>
    ostream& operator<<(ostream& os, const vector<T>& v) {
        os << "[";
        bool first = true;
        for (const auto& x : v) {
            if (first) {
                first = false;
            } else {
                os << ", ";
            }
            os << x;
        }
        os << "]";
        return os;
    }

    template <typename T>
    ostream& operator<<(ostream& os, const optional<T>& v) {
        if (v)
            os << *v;
        else
            os << "nullopt";
        return os;
    }
}
