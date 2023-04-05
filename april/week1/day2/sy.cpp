#define	_CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;
using ll = long long;

struct Node {
	int y, x;
};

int N, M, K, C; // 맵크기, 진행 기간, 확산 범위, 지속되는 기간
int MAP[21][21][3]; // 0: 나무, 벽, 1: 제초제, 2: 나무 주변 빈공간 

queue<Node> trees;
ll kill = 0;

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

int ydir_k[] = { -1,-1,1,1 };
int xdir_k[] = { -1,1,1,-1 };

// 나무 성장
void grow() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j][0] < 1)
				continue;
			// 해당 위치부터 4방향 탐색
			// 근처에 있는 나무의 개수를 찾고
			int cnt = 0;
			int emp = 0;
			for (int d = 0; d < 4; d++) {
				int ny = i + ydir[d];
				int nx = j + xdir[d];

				if (ny < 0 || nx < 0 || ny >= N || nx >= N)
					continue;

				if (MAP[ny][nx][0] > 0)
					cnt++;
				if (MAP[ny][nx][0] == 0 && MAP[ny][nx][1] == 0)
					emp++;

			}
			MAP[i][j][0] += cnt;
			MAP[i][j][2] = emp;
		}
	}
}
// 나무 번식
void spread() {
	// #2. 기존에 있었던 나무들은 
	// 인접한 4개의 칸 중 벽, 다른 나무, 제초제 모두 없는 칸에 번식
	//  칸의 나무 그루 수에서 총 번식이 가능한 칸의 개수만큼 나누어진 그루 수만큼 번식
	int COPY[21][21] = {0,};
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j][0] < 1 || MAP[i][j][2] == 0)
				continue; 
			int tmp = MAP[i][j][0] / MAP[i][j][2];
			// 4방향 번식
			for (int d = 0; d < 4; d++) {
				int ny = i + ydir[d];
				int nx = j + xdir[d];

				if (ny < 0 || nx < 0 || ny >= N || nx >= N)
					continue;
				// 빈 공간이면 번식한다!
				if (MAP[ny][nx][0] == 0 && MAP[ny][nx][1] == 0) {
					COPY[ny][nx] += tmp;
				}
			}
			
		}
	}
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < N; j++) 
			MAP[i][j][0] += COPY[i][j];
}

ll getSum(int y, int x) {
	ll sum = MAP[y][x][0];

	for (int i = 0; i < 4; i++) {
		for (int k = 1; k <= K; k++) {
			int ny = y + ydir_k[i]*k;
			int nx = x + xdir_k[i]*k;

			if (ny < 0 || nx < 0 || ny >= N || nx >= N)
				break;
			if (MAP[ny][nx][0] < 1)
				break;

			sum += MAP[ny][nx][0];
		}
	}

	return sum;
}
// 제초제를 뿌릴 위치 선정
Node getPos() {
	ll MAX = -1;
	int mxy = 0, mxx = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j][0] < 1)
				continue;
			// 나무가 있다면
			ll tmp = getSum(i, j);
			if (tmp > MAX) {
				MAX = tmp;
				mxy = i;
				mxx = j;
			}
		}
	}
	if(MAX != -1)
		kill += MAX;
	return { mxy, mxx };
}

// 제초제를 뿌리자
void killTree() {
	Node pos = getPos();
	// 이 나무는 죽었다!
	MAP[pos.y][pos.x][0] = 0;
	MAP[pos.y][pos.x][1] = C + 1;
	// 4방향을 K범위만큼 죽이자!
	for (int i = 0; i < 4; i++) {
		for (int k = 1; k <= K; k++) {
			int ny = pos.y + ydir_k[i]*k;
			int nx = pos.x + xdir_k[i]*k;
			// 범위를 벗어나면 break
			if (ny < 0 || nx < 0 || ny >= N || nx >= N)
				break;
			// 빈칸, 벽이면 break
			if (MAP[ny][nx][0] < 0) 
				break;
			if (MAP[ny][nx][0] == 0) {
				MAP[ny][nx][1] = C + 1;
				break;
			}
			// 얘도 죽었다!
			MAP[ny][nx][0] = 0;
			MAP[ny][nx][1] = C + 1;
		}
	}
}

void countDown() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j][1] > 0)
				MAP[i][j][1]--;
		}
	}
}

int check() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (MAP[i][j][0] > 0)
				return 0;
	return 1;
}

void simul() {
	while (M--)
	{
		int de = 1;
		// 제초제 시간 줄이기
		countDown();

		// 나무 성장
		grow();

		// 나무 번식
		spread();
	
		// 제초제 살포
		killTree();

		if (check())
			break;
	}
	printf("%lld\n", kill);
}

int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%d %d %d %d", &N, &M, &K, &C);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			scanf("%d", &MAP[i][j][0]);
			if (MAP[i][j][0] > 0)
				trees.push({ i, j });
		}

	simul();
	return 0;
}
