#include <iostream>
#include <cstring>
using namespace std;

int  N,M,cnt, ans,ty,tx;
int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };
string MAP[10];
struct coord { int y, x; };

coord RED, BLUE;

// 입력 함수
void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> MAP[i];
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] == 'R') {
				RED.y = i;
				RED.x = j;
			}
			if (MAP[i][j] == 'B') {
				BLUE.y = i;
				BLUE.x = j;
			}
			if (MAP[i][j] == 'O') {
				ty = i;
				tx = j;
			}
		}
	}
}


// 구슬 회전 함수
void rotate(int direction) {
	int nry = RED.y;
	int nrx = RED.x;
	int nby = BLUE.y;
	int nbx = BLUE.x;

	while (1) {
		// 구슬 direction 방향으로 이동시켰다
		// 빨간 구슬과 파란 구슬 모두 이동 가능하다면
		nry = RED.y+ ydir[direction];
		nrx = RED.x +xdir[direction];
		nby = BLUE.y +ydir[direction];
		nbx = BLUE.x +xdir[direction];

		// 빨간 구슬만 이동 가능하다면
		if ((MAP[nby][nbx] == '#' || MAP[nby][nbx] == 'R') && (MAP[nry][nrx] == '.' || MAP[nry][nrx] == 'O'))
		{
			RED.y = nry;
			RED.x = nrx;
		}
		// 파란 구슬만 이동 가능하다면
		if ((MAP[nry][nrx] == '#' || MAP[nry][nrx] == 'B') && (MAP[nby][nbx] == '.' || MAP[nby][nbx] == 'O'))
		{
			BLUE.y = nry;
			BLUE.x = nbx;
		}

		// 둘 다 이동할 수 없다면
		if (MAP[nry][nrx] == '#' && MAP[nby][nbx] == '#')break;
	};

	// 구슬의 최종 좌표 완성
	RED.y = nry;
	RED.x = nrx;
	BLUE.y = nby;
	BLUE.x = nbx;
}

// 맵 변경 함수
void changeMAP(int nowry,int nowrx,int nowby,int nowbx) {
	MAP[nowry][nowrx] = '.';
	MAP[nowby][nowbx] = '.';
	MAP[RED.y][RED.x] = 'R';
	MAP[BLUE.y][BLUE.x] = 'B';
}

// dfs
void dfs(int d) {
	// 들어왔을때 기저조건 1 확인
	// 기저조건 1
	if (cnt >= 10) return;

	// 회전하기 전 좌표 저장
	int nowry = RED.y;
	int nowrx = RED.x;
	int nowby = BLUE.y;
	int nowbx = BLUE.x;

	cnt++;
	rotate(d);
	// 돌린 후 기저조건 2 확인
	// 기저조건 2
	if (MAP[RED.y][RED.x] == 'O' && MAP[BLUE.y][BLUE.x] == 'O' || MAP[RED.y][RED.x] != 'O' && MAP[BLUE.y][BLUE.x] == 'O') {
		ans = -1;
		return;
	}
	else if (MAP[RED.y][RED.x] == 'O') {
		ans = cnt;
		return;
	}
	

	// d 방향으로 돌렸는데 더 돌릴 수 있다면 또다시 방향을 확인해본다
	// 맵 저장하고
	string backup[10];
	memcpy(backup, MAP, N * sizeof(string));
	// 맵 변경
	changeMAP(nowry, nowrx, nowby, nowbx);

	for (int i = 0; i < 4; i++) {
		int ny = RED.y + ydir[i];
		int nx = RED.x + xdir[i];
		if (MAP[ny][nx] == '#')continue;
		if (MAP[ny][nx] == 'O') {
			ans = cnt + 1;
			return;
		}
		dfs(d);
		// 맵 복구
		memcpy(MAP, backup, N * sizeof(string));
		// 구슬 좌표 복구
		RED.y = nowry;
		RED.x = nowrx;
		BLUE.y = nowby;
		BLUE.x = nowbx;
	}
}


int main() {
	input();
	string backup[10];
	memcpy(backup, MAP, N * sizeof(string));
	// 빨간공 기준 이동 가능 방향 확인하기
	for (int i = 0; i < 4; i++) {
		int y = RED.y + ydir[i];
		int x = RED.x + xdir[i];
		if (MAP[y][x] != '.')continue;
		cnt = 0;
		dfs(i);
		// dfs 끝나면 맵 복구
		memcpy(MAP, backup, N * sizeof(string));
	}

}
