#include <iostream>
#include <cstring>
using namespace std;

int  N, M, cnt, ans = 21e8, ty, tx, sry, srx, sby, sbx, recent[] = { 1,0,3,2 };
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
				sry = i;
				RED.x = j;
				srx = j;
			}
			if (MAP[i][j] == 'B') {
				BLUE.y = i;
				BLUE.x = j;
				sby = i;
				sbx = j;
			}
			if (MAP[i][j] == 'O') {
				ty = i;
				tx = j;
			}
		}
	}
}

void pMAP() {
	for (int i = 0; i < N; i++) {
		cout << MAP[i] << '\n';
	}cout << '\n';
};

// 구슬 회전 함수
void rotate(int direction) {
	int nry = RED.y;
	int nrx = RED.x;
	int nby = BLUE.y;
	int nbx = BLUE.x;
	cout << direction << "방향 회전" << cnt << "\n";
	while (1) {
		// 구슬 direction 방향으로 이동시켰다
		// 빨간 구슬과 파란 구슬 모두 이동 가능하다면
		nry = RED.y + ydir[direction];
		nrx = RED.x + xdir[direction];
		nby = BLUE.y + ydir[direction];
		nbx = BLUE.x + xdir[direction];

		// 빨간 구슬만 이동 가능하다면
		if ((MAP[nby][nbx] == '#' || MAP[nby][nbx] == 'R') && (MAP[nry][nrx] == '.' || MAP[nry][nrx] == 'O'))
		{
			RED.y = nry;
			RED.x = nrx;
			nby = BLUE.y;
			nbx = BLUE.x;
		}
		// 파란 구슬만 이동 가능하다면
		if ((MAP[nry][nrx] == '#' || MAP[nry][nrx] == 'B') && (MAP[nby][nbx] == '.' || MAP[nby][nbx] == 'O'))
		{
			nry = RED.y;
			nrx = RED.x;
			BLUE.y = nby;
			BLUE.x = nbx;
		}

		// 둘 다 이동할 수 없다면
		if ((MAP[nry][nrx] == '#' && MAP[nby][nbx] == '#') || (MAP[nry][nrx] == 'B' && MAP[nby][nbx] == '#') || (MAP[nry][nrx] == '#' && MAP[nby][nbx] == 'R'))
		{
			nby = BLUE.y;
			nbx = BLUE.x;
			nry = RED.y;
			nrx = RED.x;
			break;
		};

		// 구슬의 최종 좌표 완성
		RED.y = nry;
		RED.x = nrx;
		BLUE.y = nby;
		BLUE.x = nbx;
	}
}

// 맵 변경 함수
void changeMAP(int nowry, int nowrx, int nowby, int nowbx) {
	MAP[nowry][nowrx] = '.';
	MAP[nowby][nowbx] = '.';
	MAP[RED.y][RED.x] = 'R';
	MAP[BLUE.y][BLUE.x] = 'B';
}

// dfs
void dfs(int d, int level) {
	cout << "level: " << level << '\n';
	// 들어왔을때 기저조건 1 확인
	// 기저조건 1
	if (cnt >= 10) return;

	// 회전 후 이동한 좌표가 가능하다면 맵 갱신하기 위해서
	// 회전하기 전 좌표 저장
	int nowry = RED.y;
	int nowrx = RED.x;
	int nowby = BLUE.y;
	int nowbx = BLUE.x;

	// 회전
	cnt++;
	rotate(d);

	// 기저조건 2 확인
	if (MAP[RED.y][RED.x] == 'O' && MAP[BLUE.y][BLUE.x] == 'O' || MAP[RED.y][RED.x] != 'O' && MAP[BLUE.y][BLUE.x] == 'O') return;
	else if (MAP[RED.y][RED.x] == 'O') {
		if (ans > cnt)
			ans = cnt;
		return;
	}


	// 맵 변경 전 저장( 현재 level의 기본 MAP )
	string backup2[10];
	for (int i = 0; i < N; i++) backup2[i] = MAP[i];
	// 맵 변경 ( 현재 level의 rotated MAP )
	changeMAP(nowry, nowrx, nowby, nowbx);
	pMAP();

	for (int i = 0; i < 4; i++) {

		if (i == recent[d]||i==d)continue;
		int ny = RED.y + ydir[i];
		int nx = RED.x + xdir[i];
		if (MAP[ny][nx] == '#')continue;
		if (MAP[ny][nx] == 'O') {
			ans = cnt + 1;
			return;
		}
		dfs(i, level + 1);

		// 맵 복구
		cout << "level : " << level << '\n';
		cout << "복구\n";
		for (int i = 0; i < N; i++) MAP[i]= backup2[i];
		pMAP();
		// 구슬 좌표 복구
		RED.y = nowry;
		RED.x = nowrx;
		BLUE.y = nowby;
		BLUE.x = nowbx;
	}
	return;
}

int main() {
	input();
	string backup[10];
	for (int i = 0; i < N; i++) backup[i] = MAP[i];

	// 빨간공 기준 이동 가능 방향 확인하기
	for (int i = 0; i < 4; i++) {
		int ry = RED.y + ydir[i];
		int rx = RED.x + xdir[i];

		
		cnt = 0;
		if (MAP[ry][rx] == 'O') {
			ans = 1;
			break;
		}
		if (MAP[ry][rx] != '.')continue;
		dfs(i, 0);
		// dfs 끝나면 맵 복구
		for (int i = 0; i < N; i++)	MAP[i] = backup[i];
	
		// 구슬도 복구
		RED.y = sry;
		RED.x = srx;
		BLUE.y = sby;
		BLUE.x = sbx;
	}
	cout << ans;

}
