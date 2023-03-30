#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    int tmp;
    while (b != 0)
    {
        tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        // reset
        int M, N, x, y;
        // input
        cin >> M >> N >> x >> y;
        // solve
        int year = 1;
        int last =lcm(M, N);

        while (true)
        {
            if (x > last) {
                year = -1;
                break;
            }
            if ((x - 1) % N + 1 == y) {
                year = x;
                break;
            }
            x += M;
        }
        //output
        cout << year << '\n';
    }
    return 0;
}
