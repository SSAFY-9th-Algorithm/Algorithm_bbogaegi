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
			visited[next] = visited[now] + 1;	// �ִܰŸ��� ���ϱ� ���� ������ ���������� ��ĭ �� ���� ������ �������ش�
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
		if (visited[i] - 1 == K) {	// ex) 1->2->3 1���� 3���� ��� �� �ϳ��ε� �⸧ �Ҹ�� �ι� �Ǿ��� ������ -1�� ���ش�
			flag = 1;
			cout << i << '\n';
		}
	if (flag == 0) cout << "-1" << '\n';	// �⸧���� �ٽἭ ���� ��찡 ������ -1�� ������ش�
	return 0;
}