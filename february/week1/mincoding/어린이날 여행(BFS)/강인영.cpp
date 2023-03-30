/*
N번 도시 & M개 단방향 도로
도시 간의 도로 거리 동일. 도시 간의 이동 시 한 칸의 기름 소모.
기름통의 칸을 모두 소모하여 갈 수 있는 도시로 여행지 정하기
while문을 돌릴 때에 k--를 해주고 k가 0이 되면 출력하도록 했는데 내림차순 정렬해서 출력하는 것이 통제 안 되어서 최종적으로 DAT 사용.
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
int k, p;
vector<int> v[200000];
queue<int> q;
int visited[200000];
int flag;

void bfs(int start) {
	q.push(start);
	visited[start] = 1;

	while (!q.empty()) {

		int now = q.front();
		q.pop();

		for (int i = 0; i < v[now].size(); i++) {
			int next = v[now][i];

			if (visited[next] > 0)
				continue;
			
			visited[next] = visited[now]+1;
			q.push(next);
		}
	}

}

int main() {
	cin >> n >> m;
	cin >> k >> p;

	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		v[a].push_back(b);
	}

	bfs(p);

	for (int i = 1; i <= n; i++) {
		if (visited[i] - 1 == k) {
			flag = 1;
			cout << i << endl;
		}
	}
	if (flag == 0)
		cout << -1;

}
