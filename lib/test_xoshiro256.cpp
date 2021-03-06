#include "prelude.hpp"
#include "xoshiro256.hpp"

int main() {
    Xoshiro256 engine;
    normal_distribution dist(1.0, 0.5);
    REP(i, 100) {
        auto r = dist(engine);
        cout << r << '\n';
    }
    cout << "----" << endl;
    REP(i, 1000) {
        auto r = engine.next_double();
        cout << r << '\n';
    }
}
