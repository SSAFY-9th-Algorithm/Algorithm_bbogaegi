//thanks to 세이언냐
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

/* 나무박멸
n*n 격자 - 나무의 그루수 & 벽의 정보
제초제를 뿌려 나무의 성장 억제
k의 범위만큼 대각선으로 퍼짐. 벽이 있는 경우 가로막혀 전파 X.
1. 인접한 네 개의 칸 중 나무가 있는 칸의 수만큼 나무 성장. (모든 나무 동시 성장)
2. 기존 나무들은 인접한 4개의 칸 중 벽, 다른 나무, 제초제 모두 없는 칸에 번식.
이때, 각 칸의 나무 그루 수에서 총 번식이 가능한 칸의 개수만큼 나누어진 그루수만큼 번식. (나머지 버림)
번식도 모든 나무 동시에 발생
3. 각 칸 중 제초제를 뿌렸을 때 나무가 가장 많이 박멸되는 칸에 제초제 뿌림.
나무가 없는 칸에 뿌리면 박멸되는 나무 없음. 나무가 있는 칸은 4개의 대각선 방향으로 k칸만큼 전파.
전파되는 도중 벽 OR 나무 없는 칸은 그 칸까지 제초제 뿌려지고 그 이후 칸으로 전파 x.
제초제 뿌려진 칸에는 C년만큼 제초제가 남아있다가 C+1 년째가 될 때 사라짐.
제초제 뿌려진 곳에 다시 제초제가 뿌려지면 새로 뿌려진 해부터 다시 C년 동안 제초제 유지.
 */

int n, m, k, c;
int MAP[21][21];
struct Tree {
	int y;
	int x;
	int age;
	int aroundTreeCnt;
};

vector<Tree>trees;
vector<Tree>newtrees;
int diry[4] = { -1, 1, 0, 0 };
int dirx[4] = { 0, 0, -1, 1 };
int tmpMAP[21][21];
int pestMAP[21][21];
int deadPestTreeCnt = 0;

int grow(Tree nowtree) {

	int aroundTreeCnt = 0;

	for (int i = 0; i < 4; i++) {
		int ny = nowtree.y + diry[i];
		int nx = nowtree.x + dirx[i];

		if (ny < 0 || nx < 0 || ny >= n || nx >= n)
			continue;

		if (MAP[ny][nx] > 0)
			aroundTreeCnt++;
	}

	return aroundTreeCnt;
}

void breed(Tree nowtree) {

	int canBreedCnt = 0;

	for (int i = 0; i < 4; i++) {
		int ny = nowtree.y + diry[i];
		int nx = nowtree.x + dirx[i];

		if (ny < 0 || nx < 0 || ny >= n || nx >= n)
			continue;

		if (tmpMAP[ny][nx] == 0 && pestMAP[ny][nx] == 0)
			canBreedCnt++;
	}

	if (canBreedCnt == 0)
		return;

	int breedScore = nowtree.age / canBreedCnt;

	for (int i = 0; i < 4; i++) {
		int ny = nowtree.y + diry[i];
		int nx = nowtree.x + dirx[i];

		if (ny < 0 || nx < 0 || ny >= n || nx >= n)
			continue;

		if (tmpMAP[ny][nx] == 0 && pestMAP[ny][nx] == 0) { //tmpMAP과 MAP 구분 사용 주의!!!
			MAP[ny][nx] += breedScore;
			newtrees.push_back({ ny, nx, MAP[ny][nx] });
		}
		else {
			for (int i = 0; i < newtrees.size(); i++) {
				if (newtrees[i].y == ny && newtrees[i].x == nx) {
					MAP[ny][nx] += breedScore;
					newtrees[i].age = MAP[ny][nx];
				}
			}
		}
	}

	return;
}

int dy[4] = { -1, 1, -1, 1 };
int dx[4] = { -1, 1, 1, -1 };

int findSpot(int y, int x) {
	int deadTreeCnt = MAP[y][x];

	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= k; j++) {
			int ny = y + dy[i] * j;
			int nx = x + dx[i] * j;

			if (ny < 0 || nx < 0 || ny >= n || nx >= n)
				break;

			if (MAP[ny][nx] <= 0 || pestMAP[ny][nx])
				break;

			deadTreeCnt += MAP[ny][nx];
		}
	}

	return deadTreeCnt;
}

void spreadMed(int y, int x) {

	pestMAP[y][x] = c;

	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= k; j++) {
			int ny = y + dy[i] * j;
			int nx = x + dx[i] * j;

			if (ny < 0 || nx < 0 || ny >= n || nx >= n)
				break;

			if (MAP[ny][nx] <= 0) {
				if (MAP[ny][nx] == 0 || MAP[ny][nx] == -2)
					pestMAP[ny][nx] = c;
				break;
			}

			//deadPestTreeCnt += MAP[ny][nx];
			pestMAP[ny][nx] = c;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (pestMAP[i][j] == c)
				MAP[i][j] = -2;
		}
	}

}


int main() {
	cin >> n >> m >> k >> c;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] > 0)
				trees.push_back({ i, j, MAP[i][j] });
		}
	}

	for (int t = 0; t < m; t++) {
		//성장시기
		int ts = trees.size();
		for (int i = 0; i < ts; i++) {
			int growage = grow(trees[i]);
			trees[i].aroundTreeCnt = growage;
			trees[i].age += growage;
			MAP[trees[i].y][trees[i].x] += growage;
		}
		// 번식
		memcpy(tmpMAP, MAP, sizeof(MAP));
		for (int i = 0; i < trees.size(); i++) {
			breed(trees[i]);
		}
		for (int i = 0; i < newtrees.size(); i++) {
			trees.push_back({ newtrees[i] });
		}
		newtrees.clear();

		// 제초제를 뿌릴 위치 선정
		//int de = 1;
		int maxDeadCnt = -1;
		int maxy = -1;
		int maxx = -1;
		int de = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (MAP[i][j] < 1)
					continue;

				int deadTreeCnt = findSpot(i, j);
				if (maxDeadCnt < deadTreeCnt) {
					maxDeadCnt = deadTreeCnt;
					maxy = i;
					maxx = j;
				}
			}
		}


		if (maxDeadCnt != -1)
			deadPestTreeCnt += maxDeadCnt;
		// 제초제 시간 줄이기
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (pestMAP[i][j] > 0)
					pestMAP[i][j]--;
				if (pestMAP[i][j] == 0 && MAP[i][j] == -2)
					MAP[i][j] = 0;
			}
		}
		// 제초제 뿌리기
		spreadMed(maxy, maxx);

		// 나무 정보 업데이트
		trees.clear();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (MAP[i][j] > 0)
					trees.push_back({ i,j,MAP[i][j] });
			}
		}
	}


	cout << deadPestTreeCnt;

}
