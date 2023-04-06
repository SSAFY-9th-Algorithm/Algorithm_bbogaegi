/* 테스트케이스 16 불통
10 130 8 8
-1 0 0 0 86 0 0 0 0 0 
0 27 0 0 0 0 0 0 0 0 
0 -1 0 -1 0 0 0 -1 0 69 
0 47 0 0 0 0 51 0 0 0 
0 0 0 0 0 72 0 0 0 0 
0 0 0 0 0 0 0 -1 0 0 
0 0 0 0 0 0 0 0 0 -1 
0 0 0 -1 0 0 0 0 55 0 
84 0 0 0 0 0 0 -1 0 0 
0 0 96 50 0 0 0 0 0 0 

답 : 18459
나의출력 : 18484
*/

#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

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

		if (MAP[ny][nx] == 0 && pestMAP[ny][nx] == 0) {
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

	int deadTreeCnt = 0;

	if (MAP[y][x] <= 0)
		return deadTreeCnt;

	deadTreeCnt += MAP[y][x];

	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= k; j++) {
			int ny = y + dy[i] * j;
			int nx = x + dx[i] * j;

			if (ny < 0 || nx < 0 || ny >= n || nx >= n)
				continue;

			if (MAP[ny][nx] <= 0)
				break;

			deadTreeCnt += MAP[ny][nx];
		}
	}

	return deadTreeCnt;

}

void spreadMed(int y, int x) {

	//deadPestTreeCnt += MAP[y][x];
	pestMAP[y][x] = c;
	MAP[y][x] = -2;

	//if (deadPestTreeCnt <= 0)
	//	return;

	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= k; j++) {
			int ny = y + dy[i] * j;
			int nx = x + dx[i] * j;

			if (ny < 0 || nx < 0 || ny >= n || nx >= n)
				continue;

			if (MAP[ny][nx] <= 0) {
				if (MAP[ny][nx] == 0)
					pestMAP[ny][nx] = c;
				else if (MAP[ny][nx] == -2)
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

		memcpy(tmpMAP, MAP, sizeof(MAP));
		for (int i = 0; i < trees.size(); i++) {
			breed(trees[i]);
		}
		for (int i = 0; i < newtrees.size(); i++) {
			trees.push_back({ newtrees[i] });
		}
		newtrees.clear();
		//memset(tmpMAP, 0, sizeof(tmpMAP));

		int maxDeadCnt = -21e8;
		int maxy = 0;
		int maxx = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (MAP[i][j] < 0)
					continue;
				int deadTreeCnt = findSpot(i, j);
				if (maxDeadCnt < deadTreeCnt) {
					maxDeadCnt = deadTreeCnt;
					maxy = i;
					maxx = j;
				}
			}
		}

		deadPestTreeCnt += maxDeadCnt;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (pestMAP[i][j] > 0)
					pestMAP[i][j]--;
				if (pestMAP[i][j] == 0 && MAP[i][j] == -2)
					MAP[i][j] = 0;
			}
		}

		spreadMed(maxy, maxx);

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
