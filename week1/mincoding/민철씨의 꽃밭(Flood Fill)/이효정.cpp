#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;

struct POS {
	int y;
	int x;
};

int MAP[501][501];

/*
	0 - 씨가 뿌려지지 않은상태
	1 - 씨가 뿌려진 상태
	2보다 크거나 같으면 꽃이 핀 상태(2인 날이 꽃이 피기 시작)
	-1 - 꽃이 폈다 진 상태(다시 꽃이 필 수 없음)
*/

int visited[501][501];
int N, M; // 세로, 가로

int day, maxDay, maxFlowers; // max가 붙은 변수들은 꽃이 최대로 핀 날에 대한 기록

int ydir[4] = { -1, 1, 0, 0 };
int xdir[4] = { 0, 0, -1, 1 };

// 꽃 상태가 모두 업데이트 되면 바로 그 날 펴있는 꽃 개수 카운트
void cntFlowers() {
	int cnt = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (visited[i][j] > 1)
				cnt++;
	if (cnt > maxFlowers)
	{
		maxDay = day;
		maxFlowers = cnt;
	}
}

// 하루가 지나자마자 꽃 상태 확인
void checkVisited(void) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (visited[i][j] > 0) {
				visited[i][j]++;
				if (visited[i][j] - 2 >= MAP[i][j])
					visited[i][j] = -1;
			}
		}
	}
}

void bfs(int y, int x) {
	queue<POS> q;
	q.push({ y, x });
	while (!q.empty()) {
		day++;
		checkVisited();
		cntFlowers();
		int curSize = q.size();
		for (int j = 0; j < curSize; j++) {
			POS now = q.front();
			q.pop();
			for (int i = 0; i < 4; i++) {
				int ny = now.y + ydir[i];
				int nx = now.x + xdir[i];
				if (ny < 0 || nx < 0 || ny >= N || nx >= M)
					continue;
				if (visited[ny][nx] != 0 || MAP[ny][nx] == 0) // MAP[ny][nx] == 0인 경우를 해주지 않으면 오답나오는 경우가 있음
					continue;
				visited[ny][nx] = 1;
				q.push({ ny, nx });
			}
		}
	}

}

int main(void) {
	POS start;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			cin >> MAP[i][j];
	}
	cin >> start.y >> start.x;
	visited[start.y][start.x] = 1;
	bfs(start.y, start.x);
	cout << maxDay << "일\n" << maxFlowers << "개\n";
	return 0;
}
