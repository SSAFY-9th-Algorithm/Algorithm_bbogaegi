#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <vector>
using namespace std;

// 주사위는 지도 위에 윗 면이 1이고, 동쪽을 바라보는 방향이 3인 상태로 놓여져 있으며, 놓여져 있는 곳의 좌표는 (x, y)
// 이동한 칸에 쓰여 있는 수가 0이면, 주사위의 바닥면에 쓰여 있는 수가 칸에 복사
// 0이 아닌 경우에는 칸에 쓰여 있는 수가 주사위의 바닥면으로 복사되며, 칸에 쓰여 있는 수는 0
// 가장 처음에 주사위에는 모든 면에 0

struct Dice {
	int y, x;
	int up, down, left, right, top, bottom;
};

// 동 서 북 남
int ydir[5] = { 0,0,0,-1,1 };
int xdir[5] = { 0,1,-1,0,0 };

int N, M;
int MAP[25][25];
Dice dice;

void changeDice(int d) {
	int ltmp = dice.left;
	int rtmp = dice.right;
	int btmp = dice.bottom;
	int ttmp = dice.top;
	int dtmp = dice.down;
	int utmp = dice.up;

	// 동
	if (d == 1) {
		dice.bottom = rtmp;
		dice.top = ltmp;
		dice.left = btmp;
		dice.right = ttmp;
	}
	// 서
	else if (d == 2) {
		dice.bottom = ltmp;
		dice.top = rtmp;
		dice.left = ttmp;
		dice.right = btmp;
	}
	// 북
	else if (d == 3) {
		dice.bottom = utmp;
		dice.top = dtmp;
		dice.up = ttmp;
		dice.down = btmp;
	}
	// 남
	else {
		dice.bottom = dtmp;
		dice.top = utmp;
		dice.up = btmp;
		dice.down = ttmp;
	}
}

int main() {
	fastIO;

	int K;
	cin >> N >> M >> dice.y >> dice.x >> K;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> MAP[i][j];
	
	for (int i = 0; i < K; i++) {
		int dir;
		cin >> dir;

		int y = dice.y;
		int x = dice.x;

		y += ydir[dir];
		x += xdir[dir];

		if (y < 0 || x < 0 || y >= N || x >= M)
			continue;

		dice.y = y;
		dice.x = x;
		changeDice(dir);

		if (!MAP[y][x])
			MAP[y][x] = dice.bottom;
		else {
			dice.bottom = MAP[y][x];
			MAP[y][x] = 0;
		}

		cout << dice.top << '\n';
	}
	
	return 0;
}
