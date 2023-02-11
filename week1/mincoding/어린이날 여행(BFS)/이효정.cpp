#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 도시 개수, 도로 개수, 남은 기름, 출발도시
int N, M, K, P;
vector<int> MAP[200001];
int visited[200001];

void bfs(int start) {
	queue<int> q;
	q.push(start);
	visited[start] = 1;
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		for (int i = 0; i < MAP[now].size(); i++) {
			int next = MAP[now][i];
			if (visited[next])
				continue;
			visited[next] = visited[now] + 1;
			q.push(next);
		}
	}
}

int main(void) {
	cin >> N >> M >> K >> P;
	for (int i = 0; i < M; i++) {
		int from, to;
		cin >> from >> to;
		MAP[from].push_back(to); // 단방향 연결
	}
	bfs(P);
	int flag = 0;
	for (int i = 1; i <= N; i++) {
		if (visited[i] - 1 == K) {
			flag = 1;
			cout << i << '\n';
		}
	}
	if (!flag) // 기름통을 모두 소모하여 살 수 있는 도시가 없음
		cout << "-1\n";
	return 0;
}
