#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

// R, C로 받아 놓고 N, M을 찾지 말자...

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

struct Node {
	int y;
	int x;

	bool operator <(Node next) const {
		return y > next.y;
	}
};

int R, C;
char MAP[110][110];
int visited[110][110];
int N;

// 중력 구현
void gravity(vector<Node> &v) {
	sort(v.begin(), v.end());
	vector<Node> ori = v;

	while (!v.empty())
	{
		vector<Node> tmp;
		int flag = 0;

		for (int i = 0; i < v.size(); i++) {
			int y = v[i].y + 1;
			int x = v[i].x;

			if (y < 0 || x < 0 || y >= R || x >= C) {
				flag = 1;
				break;
			}
			if (visited[y][x]) {
				flag = 1;
				break;
			}
			tmp.push_back({ y, x });
		}
		if (flag)
			break;
		v = tmp;
	}
	for (auto now : ori)
		MAP[now.y][now.x] = '.';
	for (auto now : v)
		MAP[now.y][now.x] = 'x';
}

void bfs(int y, int x) {
	queue <Node> q;
	memset(visited, 0, sizeof(visited));

	// 땅에 있는 미네랄의 위치를 전부 q에 넣자!
	// -> 여기부터 연결 되어있는 클러스터 확인
	for (int j = 0; j < C; j++) {
		if (MAP[R - 1][j] == 'x') {
			q.push({ R - 1, j });
			visited[R - 1][j] = 1;
		}
	}

	//  땅과 연결된 친구들을 찾아주자!
	// -> 하나의 클러스터
	while (!q.empty())
	{
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (ny < 0 || nx < 0 || ny >= R || nx >= C)
				continue;
			if (MAP[ny][nx] == '.')
				continue;
			if (visited[ny][nx])
				continue;

			visited[ny][nx] = 1;
			q.push({ ny, nx });
		}
	}

	// 공중에 떠있는 클러스터를 찾자
	vector<Node> v;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			if (MAP[i][j] == 'x' && !visited[i][j])
				v.push_back({ i, j });

	gravity(v);
}

Node solve(int y, int dir) {
	// 왼쪽에서 쏜다
	if (dir == 0) {
		for (int j = 0; j < C; j++) {
			if (MAP[y][j] == 'x') {
				MAP[y][j] = '.';
				return {y, j};
			}
		}
	}
	// 오른쪽에서 쏜다
	if (dir == 1) {
		for (int j = C - 1; j >= 0; j--) {
			if (MAP[y][j] == 'x') {
				MAP[y][j] = '.';
				return { y, j };
			}
		}
	}
	return { -1, -1 };
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> R >> C;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++) 
			cin >> MAP[i][j];
		
	Node pos;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		if (i % 2 == 0)
			pos = solve(R - num, 0);
		else
			pos = solve(R - num, 1);
		if (pos.y == -1 && pos.x == -1)
			continue;
		bfs(pos.y, pos.x);
	}	

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++)
			cout << MAP[i][j];
		cout << '\n';
	}
	return 0;
}
