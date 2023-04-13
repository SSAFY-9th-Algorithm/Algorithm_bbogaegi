/*
세이 언니 비트 리스펙
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
using namespace std;

int N; 

void func(int num, int from, int mid, int to) {
	if (num == 1) {
		printf("%d %d\n", from, to);
		return;
	}

	func(num - 1, from, to, mid);
	printf("%d %d\n", from, to);
	func(num - 1, mid, from, to);
}

int main() {
	scanf("%d", &N);
	int n = 1 << N;
	n--;
	printf("%d\n", n);
	func(N, 1, 2, 3);

	return 0;
}
