#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

/* 
map을 2씩 크게 만들어서 그 라인이 채워졌으면 
다음으로 넘어가게
왼쪽 오른쪽으로 채울 땐 세로로 연결된 곳이 있는지,
위쪽 아래쪽으로 채울 땐 가로로 연결된 곳이 있는지 확인해야 함.

여러 방법(DFS)이 있으면 전선 길이의 합이 최소!

우선 순위 -> 최대한 많은 Core에 전원 연결, 최소 길이
priority_queue를 이용해보면 어떨까

-> 코드가 짤려서 안돌아가던 거였음 ㄹㅈㄷ
*/

struct Node {
	int core;
	int sum;

	bool operator<(Node next) const {
		if (core < next.core)
			return true;
		if (core > next.core)
			return false;
		if (sum > next.sum)
			return true;
		if (sum < next.sum)
			return false;
		return false;
	}
};

struct Pos {
	int y;
	int x;
};

int N; // 가로,세로크기
int mat[15][15];
int visited[4][15]; // 상하좌우
vector<Pos> cores;
Node minSum = { 0, 0 }; // core개수는 최대, 길이합은 최소
Node totalSum = { 0, 0 };
int ydir[] = { -1, 1, 0, 0 };
int xdir[] = { 0, 0, -1, 1 };

void reset() {
	memset(mat, 0, sizeof(mat));
	memset(visited, 0, sizeof(visited));
	cores.clear();
	minSum = { 0, 0 };
}

void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> mat[i][j];
			if (mat[i][j]) {
				if (1 == i) { // top
					visited[0][j] = -1;
				}
				else if (N == i) { // bottom
					visited[1][j] = -1;
				}
				else if (1 == j) { // left
					visited[2][i] = -1;
				}
				else if (N == j) { // right
					visited[3][i] = -1;
				}
				else {
					cores.push_back({ i, j });
					continue;
				}
				totalSum.core++;
			}
		}
	}
}

int allFlag = 0;
void dfs(int vIdx) {
	int flag = 0;
	if (vIdx == cores.size()) {
		flag = 1;
		if (minSum.core > totalSum.core)
			return;
		if (minSum < totalSum)
			minSum = totalSum;
		return;
	}
	Pos now = cores[vIdx];
	for (int i = 0; i < 4; i++) {
		int ny = now.y + ydir[i];
		int nx = now.x + xdir[i];
		if (ny < 1 || nx < 1 || ny >= N + 1 || nx >= N + 1)
			continue;
		if (mat[ny][nx])
			continue;
		int failFlag = 0;
		// top부터 봄
		// bottom
		if (i < 2) {
			if (visited[i][now.x])
				continue;
			for (int j = 1; j < N; j++) {
				// left 확인
				if (i == 0 && j < now.y
					|| i == 1 && j > now.y){
					if (visited[2][j] && visited[2][j] >= now.x - 1) {
						failFlag = 1;
						break;
					}
					if (visited[3][j] && visited[3][j] >= N - now.x) {
						failFlag = 1;
						break;
					}
				}
			}
			if (failFlag)
				continue;

			// 만약 전선이 교차되는가?
			for (int y = 1; i == 0 && y < now.y; y++) {
				if (mat[y][now.x]) {
					failFlag = 1;
					break;
				}
			}
			for (int y = now.y + 1; i == 1 && y <= N; y++) {
				if (mat[y][now.x]) {
					failFlag = 1;
					break;
				}
			}
			if (failFlag)
				continue;
			// i == 0일 땐 -1을 해줘야함
			visited[i][now.x] = abs(i * N - now.y) - (int)(!i);
			totalSum.sum += visited[i][now.x];
			totalSum.core++;
			flag = 1;
		}
		else {
			if (visited[i][now.y])
				continue;
			for (int j = 1; j < N; j++) {
				// left 확인
				if (i == 2 && j < now.x
				    || i == 3 && j > now.x) {
					if (visited[0][j] && visited[0][j] >= now.y - 1) {
						failFlag = 1;
						break;
					}
					if (visited[1][j] && visited[1][j] >= N - now.y) {
						failFlag = 1;
						break;
					}
				}
			}
			if (failFlag)
				continue;

			for (int x = 1; i == 2 && x < now.x; x++) {
				if (mat[now.y][x]) {
					failFlag = 1;
					break;
				}
			}
			for (int x = now.x + 1; i == 3 && x <= N; x++) {
				if (mat[now.y][x]) {
					failFlag = 1;
					break;
				}
			}
			if (failFlag)
				continue;
			visited[i][now.y] = abs((i - 2) * N - now.x) - (int)(!(i - 2));
			totalSum.sum += visited[i][now.y];
			totalSum.core++;
			flag = 2;
		}
		dfs(vIdx + 1);
		if (flag) {
			totalSum.core--;
			if (flag == 1) {
				totalSum.sum -= visited[i][now.x];
				visited[i][now.x] = 0;
			}
			else {
				totalSum.sum -= visited[i][now.y];
				visited[i][now.y] = 0;
			}
		}
	}
	if (!allFlag)
		dfs(vIdx + 1);
}


int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		reset();
		// input
		input();
		// solve
		/*
			벡터에서 코어 하나씩 꺼내면서 4방향으로 보기
		*/
		dfs(0); // vector idx
		// output
		cout << "#" << tc << " " << minSum.sum << '\n';
	}
	return 0;
}
