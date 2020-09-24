#pragma once
#include "lib/std.hpp"

template <class Func>
struct Fix {
    Func f;
    template <class... Args>
    decltype(auto) operator()(Args&&... args) const {
        return f(*this, forward<Args>(args)...);
    }
};
template <class Func>
Fix<std::decay_t<Func>> fix(Func&& f) {
    return {forward<Func>(f)};
}
