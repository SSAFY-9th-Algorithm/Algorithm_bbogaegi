#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/* 꼬리잡기놀이
n*n 격자
3명 이상 한 팀.
모든 사람들은 자신의 앞 사람 허리 잡고 움직임.
맨 앞 사람은 머리사람, 맨 뒷 사람은 꼬리사람.
각 팀은 주어진 이동 선 따라서 이동. 각 팀의 이동 선 끝은 이어져있으나 겹치지 않음.
1. 머리사람 따라서 한 칸 이동
2. 공이 던져짐(n개의 행, n개의 열)
   좌->우 / 하->상 / 우->좌 / 상->하
   4n라운드 넘어가면 1번째 라운드 방향으로 돌아감
3. 공이 던져지는데 해당 선에 사람이 있으면 최초 만난 사람이 공 & 점수 획득.
점수는 머리사람 시작으로 팀 내에서 k번째 사람이면 k의 제곱수만큼 획득. eks,아무도 받지 못하면 점수 X.
공 획득 팀은 머리사람과 꼬리사람 변경 => 방향 변경
*/

int n, m, k;
int scores[6];
int MAP[21][21];
int road[21][21];
struct Person {
	int y;
	int x;
	int id;
	int dir;
};
struct Block {
	int y;
	int x;
	int id;
};
vector<Person> people[6]; //각 팀에 해당하는 사람들의 모음

//동(위아래), 북(왼오), 서(아래위), 남(오왼)
int diry[4] = { 0, -1, 0, 1 };
int dirx[4] = { 1, 0, -1, 0 };

void ConnectRoad(int y, int x) {
	
	queue<Block>blocks;
	blocks.push({ y, x, MAP[y][x]});

	while (!blocks.empty()) {
		Block nowblock = blocks.front();
		blocks.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + diry[i];
			int nx = x + dirx[i];

			if (ny < 0 || nx < 0 || ny >= n || nx >= n)
				continue;

			if (MAP[ny][nx] == 4) {
				road[ny][nx] = 4;
			}
			else if (MAP[ny][nx] != 0) {
				road[ny][nx] = 4;
			}
			blocks.push({ ny, nx, MAP[ny][nx] });
		}
	}

	

}

void FindRoad() {

	//맵에서 숫자인 거를 찾으면 연결된 부분 다 연결하기
	//각 팀의 길 맵 만들기
	//road[][]이용
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (MAP[i][j] != 0) {
				ConnectRoad(i, j);
			}
		}
	}

	//각 팀에 해당하는 사람들 모으기
	//people[i] 이용
}

void Move() {
	// 머리사람 따라서 한 칸 이동하기
}

void ThrowBall() {
	//공 던지기위한 라운드의 방향 찾기

	//방향대로 공을 던져서 가장 먼저 부딫히는 사람이 있는지 확인
	for (int i = 0; i < n; i++) {
		int ndy;
		int ndx;
		//정해진 방향대로 한 칸씩 이동하는데 만약 어떤 사람이 발견되면 해당 사람이 공을 획득하도록 해야지
	}
	//부딫히는 사람 있으면 해당 조 점수 획득 후 방향 전환(머리<->꼬리)

	//부딫히는 사람 없으면 아무 점수 없음
}

int Solution() {

	int ans = 0;

	for (int i = 0; i < m; i++) {
		ans += scores[i];
	}

	return ans;
}

int main() {

	cin >> n >> m >> k;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> MAP[i][j];
		}
	}

	FindRoad();

	Move();

	ThrowBall();

	for (int r = 1; r <= k; r++) {

		int ans = Solution();
		cout << ans;
	}


}
