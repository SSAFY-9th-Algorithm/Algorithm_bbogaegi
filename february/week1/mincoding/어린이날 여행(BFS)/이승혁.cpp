#include <vector>
#include <queue>
#include <iostream>
using namespace std;

int N, M, K, P,flag=0;
vector<int> v[1000000];
int dat[200001];
int visited[200001];

void bfs(int start) {
	queue<int> q;
	q.push(start);
	visited[start] = 1;
	while (!q.empty()) {
		int now = q.front();
		q.pop();
			
		for (int next = 0; next < v[now].size(); next++) {
			if (dat[now] == K) continue;
			int to = v[now][next];
			if (visited[to] == 1)continue;
			visited[to] = 1;
			dat[to] = dat[now] + 1;
			q.push(to);
		}
	}
}

int main() {
	cin >> N >> M >> K >> P;

	for (int i = 0; i < M; i++) {
		int from, to;
		cin >> from >> to;
		v[from].push_back(to);
	}
	
	bfs(P);

	for (int i = 1; i <= N; i++) {
		if (dat[i] == K) {
			cout << i << '\n';
			flag = 1;
		}
	}

	if (flag == 0)cout << -1;
}
