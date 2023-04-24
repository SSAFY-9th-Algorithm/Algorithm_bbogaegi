#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
using namespace std;

int ydir[] = { 0,0,-1,-1,-1,0,1,1,1 };
int xdir[] = { 0,-1,-1,0,1,1,1,0,-1 };

int N, M;
int MAP[101][101][3]; // 0: 물양, 1: 구름으로 물이 증가한 칸, 2: 구름

void input() {
	scanf("%d %d", &N, &M);
	for(int i=0;i<N;i++) 
		for (int j = 0; j < N; j++) {
			scanf("%d", &MAP[i][j][0]);
		}
}

bool outRange(int y, int x) {
	return y < 0 || x < 0 || y >= N || x >= N;
}

void wCOPY(int y, int x) {
	int diry[] = { -1,-1,1,1 };
	int dirx[] = { -1,1,1,-1 };
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		int ny = y + diry[i];
		int nx = x + dirx[i];

		if (outRange(ny, nx))
			continue;
		if (!MAP[ny][nx][0])
			continue;
		cnt++;
	}
	MAP[y][x][0] += cnt;
}

void waterCopy() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j][1])
				wCOPY(i, j);
		}
	}
}

void MOVE(int d, int s) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!MAP[i][j][2])
				continue;
			int ny = i + ydir[d] * s;
			int nx = j + xdir[d] * s;

			ny = (ny + 75*N) % N;
			nx = (nx + 75*N) % N;

			// 해당칸 물 증가
			MAP[ny][nx][1] = 1;
			MAP[ny][nx][0]++;
			// 구름이 사라짐
			MAP[i][j][2] = 0;
		}
	}
}

void mCLOUD() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// 구름이 사라졌던 칸은 continue
			if (MAP[i][j][1]) {
				MAP[i][j][1] = 0;
				continue;
			}
			if (MAP[i][j][0] >= 2) {
				MAP[i][j][0] -= 2;
				MAP[i][j][2] = 1;
			}
		}
	}
}

int getSum() {
	int sum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			sum += MAP[i][j][0];
	}
	return sum;
}

void print(int idx) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%2d ", MAP[i][j][idx]);
		}
		printf("\n");
	}
}

void solve() {
	// 초기 구름
	MAP[N - 1][0][2] = 1, MAP[N - 1][1][2] = 1, MAP[N - 2][0][2] = 1, MAP[N - 2][1][2] = 1;
	for (int i = 0; i < M; i++) {
		int d, s;
		scanf("%d %d", &d, &s);
		// 구름 이동
		MOVE(d, s);
		// 물복사
		waterCopy();
		// 구름 생성
		mCLOUD();
	}
	int res = getSum();
	printf("%d\n", res);
}

int main() {
	//freopen("input.txt", "r", stdin);
	input();
	solve();
	return 0;
}
