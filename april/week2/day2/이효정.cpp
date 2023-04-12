// https://www.acmicpc.net/problem/11729

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cmath>

using namespace std;

void hanoi(int n, int from, int sub, int to) {

   if (n == 1) {
        printf("%d %d\n", from, to);
		return;
	}

	hanoi(n - 1, from, to, sub);

	printf("%d %d\n", from, to);

	hanoi(n-1, sub, from, to);
}


int main(void)

{

	int n;
	scanf("%d", &n);

	printf("%lld\n", (long long)pow(2, n) - 1);

	hanoi(n, 1, 2, 3);


}
