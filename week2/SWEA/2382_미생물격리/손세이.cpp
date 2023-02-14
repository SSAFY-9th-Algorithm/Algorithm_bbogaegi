#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

// 알고리즘 보다는 구현의 문제 였음
// 풀면서 어려웠던 점
// #1. 처음에 움직이는 맵을 배열로 구현 -> 여러개 (3개 이상)가 한번에 만나는 경우 구현이 어려움
// #2. 맵에서 군집이 있는 위치 초기화를 안했더니 답이 틀림
// #3. M번 만큼 반복하는거 범위 제대로 안해서 자꾸 틀림 -> 그냥 while 문으로 바꿈

struct microbe {
	int y;
	int x;
	int amount;
	int dir;
};

vector<int>MAP[101][101];
int N, M, K;
int ydir[5] = { 0, -1, 1, 0, 0 }; //이동방향 : 상(1) 하(2) 좌(3) 우(4)
int xdir[5] = { 0, 0, 0, -1, 1 };
microbe arr[1001];

void move() {
	//이동 맵 초기화
	for (int i = 1; i <= K; i++) {
		if (arr[i].amount > 0) {
			MAP[arr[i].y][arr[i].x].clear();
		}
	}

	for (int i = 1; i <= K; i++) {
		microbe tmp = arr[i];

		// 소멸한 군집이면 진행 안합
		if (tmp.amount == 0)
			continue;

		// 방향으로 한칸 이동
		tmp.y += ydir[tmp.dir];
		tmp.x += xdir[tmp.dir];

		// #1. 약품이 처리된 곳에 가면 절반이 죽고 이동방향 반대로
		if (tmp.y <= 0 || tmp.x <= 0 || tmp.y >= N - 1 || tmp.x >= N - 1) {
			tmp.amount /= 2;
			if (tmp.dir % 2 == 0) tmp.dir--;
			else tmp.dir++;
		}

		if (tmp.amount > 0)
			MAP[tmp.y][tmp.x].push_back(i); // MAP에 미생물 번호 기록
		arr[i] = tmp;
	}

	for (int i = 1; i <= K; i++) {

		if (arr[i].amount == 0)
			continue;

		int y = arr[i].y;
		int x = arr[i].x;

		// #2. 두개 이상의 군집이 한셀에 만나면 큰 군집으로 합쳐지고 방향은 큰 군집을 따른다.
		if (MAP[y][x].size() > 1) {
			int sum = 0;
			int max_num = 0;
			int MAX = -21e8;
			for (int j = 0; j < MAP[y][x].size(); j++) {
				sum += arr[MAP[y][x][j]].amount;

				if (arr[MAP[y][x][j]].amount > MAX) {
					MAX = arr[MAP[y][x][j]].amount;
					max_num = MAP[y][x][j];
				}
				arr[MAP[y][x][j]].amount = 0;
			}
			arr[max_num].amount = sum;
		}
	}
}

int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		// reset
		int ans = 0;
		memset(arr, 0, sizeof(arr));
		// MAP 초기화
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				MAP[i][j].clear();

		// input
		cin >> N >> M >> K;
		for (int i = 1; i <= K; i++) {
			cin >> arr[i].y >> arr[i].x >> arr[i].amount >> arr[i].dir;
		}

		// solve
		while (M--)
		{
			move();
		}
		for (int i = 1; i <= K; i++) {
			if (arr[i].amount > 0) ans += arr[i].amount;
		}

		// output
		cout << "#" << tc << " " << ans << '\n';
	}
	return 0;
}
