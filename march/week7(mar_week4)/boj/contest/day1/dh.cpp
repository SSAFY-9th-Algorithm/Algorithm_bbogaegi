#include <iostream>
using namespace std;

// 맨 처음 시작하는 부분은 무조건 청소 -> 1부터 카운트 시작
// 경우 2가지
// 우선 현재 칸에서 주변 4칸 중에 청소가 되어 있지 않은 칸이 있는지 확인
// 왼쪽으로 회전 0 3 2 1 0 3 2 1...... -> d = (d + 3) % 4

int dir[4] = { 0, 1, 2, 3 };
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int N, M;
int r, c, d;
int MAP[50][50];
int visited[50][50];
int cnt;


int main() {
	cin >> N >> M;
	cin >> r >> c >> d;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> MAP[i][j];


	while (1) {
		if (visited[r][c] == 0) {
			visited[r][c] = 1; // 출발점은 무조건 청소
			cnt++;
		}
		int flag = 0;
		// 방향을 돌리면서 확인
		for (int i = 0; i < 4; i++) {
			d = (d + 3) % 4;
			int nx = r + dx[d];
			int ny = c + dy[d];
			if (MAP[nx][ny] == 0 && visited[nx][ny] == 0) {
				r += dx[d];
				c += dy[d];
				flag = 1;
				break;	// 돌리는 구간에서 나와서 위로가서 청소 여부 확인
			}
		}	// 4방향 확인했는데 모두 청소할 곳이 없다면? (flag = 0)

		// 후진한다 -> 후진할때 벽이라면 작동멈춘다
		if (flag == 0) {
			/*
			0 -> 2
			1 -> 3
			2 -> 0
			3 -> 1
			*/
			// -> d = (d+2)%4
			int backdir = (d + 2) % 4;
			if (MAP[r + dx[backdir]][c + dy[backdir]] == 1) break; // 벽이면 끝
			// 아니면 후진
			r += dx[backdir];
			c += dy[backdir];
		}
	}
	cout << cnt << endl;
}
