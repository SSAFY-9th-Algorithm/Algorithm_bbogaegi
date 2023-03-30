#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

// 0 위 1 아래 2 왼쪽 3 오른쪽
int ydir[] = { -1, 1, 0, 0 };
int xdir[] = { 0, 0, -1, 1 };

struct Shark {
	int y, x, dir;
	int priority[4][4];
};

int MAP[21][21][3]; // 0: 상어 번호, 1: 그 칸에 있는 냄새의 상어 번호, 2: 냄새 시간
int N, M, K;
Shark shark[401];
int res = -1;

void input() {
	cin >> N >> M >> K;
	for(int i=0;i<N;i++){
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j][0];
			int n = MAP[i][j][0];
			if (MAP[i][j][0]) {
				shark[n].y = i;
				shark[n].x = j;
				MAP[i][j][1] = n;
				MAP[i][j][2] = K;
			}
		}
	}

	for (int i = 1; i <= M; i++) {
		cin >> shark[i].dir;
		shark[i].dir--;
	}
	// 각 상어의 방향별 우선순위
	for (int i = 1; i <= M; i++) 
		for (int j = 0; j < 4; j++) {
			cin >> shark[i].priority[j][0] >> shark[i].priority[j][1] >> shark[i].priority[j][2] >> shark[i].priority[j][3];
			shark[i].priority[j][0]--;
			shark[i].priority[j][1]--;
			shark[i].priority[j][2]--;
			shark[i].priority[j][3]--;
		}
}

void solve() {
	int time = 0;
	int dead_shark = 0;

	while (time <= 1000)
	{
		// 시간이 1초 지났다!
		time++;
		int de = 1;
		// 칸에 남아있는 냄새의 시간을 줄여주자
		int COPY[21][21][3] = { 0, };
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				// 상어 번호
				COPY[i][j][0] = MAP[i][j][0];
				// 냄새 시간
				COPY[i][j][2] = MAP[i][j][2];

				if (COPY[i][j][2] > 0) 
					COPY[i][j][2]--;
				// 시간이 지나도 냄새가 남아있다면
				// 냄새 상어 번호 기록
				if(COPY[i][j][2] > 0)
					COPY[i][j][1] = MAP[i][j][1];

			}
		}
		// 상어 이동
		for (int i = 1; i <= M; i++) {
			Shark now = shark[i];
			// 죽은 상어면 continue
			if (now.y == -1)
				continue;
			int flag = 0;
			// 4방향을 확인하며 빈칸 찾기
			for (int d = 0; d < 4; d++) {
				int ndir = now.priority[now.dir][d];
				int ny = now.y + ydir[ndir];
				int nx = now.x + xdir[ndir];
				// 범위를 벗어나면 continue
				if (ny < 0 || nx < 0 || ny >= N || nx >= N)
					continue;
				// 가려는 곳에 냄새가 있으면 continue
				if (MAP[ny][nx][2])
					continue;

				// 원래 있던 곳은 초기화
				COPY[now.y][now.x][0] = 0;
				flag = 1;
				// 상어가 없다면
				if (!COPY[ny][nx][0]) {
					// 이동할 곳에 정보를 넣어주고
					COPY[ny][nx][0] = i;
					COPY[ny][nx][1] = i;
					COPY[ny][nx][2] = K;
					// 상어 정보 업데이트
					shark[i].y = ny;
					shark[i].x = nx;
					shark[i].dir = ndir;
				}
				// 작은 숫자의 상어부터 보고 있기 때문에
				// 가려는 위치에 상어가 있다면
				// 그 상어는 죽는다!
				else {
					// 이 상어는 죽었다!
					dead_shark++;
					shark[i].y = -1;
				}
				break;
			}
			// 만약 인접한 4방향에 빈 칸이 없었다면
			// 내 냄새가 있는 곳으로 가야한다
			if (!flag) {
				for (int d = 0; d < 4; d++) {
					int ndir = now.priority[now.dir][d];
					int ny = now.y + ydir[ndir];
					int nx = now.x + xdir[ndir];
					// 범위를 벗어나면 continue
					if (ny < 0 || nx < 0 || ny >= N || nx >= N)
						continue;
					// 가려는 곳이 내 냄새가 아니면 continue
					if (MAP[ny][nx][2] && MAP[ny][nx][1] != i)
						continue;

					// 원래 있던 곳은 초기화
					COPY[now.y][now.x][0] = 0;
					// 상어가 없다면
					if (!COPY[ny][nx][0]) {
						// 이동할 곳에 정보를 넣어주고
						COPY[ny][nx][0] = i;
						COPY[ny][nx][1] = i;
						COPY[ny][nx][2] = K;
						// 상어 정보 업데이트
						shark[i].y = ny;
						shark[i].x = nx;
						shark[i].dir = ndir;
					}
					// 작은 숫자의 상어부터 보고 있기 때문에
					// 가려는 위치에 상어가 있다면
					// 그 상어는 죽는다!
					else {
						// 이 상어는 죽었다!
						dead_shark++;
						shark[i].y = -1;
					}
					break;
				}
			}
		}
		// 1번 상어만 남으면 종료!
		if (dead_shark == M - 1)
			break;
		for(int i=0;i<N;i++)
			for (int j = 0; j < N; j++) {
				MAP[i][j][0] = COPY[i][j][0];
				MAP[i][j][1] = COPY[i][j][1];
				MAP[i][j][2] = COPY[i][j][2];
			}
	}
	if (time <= 1000)
		res = time;
}

int main() {
	fastIO;
	
	input();
	solve();

	cout << res << '\n';

	return 0;
}
