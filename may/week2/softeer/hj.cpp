#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

int H, K, R;

int task[1025][10];
vector<int> order[11];

void input() {
	scanf("%d %d %d", &H, &K, &R);
	int last = 1 << H;
	for (int i = 1; i <= last; i++) {
		for (int j = 0; j < K; j++) {
			scanf("%d", &task[i][j]);
		}
	}
}

int main(void) {
	input();
	order[1].push_back(2);
	order[1].push_back(1);
	if (R < H + 1) {
		printf("0\n");
		return 0;
	}
	for (int i = 2; i <= H; i++) {
		int vsize = order[i - 1].size();
		int rInc = 1 << (i - 1);
		for (int j = 0; j < vsize; j++) {
			if (i % 2 == 0) {
				order[i].push_back(order[i - 1][j]);
				order[i].push_back(order[i - 1][j] + rInc);
			}
			else {
				order[i].push_back(order[i - 1][j] + rInc);
				order[i].push_back(order[i - 1][j]);
			}
		}
	}
	int sum = 0;
	int lastDay = R - H - 1;
	int lastPerson = 1 << H;
	for (int i = 0; i <= lastDay; i++) {
		int taskNum = i / lastPerson;
		if (taskNum >= K)
			break;
		sum += task[order[H][i % lastPerson]][taskNum];
	}
	printf("%d\n", sum);
}
