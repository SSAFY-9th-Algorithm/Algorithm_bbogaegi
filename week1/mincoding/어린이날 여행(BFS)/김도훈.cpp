#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M, K, P;
vector<int>al[200001];
int visited[200001];

void bfs(int start) {
	queue<int>q;
	q.push(start);

	visited[start] = 1;

	while (!q.empty())
	{
		int now = q.front();
		q.pop();

		for (int i = 0; i < al[now].size(); i++) {
			int next = al[now][i];
			if (next == 0)
				continue;
			if (visited[next] > 0)
				continue;
			visited[next] = visited[now] + 1;	// 최단거리를 구하기 위해 이전의 목적지에서 한칸 더 가는 것으로 생각해준다
			q.push(next);
		}
	}
}

int main() {
	cin >> N >> M >> K >> P;
	for (int i = 0; i < M; i++) {
		int from, to;
		cin >> from >> to;
		al[from].push_back(to);
	}
	bfs(P);
	int flag = 0;
	for (int i = 1; i <= N; i++)
		if (visited[i] - 1 == K) {	// ex) 1->2->3 1에서 3까지 방법 중 하나인데 기름 소모는 두번 되었기 때문에 -1을 해준다
			flag = 1;
			cout << i << '\n';
		}
	if (flag == 0) cout << "-1" << '\n';	// 기름통을 다써서 가는 경우가 없으면 -1을 출력해준다
	return 0;
}