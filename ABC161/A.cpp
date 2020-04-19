#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int X, Y, Z;
    cin >> X;
    cin >> Y;
    cin >> Z;

    swap(X, Y);
    swap(X, Z);

    cout << X << " " << Y << " " << Z << "\n";

    return 0;
}
