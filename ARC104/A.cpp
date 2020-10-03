#include "lib/prelude.hpp"

/*
X+Y = A
X-Y = B

2X=A+B
X=(A+B)/2

2Y=A-B
Y=(A-B)/2
*/

int main() {
    int A = read_int();
    int B = read_int();
    cout << (A+B)/2 << " " << (A-B)/2 << endl;
}
