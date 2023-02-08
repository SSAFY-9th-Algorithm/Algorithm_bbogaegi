#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
	int to;
	int cost;
};

int N;	// 동굴 방의 개수
int r1, r2;		//두 로봇의 초기 위치
vector<Edge> al[100001];	//노드와 간선 가중치를 담을 벡터
int visited[100001];		// 방문 기록
int sum;
int MIN = 21e8;
int MAX_DIST = -21e8;

void dfs(int now) {
	if (now == r2) {
		MIN = sum - MAX_DIST;
		return;
	}
	for (int i = 0; i < al[now].size(); i++) {
		int next = al[now][i].to;
		int nc = al[now][i].cost;
		if (visited[next] == 1)
			continue;
		visited[next] = 1;
		sum += nc;
		if (nc > MAX_DIST)
			MAX_DIST = nc;
		dfs(next);
		visited[next] = 0;
		sum -= nc;
	}
}


int main() {
	cin >> N >> r1 >> r2;
	for (int i = 0; i < N - 1; i++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		al[from].push_back({ to, cost });
		al[to].push_back({ from, cost });
	}
	if (N == 1 || N == 2) { //방이 1개거나 2개일 경우 이동할 필요가 없음
		cout << "0";
	}
	else {
		visited[r1] = 1;
		dfs(r1);
		cout << MIN;
	}
	return 0;
}
