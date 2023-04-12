#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
using namespace std;
using ll = long long;

int N; // 1 <= N <= 20

void func(int level, int from, int bia, int to) {
    // 기저조건 -> level == 1 즉, 옮겨야할 블록이 1개가 남았을 때
    if (level == 1) {
        printf("%d %d\n", from, to);
        return;
    }
    // 재귀 구성
    // 1 -> 2
    func(level - 1, from, to, bia);
    printf("%d %d\n", from, to);
    // 2 -> 3
    func(level - 1, bia, from, to);
}

int main() {
    scanf("%d", &N);
    // 경우의 수는 2^N - 1
    int res = 1 << N;
    res--;
    printf("%d\n", res);
    // 경로 찾기
    func(N, 1, 2, 3);

    return 0;
}
