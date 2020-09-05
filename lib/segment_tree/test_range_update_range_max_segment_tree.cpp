#include <iostream>
#include <random>
#include <cassert>
using namespace std;

#include "range_update_range_max_segment_tree.hpp"
#include "../debug.hpp"

template<typename T>
void print_segment_tree(const vector<T>& data, int index, int indent, int left, int right) {
    for (int i = 0; i < indent; ++i)
        cout << "  ";
    cout << "*" << data[index] << "  (" << left << ", " << right << ")" << '\n';
    int middle = (left + right) / 2;
    if (index * 2 + 1 < (int)data.size())
        print_segment_tree(data, index * 2 + 1, indent + 1, left, middle);
    if (index * 2 + 2 < (int)data.size())
        print_segment_tree(data, index * 2 + 2, indent + 1, middle, right);
}

template<typename T>
void print_segment_tree(const vector<T>& data) {
    print_segment_tree(data, 0, 0, 0, (int)(data.size() + 1) / 2);
}

void test_1() {
    int n = 100;
    RangeUpdateRangeMaxSegmentTree<int> sut(n);
    vector<int> expected(n);
    mt19937 rng(1234567890);

    for (int i = 0; i < 100000; ++i) {
        {
            int lo = rng() % n;
            int hi = rng() % n;
            int value = rng() % 10;
            if (lo > hi) swap(lo, hi);

            sut.range_update(lo, hi+1, value);

            for (int i = lo; i < hi+1; ++i)
                expected[i] = value;

            /*
            cout << "* lo=" << lo << ", hi=" << hi << ", value=" << value << endl;
            cout << "* expected = " << expected << endl;
            print_segment_tree(sut.data);
            print_segment_tree(sut.lazy);
            cout << endl;
            cout << endl;
            */
        }
        {
            int lo = rng() % n;
            int hi = rng() % n;
            if (lo > hi) swap(lo, hi);

            int v1 = sut.range_max(lo, hi+1);

            int v2 = numeric_limits<int>::min();
            for (int i = lo; i < hi+1; ++i)
                v2 = max(v2, expected[i]);

            if (v1 != v2) {
                cout << "lo=" << lo << ", hi=" << hi << endl;
                cout << "Expected: " << v2 << endl;
                cout << "Actual: " << v1 << endl;
                cout << endl;
                cout << "expected = " << expected << endl;
                cout << "data    = " << sut.data << endl;
                cout << endl;
                cout << endl;
            }
        }
    }
}

void test_2() {
    int n = 100;
    RangeUpdateRangeMaxSegmentTree<int64_t> sut(n);
    vector<int64_t> expected(n);
    mt19937 rng(1234567890);

    for (int i = 0; i < 100000; ++i) {
        {
            int lo = rng() % n;
            int hi = rng() % n;
            int64_t value = (int64_t)rng() * 1234567890;
            if (lo > hi) swap(lo, hi);

            sut.range_update(lo, hi+1, value);

            for (int i = lo; i < hi+1; ++i)
                expected[i] = value;

            /*
            cout << "* lo=" << lo << ", hi=" << hi << ", value=" << value << endl;
            cout << "* expected = " << expected << endl;
            print_segment_tree(sut.data);
            print_segment_tree(sut.lazy);
            cout << endl;
            cout << endl;
            */
        }
        {
            int lo = rng() % n;
            int hi = rng() % n;
            if (lo > hi) swap(lo, hi);

            int64_t v1 = sut.range_max(lo, hi+1);

            int64_t v2 = numeric_limits<int64_t>::min();
            for (int i = lo; i < hi+1; ++i)
                v2 = max(v2, expected[i]);

            if (v1 != v2) {
                cout << "lo=" << lo << ", hi=" << hi << endl;
                cout << "Expected: " << v2 << endl;
                cout << "Actual: " << v1 << endl;
                cout << endl;
                cout << "expected = " << expected << endl;
                cout << "data    = " << sut.data << endl;
                cout << endl;
                cout << endl;
            }
        }
    }
}

int main() {
    test_1();
    test_2();
}
