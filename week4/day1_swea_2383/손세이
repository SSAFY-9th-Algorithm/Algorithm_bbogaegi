#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

// 초기화 안해서 답 안나옴 하하
// 처음에 dfs인건 알았는데 그걸 어떻게 구현할지 고민 많이함
// dfs가 문제가 아니야!!!!
// 계산이 더 문제였어!!!
// 인간들아 그냥 가까운 계단 쓰자
// 이번엔 주석 많이 달면서 해서 이해는 잘 될거에요

struct Stair {
	int y;
	int x;
	int h;	// 높이
};

struct Node {
	int y;
	int x;
};

int N;
int MAP[15][15]; 
Stair stair[2];	// 계단 정보
vector<Node> p;	// 인간 정보
vector<int> wait[2]; // 계단 두개를 이용할 대기 인원들
int ans;

void INIT() {
	memset(MAP, 0, sizeof(MAP));
	memset(stair, 0, sizeof(stair));
	wait[0].clear();
	wait[1].clear();
	ans = 21e8;
	p.clear();
}

void input() {
	cin >> N;
	int idx = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];

			if (MAP[i][j] == 1) {
				p.push_back({ i,j });
			}
			else if (MAP[i][j] > 1)
				stair[idx++] = { i,j,MAP[i][j] };
		}
	}
}

// 거리 구하는 함수
int getDist(int y1, int x1, int y2, int x2) {
	return abs(y1 - y2) + abs(x1 - x2);
}

int downStair(vector<int>& s, int h) {	// s : 계단을 이용할 예정인 사람들과 계단 사이의 거리가 저장된 vector, h: 높이
	// 모두가 계단을 내려가는데 걸리는 시간
	int duration = 0;
	queue<int>q;	// 계단을 내려갈 사람들을 담아서 처리

	int idx = 0;
	while (idx < s.size()) // 이용 예정 인원만큼 보면 종료
	{
		// 계단 까지 오는시간 + 계단을 내려가는 시간이 현재 총 걸린보다 같거나 작으면 이미 내려갔다!
		while (!q.empty() && q.front() + h <= duration)
			q.pop();
		// 대기 인원이 3명보다 적으면 오는 시간 대기열 추가
		while (idx < s.size() && q.size() < 3 && s[idx] <= duration){
			q.push(duration); 
			idx++;
		}
		// 걸리는 시간 추가
		duration++;
	}
	// 대기열에 아직도 사람이 있으면 처리해주자!
	while (!q.empty()) {
		// 계단 까지 오는시간 + 계단을 내려가는 시간이 현재 총 걸린보다 같거나 작으면 이미 내려갔다!
		while (!q.empty() && q.front() + h <= duration)
			q.pop();
		// 아직도 못갔으면 걸리는 시간 추가!
		duration++;
	}
	return duration;
}

int getTime() {
	vector<int> StoPDist[2];
	int res = 0;
	for (int i = 0; i < 2; i++) {
		int sy = stair[i].y, sx = stair[i].x;
		// 계단 번호별 대기열에 걸려있는 사람들과 계단의 거리를 구해봅시다
		for (int j : wait[i]) {
			int py = p[j].y, px = p[j].x;
			int dist = getDist(sy, sx, py, px);
			StoPDist[i].push_back(dist);
		}
		// 거리가 짧은 순서부터 오름차순 정렬
		sort(StoPDist[i].begin(), StoPDist[i].end());
		// 이제 계단을 내려가 봅시다
		int tmp = downStair(StoPDist[i], stair[i].h);
		// 계단 두개 중 오래걸린 시간 저장
		res = max(res, tmp);
	}
	return res;
}

void dfs(int now) {
	if (now == p.size()) {
		int tmp = getTime();
		ans = min(ans, tmp);
		return;
	}

	// 1번 계단 이용
	wait[0].push_back(now);
	dfs(now + 1);
	wait[0].pop_back();

	// 2번 계단 이용
	wait[1].push_back(now);
	dfs(now + 1);
	wait[1].pop_back();
}

int main() {
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		INIT();
		// input
		input();
		// solve
		dfs(0);
		// output
		cout << '#' << tc << ' ' << ans << '\n';
	}
	return 0;
}
