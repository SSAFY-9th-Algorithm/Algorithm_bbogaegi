#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

int N; // 이닝수
int mat[51][10]; // 이닝 당 결과
int maxScore = 0;

int path[10];
int visited[10];

void input() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 1; j <= 9; j++) {
			scanf("%d", &mat[i][j]);
		}
	}
}

void rotate(int base[4]) {
	for (int i = 3; i > 0; i--) {
		base[i] = base[i - 1];
	}
}

int calcScore() {
	int outCount = 0;
	int idx = 1;
	int score = 0;
	int base[4] = { 0 };
	for (int i = 0; i < N; i++) {
		memset(base, 0, sizeof(base));
		for (outCount = 0; outCount < 3; idx++) {
			if (idx > 9)
				idx = 1;
			int now = mat[i][path[idx]];
			if (now == 0) {
				outCount++;
				continue;
			}
			else if (now < 3) {
				rotate(base);
				base[0] = now;
				for (int d = 1; d < now; d++) {
					if (base[3] > 0) {
						base[3] = 0;
						score++;
					}
					rotate(base);
				}
			}
			else {
				for (int d = 0; d < 3; d++) {
					if (base[d]) {
						base[d] = 0;
						score++;
					}
				}
				score++;
			}
			if (base[3] > 0) {
				base[3] = 0;
				score++;
			}
		}
	}
	return score;
}

void dfs(int level) {
	if (level == 10) {
		if (path[2] == 1 && path[3] == 5 && path[4] == 6 && path[5] == 7)
			int de = 1;
		int score = calcScore();
		if (maxScore < score) {
			maxScore = score;
			for (int i = 1; i < level; i++) {
				printf("%d ", path[i]);
			}
			printf("\n\n");
		}
		return;
	}
	for (int i = 1; i <= 9; i++) {
		if (visited[i])
			continue;
		visited[i] = 1;
		path[level] = i;
		dfs(level + 1);
		path[level] = 0;
		visited[i] = 0;
	}
}

void solution() {
	dfs(2);
}

int main() {
	input();
	path[1] = 4;
	visited[4] = 1;
	solution();
	printf("%d\n", maxScore);
	return 0;
}
