#include <iostream>
#include <queue>
using namespace std;

int N, M;
int MAP[51][51];
int visited[51][51];
queue<int>ds;
queue<int>ss;
struct Cloud {
	int y;
	int x;
};
Cloud clouds[4];
int diry[8] = {0,-1,-1,-1,0,1,1,1};
int dirx[8] = {-1,-1,0,1,1,1,0,-1};
/*
비바라기 시전 ->  (N, 1), (N, 2), (N-1, 1), (N-1, 2)에 비구름 생성
N x n 격자 - 바구니(한칸) : 물 저장
(r,c) : r행 c열 바구니 / A[r][c] : (r,c) 바구니에 저장된 물 양
M번 명령 ←, ↖, ↑, ↗, →, ↘, ↓, ↙
1. 모든 구름이 di 방향으로 si칸 이동한다.
2. 각 구름에서 비가 내려 구름이 있는 칸의 바구니에 저장된 물의 양이 1 증가한다.
3. 구름이 모두 사라진다.
4. 2에서 물이 증가한 칸 (r, c)에 물복사버그 마법을 시전. 
   대각선 방향으로 거리가 1인 칸에 물이 있는 바구니의 수만큼 (r, c)에 있는 물 양 증가
     - 이동과 다르게 경계를 넘어가는 칸은 대각선 방향으로 거리가 1인 칸이 아니다.
       (N, 2)에서 인접한 대각선 칸은 (N-1, 1), (N-1, 3)이고, (N, N)에서 인접한 대각선 칸은 (N-1, N-1)뿐이다.
5. 바구니에 저장된 물의 양이 2 이상인 모든 칸에 구름이 생기고, 물의 양이 2 줄어든다. 이때 구름이 생기는 칸은 3에서 구름이 사라진 칸이 아니어야 한다.
=> M번의 이동이 모두 끝난 후 바구니에 들어있는 물의 양의 합
*/

void test() {
	cout << "=====구름======" << endl;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << visited[i][j] << ' ';
		}cout << endl;
	}
}
void moveCloud(int d, int s) {
	//test();
	for (int i = 0; i < 4; i++) {
		Cloud nc = clouds[i];
		visited[clouds[i].y][clouds[i].x] = 0;
		//cout << "원래" << clouds[i].y << " 이동" << diry[d - 1] * s << endl;
		//cout << "원래" << clouds[i].y << " 이동" << diry[d - 1] * s << endl;
		clouds[i].y += diry[d - 1]*s;
		clouds[i].y += dirx[d - 1]*s;

		if (clouds[i].y < 0)
			clouds[i].y += N;
		if (clouds[i].x < 0)
			clouds[i].x += N;
		if (clouds[i].y >= N)
			clouds[i].y %= N;
		if (clouds[i].x >= N)
			clouds[i].x %= N;
		//cout << "최종 y: " << clouds[i].y << " x: "<<clouds[i].x << endl;
		visited[clouds[i].y][clouds[i].x] = 1;
	}
	test();
}

int dy[4] = { -1,-1,1,1 };
int dx[4] = { -1,1,-1,1 };
int diagnolChk(int y, int x) {
	int cnt = 0;

	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
	}

	return cnt;
}

int main() {
	
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}
	int d, s;
	clouds[0] = { N-1, 0 };
	clouds[1] = { N-1, 1 };
	clouds[2] = { N - 2, 0 };
	clouds[3] = { N - 2, 1 };
	for (int i = 0; i < M; i++) {
		cin >> d >> s;

		memset(visited, 0, sizeof(visited));

		//1. 구름 이동
		moveCloud(d, s);

		//2. 비 내리기
		int waterBlock = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if(visited[i][j] == 1)
					MAP[i][j]++;
			}
		}
		
		//4. 물 증가한 칸에 물복사버그 수행(대각선 방향으로 거리 1칸에 물바구니수만큼 물 양 증가)
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (visited[i][j] == 1) {
					int waterCnt = diagnolChk(i,j);
				}
			}
		}
		int de = 1;

	}


	return 0;
}
