#define _CRT_SECURE_NO_WARNINGS
#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
using namespace std;

// 설계 
// dfs로 M개의 치킨집을 고르고
// 도시의 치킨 거리를 계산하여
// 가장 작은 값을 구한다
// dfs를 선택한 이유 -> M개를 고르는 모든 경우를 봐야하는 완전 탐색이라는 생각이 들어서

struct Node {
	int y, x;
};

int N, M;
int COPY[51][51];
int ans = 21e8;
vector<Node> chicken, home, chick;

void input() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int num;
			cin >> num;
			if (num == 1) {
				COPY[i][j] = num;
				home.push_back({ i, j });
			}
			if (num == 2)
				chicken.push_back({ i, j });
		}
	}
}

int calcDist(int y1, int x1, int y2, int x2) {
	return abs(y1 - y2) + abs(x1 - x2);
}

int getDist() {
	int mdist = 200;
	int sum = 0;

	int de = 1;
	int hsize = home.size();
	int csize = chick.size();

	for (int i = 0; i < hsize; i++) {
		mdist = 200;
		Node hnow = home[i];
		for (int j = 0; j < csize; j++) {
			Node cnow = chick[j];
			int tmp = calcDist(hnow.y, hnow.x, cnow.y, cnow.x);
			if (tmp < mdist)
				mdist = tmp;
		}
		sum += mdist;
	}
	return sum;
}

// M개를 골라보자
void dfs(int now, int cnt) {
	// 기저조건 -> M개를 고르면 종료
	if (cnt == M) {
		int sum = getDist();
		if (ans > sum)
			ans = sum;
		return;
	}
	if (now == chicken.size())
		return;
	// 재귀 구성 -> 해당 치킨집을 고른다 안고른다
	// 고른다
	Node tmp = chicken[now];
	COPY[tmp.y][tmp.x] = 2;
	chick.push_back(tmp);
	dfs(now + 1, cnt + 1);
	COPY[tmp.y][tmp.x] = 0;
	chick.pop_back();

	// 안고른다
	dfs(now + 1, cnt);
}

void solve() {
	dfs(0, 0);
	cout << ans << '\n';
}

int main() {
	fastIO;
	input();
	solve();
	return 0;
}
