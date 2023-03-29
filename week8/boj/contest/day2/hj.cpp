#include <iostream>
#include <string.h>
using namespace std;

struct Smell {
	int num;
	int stime;
};

struct Shark {
	int y;
	int x;
	int alive;
	int ndir;
	int dir[5][4]; // 상하좌우 1부터 시작
};

int N, M, k; // N은 20, M: N^2, k: 1000

int mat[21][21]; // 상어들의 현재 위치를 담아둘 곳
int remain; // 남은 상어 수
Smell smells[21][21];
Shark sharks[401];
int ydir[5] = { 0, -1, 1, 0, 0 };
int xdir[5] = { 0, 0, 0, -1, 1 };

void input() {
	cin >> N >> M >> k;
	remain = M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> mat[i][j];
			if (mat[i][j] > 0) {
				smells[i][j] = { mat[i][j], 1 };
				sharks[mat[i][j]] = { i, j, 1, 0, };
			}
		}
	}
	for (int i = 1; i <= M; i++) {
		int num;
		cin >> num;
		sharks[i].ndir = num;
	}
	for (int i = 1; i <= M; i++) {
		for (int j = 0; j < 4; j++) {
			for (int z = 0; z < 4; z++) {
				cin >> sharks[i].dir[j + 1][z];
			}
		}
	}
}

int solution() {
	int t = 0;
	int ny = 0;
	int nx = 0;
	int positive[5] = { 0 }; // 아무 냄새 없는 방향
	int pNum = 0; // 아무 냄새 없는 방향에 대한 개수

	// 내 냄새가 있는 방향은 무조건 존재함(이전에 내가 있던 위치)
	int myPositive[5] = { 0 }; // 내 냄새 있는 방향

	while (t < 1000 && remain > 1) {
		++t;
		// 모든 상어의 위치를 이동시킨다.
		for (int i = 1; i <= M; i++) {
			Shark now = sharks[i];
			if (now.alive == 0)
				continue;
			memset(positive, 0, sizeof(positive));
			memset(myPositive, 0, sizeof(myPositive));
			pNum = 0;
			for (int d = 1; d < 5; d++) {
				ny = now.y + ydir[d];
				nx = now.x + xdir[d];
				if (ny < 0 || nx < 0 || ny >= N || nx >= N)
					continue;
				// 칸에 냄새 존재하는데 없어져야한다면
				if (smells[ny][nx].num > 0) {
					int temp1 = t - smells[ny][nx].stime;
					if (t - smells[ny][nx].stime >= k) {
						smells[ny][nx] = { 0, 0 };
					}
				}

				if (smells[ny][nx].num == 0) {
					positive[d] = 1;
					pNum++;
				}
				else if (smells[ny][nx].num == i) {
					myPositive[d] = 1;
				}
				else { // 냄새가 있는데 이미 나보다 작은 애가 존재하는 곳이면 positive로 봄
					if (mat[ny][nx] > 0 && mat[ny][nx] < i) {
						positive[d] = 1;
						pNum++;
					}
				}
			}
			mat[now.y][now.x] = 0;
			int nextDir = 0;
			if (pNum == 0) { // 아무 냄새 없는 칸이 존재하지 않음
				for (int i = 0; i < 4; i++) {
					nextDir = now.dir[now.ndir][i];
					if (myPositive[nextDir])
						break;
				}
			}
			else {
				for (int i = 0; i < 4; i++) {
					nextDir = now.dir[now.ndir][i];
					if (positive[nextDir])
						break;
				}
			}
			ny = now.y + ydir[nextDir];
			nx = now.x + xdir[nextDir];
			// 작은 번호부터 옮기기 때문에 
			// 나보다 작은 번호가 존재하면 나는 죽음
			if (mat[ny][nx] > 0 && mat[ny][nx] < i) {
				sharks[i].alive = 0;
				remain--;
				if (remain < 2)
					return t;
				continue;
			}
			mat[ny][nx] = i;
			smells[ny][nx] = { i, t + 1 };
			sharks[i].y = ny;
			sharks[i].x = nx;
			sharks[i].ndir = nextDir;
		}
	}
	if (t == 1000)
		return -1;
	return t;
}

int main(void) {
	input();
	cout << solution();
	return 0;
}
