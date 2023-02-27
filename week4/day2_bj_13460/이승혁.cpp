############# 설계 간지 ##############

R좌표 -> dfs(sy,sx)
sy, sx 기준, 4방향 탐색 ->( 1.벽이다 2. 구멍이다. 3.파란공이다. 아니면 갈 수 있다)

갈수있는 방향을 rotate 함수 전달
(rotate 전 MAP 저장)
전달받은 방향으로 AfterRotate.y, AfterRotate.x 생성

A.y, A.x O인지 확인 -> 아니라면 dfs(A.y, A.x)

#######################################
=> 파란색도 움직이나?
=> 상으로 갔으면 그 다음에는 하로 올 수 없게? -> dfs(x,y,상) -> dfs(x,y,하) -> dfs(x,y,상) .....                             ######
  => 갔다가 막히면 돌아오는 방법.. Rotate 했는데 자기 자신이라면 return,(우 뱡향으로 왔는데, 내오른쪽/위/아래 벽이면 return) ->     R #
                                                                                                                          ######
while 을 사용해서 돌리는게 나은가? => 갈 수 있는 곳을 찾아도 갔다가 돌아와야하지 않을까 안돌아와도 된다는 보장은?


#include <iostream>
using namespace std;

struct coord {
	int y, x;
};
string MAP[10];
int N, M, ty, tx, sy, sx, ans = 0, cnt = 0, recent = 4, check[] = { 1,0,3,2,-1 };

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> MAP[i];
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] == 'R') {
				sy = i;
				sx = j;
			}
			if (MAP[i][j] == '0') {
				ty = i;
				tx = j;
			}
		}
	}
};

coord rotate(int y,int x,int d) {
	// 위로 기울이기
	if (d == 0) {
		// 현재 y좌표로부터 가장 위쪽('#'또는 'O'를 만날대까지 증가시킨다)
		for (int i = y-1; i > 0; i--) {
			if (MAP[i][x] == 'O') {
				ans = cnt;
				y = i;
				break;
			}
			if (MAP[i][x] == '#'||MAP[i][x]=='B') {
				y = i + 1;
				break;
			}
			y = i;
		}

	}
	// 아래로 기울이기
	else if (d == 1) {
		for (int i = y +1; i < N; i++) {
			if (MAP[i][x] == 'O') {
				ans = cnt;
				y = i;
				break;
			}
			if (MAP[i][x] == '#'|| MAP[i][x] == 'B'){
				y = i - 1;
				break;
			}
			y = i;
		}
	}
	// 왼쪽으로 기울이기
	else if (d == 2) {
		for (int i = x-1; i >0; i--) {
			if (MAP[y][i] == 'O') {
				ans = cnt;
				x = i;
				break;
			}
			if (MAP[y][i] == '#'|| MAP[y][i] == 'B') {
				x = i + 1;
				break;
			}
			x = i;
		}

	}
	// 오른쪽으로 기울이기
	else if (d == 3) {
		for (int i = x +1; i < M; i++) {
			if (MAP[y][i] == 'O') {
				ans = cnt;
				x = i;
				break;
			}
			if (MAP[y][i] == '#'|| MAP[y][i] == 'B') {
				x = i -1;
				break;
			}
			x = i;
		}

	}
	return { y, x };
}

void func(int y,int x) {

	if (cnt >= 10) {
		if (ans == 0) 
			ans = -1;
		return;
	}

	for (int i = 0; i < 4; i++) {
		int ny = y + ydir[i];
		int nx = x + xdir[i];

		if (ny < 0 || nx < 0 || ny >= N || nx >= M)continue;
		if (i == check[recent])continue;
		if (MAP[ny][nx] == '#')continue;
		if (MAP[ny][nx] == 'O') {
			ans = cnt + 1;
			return;
		}

		string backup[10];

		memcpy(backup, MAP, N  * sizeof(string));

		MAP[y][x] = '.';
		cnt++;
		recent = i;

		coord afterRotate=rotate(y,x, i);
		cout << i << "방향 회전해서 " << afterRotate.y << "," << afterRotate.x << "좌표로 이동\n";
		cout << "현재 회전 수 :" << cnt << '\n';

		if (MAP[afterRotate.y][afterRotate.x] == 'O') return;
		else if (afterRotate.y == y && afterRotate.x == x)return;
		else {
			MAP[afterRotate.y][afterRotate.x] = 'R';
			for (int i = 0; i < N; i++) {
				cout << MAP[i] << '\n';
			}cout << '\n';
			func(afterRotate.y, afterRotate.x);
			memcpy(backup, MAP, N * sizeof(string));
			recent = 0;
			cnt--;
		}
		
	}

}

int main() {
	// input()
	input();
	// solve()
	cout << '\n';
	func(sy, sx);
	// output()
	cout << ans;
	return 0;
}
