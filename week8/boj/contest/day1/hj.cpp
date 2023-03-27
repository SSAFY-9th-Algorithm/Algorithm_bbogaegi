#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Tree {
	int y;
	int x;
	int age;

	bool operator<(Tree next) const {
		return age > next.age;
	}
};

queue<Tree> trees;
queue<Tree> death_trees; // 죽은 나무에 대한 정보도 있어야함.

int N, M, K; // 지도 한 변의 크기, 나무 수, 시간의 흐름
int mat[11][11];
int A[11][11];

int ydir[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int xdir[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

void input() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
			mat[i][j] = 5;
		}
	}
	for (int i = 0; i < M; i++) {
		int y, x, age;
		cin >> y >> x >> age;
		trees.push({ y, x, age });
	}
}

void summer() {
	while (!death_trees.empty()) {
		Tree now = death_trees.front();
		death_trees.pop();
		mat[now.y][now.x] += now.age / 2;
	}
}

void solution() {
	static int k = 0;
	queue<Tree> temp;
	while (!trees.empty()) {
		Tree now = trees.front();
		trees.pop();
		if (mat[now.y][now.x] < now.age) {
			death_trees.push(now);
			continue;
		}
		mat[now.y][now.x] -= now.age;
		now.age++;
		temp.push(now);
	}
	summer();
	while (!temp.empty()) {
		Tree now = temp.front();
		temp.pop();
		if (now.age % 5 == 0) {
			for (int i = 0; i < 8; i++) {
				int ny = now.y + ydir[i];
				int nx = now.x + xdir[i];
				if (ny < 1 || nx < 1 || ny > N || nx > N)
					continue;
				trees.push({ ny, nx, 1 });
			}
		}
		trees.push(now);
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			mat[i][j] += A[i][j];
	}
}

int main(void) {
	input();
	for (int i = 0; i < K; i++)
		solution();
	cout << trees.size() << '\n';
	return 0;
}
