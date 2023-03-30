#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct Node {
	int y;
	int x;
	int dir; // 이동했던 방향, 1234순서로 상, 하, 좌, 우
};

int N, M, R, C, L; // 맵세로, 가로, 맨홀세로위치, 맨홀가로위치, 탈출후소요시간

int mat[51][51]; // map
int visited[51][51];

/*
뻘짓의 흔적 (탈주범을 잡는건지 나를 잡는건지...😂)
#1. map은 N x M 사이즈 -> N x N 인줄 알았음
#2. 모든 경우의 수 함수 안에서 때려박으니 수정이 어려움
#2-1. 터널 모양에 따라 이동이 불가능한 경우도 있을텐데 파악하지 못함
#2-2. 다음번 갈 곳의 터널 모양도 고려해야하고, 현재 터널의 모양도 고려해야한다

결론: 함수 단위로 쪼개놓으면 수정에 대해 편할 것 같다
     왜냐하면, 어디는 제대로 수정하고, 어디는 제대로 수정하지 않고 하면서 뻘짓을 많이 함,,
     나중에 리팩토링할 예정
*/


/*
tunnel 정보
1 -> 4방향
2 -> 상하
3 -> 좌우
4 -> 상, 우
5 -> 하, 우
6 -> 하, 좌
7 -> 상, 좌
*/

/*
	반드시 1개 이상의 터널이 있음이 보장
	L 1이상 20이하
*/
void reset() {
	memset(mat, 0, sizeof(mat));
	memset(visited, 0, sizeof(mat));
}

void input() {
	cin >> N >> M >> R >> C >> L;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> mat[i][j];
	visited[R][C] = 1;
}

int floodfill() {
	int total = 1;
	queue<Node> q;
	q.push({ R, C, 0 });
	while (!q.empty()) {
		int cursize = q.size();
		for (int c = 0; c < cursize; c++) {
			Node now = q.front();
			q.pop();
			if (visited[now.y][now.x] == L)
				return total;
			int tunnel = mat[now.y][now.x]; // 현재 터널 정보
			if (tunnel < 1)
				continue;
			if (now.dir != 2 && now.y - 1 >= 0 && (tunnel < 3 || tunnel == 4 || tunnel == 7)) {
				Node next = now;
				next.y -= 1;
				int nextTunnel = mat[next.y][next.x];
				if (nextTunnel != 0 
					&& !visited[next.y][next.x]
					&& !(nextTunnel == 3 || nextTunnel == 4 || nextTunnel == 7 )) {
					visited[next.y][next.x] = visited[now.y][now.x] + 1;
					q.push({ next.y, next.x, 1 });
					total++;
				}
			}
			if (now.dir != 1 && now.y + 1 < N && (tunnel < 3 || tunnel == 5 || tunnel == 6)) {
				Node next = now;
				next.y += 1;
				int nextTunnel = mat[next.y][next.x];
				if (nextTunnel != 0 
					&& !visited[next.y][next.x]
					&& !(nextTunnel == 3 || nextTunnel == 5 || nextTunnel == 6)) {
					visited[next.y][next.x] = visited[now.y][now.x] + 1;
					q.push({ next.y, next.x, 2 });
					total++;
				}
			}
			if (now.dir != 4 && now.x - 1 >= 0 && (tunnel == 1 || tunnel == 3 || tunnel == 6 || tunnel == 7)) {
				Node next = now;
				next.x -= 1;
				int nextTunnel = mat[next.y][next.x];
				if (nextTunnel != 0 && !visited[next.y][next.x]
					&& !(nextTunnel == 2 || nextTunnel == 6 || nextTunnel == 7)) {
					visited[next.y][next.x] = visited[now.y][now.x] + 1;
					q.push({ next.y, next.x, 3 });
					total++;
				}
			}
			if (now.dir != 3 && now.x + 1 < M && (tunnel == 1 || tunnel == 3 || tunnel == 4 || tunnel == 5)) {
				Node next = now;
				next.x += 1;
				int nextTunnel = mat[next.y][next.x];
				if (nextTunnel != 0 && !visited[next.y][next.x]
					&& !(nextTunnel == 2 || nextTunnel == 4 || nextTunnel == 5)) {
					visited[next.y][next.x] = visited[now.y][now.x] + 1;
					q.push({ next.y, next.x, 4 });
					total++;
				}
			}
		}
	}
	return total;
}

int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		reset();
		input();
		cout << "#" << tc << " " << floodfill() << "\n";
	}
	return 0;
}
