#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

struct Tree {
	int y;
	int x;
	int mnt;
};

int n; // 격자 크기(5, 20)
int m; // 박멸 진행되는 해 수(1, 1000)
int k; // 제초제 확산 범위(1, 20)
int c; // 제초제 남아있는 범위 (1, 10)

int mat[21][21]; // -1은 벽, 양수값은 나무, 제초제 -2
int bmat[21][21]; // 번식 정보 담기!
int kmat[21][21]; // 제초제 시간 정보 담기!

// 상 좌 하 우
int ydir[] = { -1, 0, 1, 0 };
int xdir[] = { 0, -1, 0, 1 };

// 대각선
int dydir[] = { -1, 1, 1, -1 };
int dxdir[] = { 1, 1, -1, -1 };

int res; // m년동안 총 박멸한 나무의 그루 수

// 번식 가능한 방향의 좌표를 담고 있을 것
// Tree 구조체에서 mnt만 무시하면서 재활용
vector<Tree> positive_dir;

void print_mat(int matt[21][21]) {
	cout << "------------------\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%3d ", matt[i][j]);
		}
		cout << "\n";
	}
	cout << "------------------\n";
}

// 대각선 합이 최대가 되는 좌표 + 더한 값을 반환
static Tree diagonal() {
	Tree maxSum = { 0, 0, 0 };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			// 트리가 있는 곳에 제초제를 뿌린다 생각
			if (mat[i][j] < 1)
				continue;
			Tree now = { i, j, mat[i][j] };
			int sum = now.mnt;
			for (int d = 0; d < 4; d++) {
				for (int g = 1; g <= k; g++) {
					int ny = now.y + dydir[d] * g;
					int nx = now.x + dxdir[d] * g;
					if (ny < 0 || nx < 0 || ny >= n || nx >= n)
						break;
					if (mat[ny][nx] < 1)
						break;
					sum += mat[ny][nx];
				}
			}
			if (maxSum.mnt < sum) {
				maxSum = { now.y, now.x, sum };
			}
		}
	}
	return maxSum;
}

void input() {
	scanf("%d %d %d %d", &n, &m, &k, &c);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &mat[i][j]);
			/*if (mat[i][j] > 0) {
				trees.push_back({ i, j, mat[i][j] });
			}*/
		}
	}
}

void grow() {
	print_mat(mat);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (mat[i][j] > 0) {
				Tree now = { i, j, mat[i][j] };
				int incMnt = 0;
				for (int d = 0; d < 4; d++) {
					int ny = now.y + ydir[d];
					int nx = now.x + xdir[d];
					if (ny < 0 || nx < 0 || ny >= n || nx >= n)
						continue;
					if (mat[ny][nx] > 0)
						incMnt++;
				}
				mat[i][j] += incMnt;
			}
		}
	}
	print_mat(mat);
}

void breed() {
	memset(bmat, 0, sizeof(bmat));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (mat[i][j] > 0) {
				Tree now = { i, j, mat[i][j] };
				int mount = now.mnt;
				if (mount == 0) // 양이 0이면 번식 못함
					continue;
				positive_dir.clear();
				for (int d = 0; d < 4; d++) {
					int ny = now.y + ydir[d];
					int nx = now.x + xdir[d];
					if (ny < 0 || nx < 0 || ny >= n || nx >= n)
						continue;
					if (mat[ny][nx] != 0)
						continue;
					positive_dir.push_back({ ny, nx, 0 });
				}
				int pNum = positive_dir.size();
				if (!pNum)
					continue;
				mount /= pNum;
				if (mount == 0)
					continue;
				for (int d = 0; d < pNum; d++) {
					Tree pos = positive_dir[d];
					bmat[pos.y][pos.x] += mount;
				}
			}
		}
	}
	printf("---------bmat------\n");
	print_mat(bmat);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			mat[i][j] += bmat[i][j];
		}
	}
	print_mat(mat);
}

int kill_tree(int ntime) {
	Tree target = diagonal();
	for (int d = 0; d < 4; d++) {
		for (int g = 0; g <= k; g++) {
			int ny = target.y + dydir[d] * g;
			int nx = target.x + dxdir[d] * g;
			if (ny < 0 || nx < 0 || ny >= n || nx >= n)
				break;
			if (mat[ny][nx] == -1)
				break;
			kmat[ny][nx] = ntime + c;
			mat[ny][nx] = -2;
			if (mat[ny][nx] == 0)
				break;
		}
	}
	return target.mnt;
}

void reset_kill(int ntime) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (kmat[i][j] == ntime) {
				kmat[i][j] = 0;
				mat[i][j] = 0;
			}
		}
	}
}

int main() {
	input();
	int res = 0;
	for (int rtime = 1; rtime <= m; rtime++) {
		reset_kill(rtime);
		grow();
		breed();
		int kNum = kill_tree(rtime);
		printf("%d\n\n", kNum);
		res += kNum;
		print_mat(mat);
	}
	printf("%d\n", res);
}
