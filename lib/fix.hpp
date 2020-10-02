#pragma once
#include "lib/std.hpp"

template<class Func>
struct Fix {
    Func f;
    explicit Fix(Func&& f): f(forward<Func>(f)) {}
    template<class... Args>
    decltype(auto) operator()(Args&&... args) const {
        return f(*this, forward<Args>(args)...);
    }
};
