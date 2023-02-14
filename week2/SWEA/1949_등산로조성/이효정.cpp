#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

struct Node {
	int y;
	int x;
};

int K, N;
int mat[8][8] = { 0, };
int ydir[4] = { -1, 1, 0, 0 };
int xdir[4] = { 0, 0, -1, 1 };
int visited[8][8];
int flag;
int maxDist;

void dfs(Node start, int dist) {
	for (int i = 0; i < 4; i++) {
		int ny = start.y + ydir[i];
		int nx = start.x + xdir[i];
		if (ny < 0 || nx < 0 || ny >= N || nx >= N)
			continue;
		if (visited[ny][nx])
			continue;
		if (mat[ny][nx] < mat[start.y][start.x]) {
			visited[ny][nx] = 1;
			dist++;
			maxDist = max(dist, maxDist);
			dfs({ ny, nx }, dist);
			dist--;
			visited[ny][nx] = 0;
		}
		else {
			if (flag == 0) {
				int dif = mat[ny][nx] - mat[start.y][start.x] + 1;
				if (dif > K)
					dif = K;
				for (int i = 1; i <= dif; i++) {
					flag = 1;
					mat[ny][nx] -= i;
					if (mat[ny][nx] < mat[start.y][start.x]) {
						visited[ny][nx] = 1;
						dist++;
						maxDist = max(dist, maxDist);
						dfs({ ny, nx }, dist);
						dist--;
						visited[ny][nx] = 0;
					}
					flag = 0;
					mat[ny][nx] += i;
				}
			}
		}
	}
}

int main(void) {
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		memset(mat, 0, sizeof(mat));
		memset(visited, 0, sizeof(visited));
		vector<Node> vec[21];
		int MAX = 0;
		cin >> N >> K;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> mat[i][j];
				vec[mat[i][j]].push_back({ i, j });
				if (MAX < mat[i][j])
					MAX = mat[i][j];
			}
		}
		maxDist = 0;
		for (int i = 0; i < vec[MAX].size(); i++) {
			Node maxNode = vec[MAX][i];
			memset(visited, 0, sizeof(visited));
			visited[maxNode.y][maxNode.x] = 1;
			dfs(maxNode, 1);
		}
		cout << "#" << tc << " " << maxDist << "\n";
	}
}