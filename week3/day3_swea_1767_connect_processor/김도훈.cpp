#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// ����Ž��
// �ھ �߰����� �� �����ڸ��� �������� �ʰų� �����¿�� �����ϴ� ��� ����
// ���� �ִ� �ھ���� �̹� ����� ���� -> ����� �� ���������� �ʾƵ��ȴ�

// �������� ������ dfs�� ��� ��ġ���� �־���ߵ��� �������� ����
// ����� ����� �ʾ����� �������� �ð��� �ɸ���

struct Node {
	int y;
	int x;
};

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };


int N;
int MAP[13][13];
vector<Node>v;

int MaxConnect;
int MinLeng = 21e8;

void dfs(int idx, int leng, int connect) {	// leng : ������ �� connect : ����� �ھ��� ����
	// dfs ���� �� �Լ� �Ű������� ���� �� �Ź� ������....
	if (idx == v.size()) {
		if (connect > MaxConnect) {
			MinLeng = leng;
			MaxConnect = connect;
		}
		else if (connect == MaxConnect) {
			MinLeng = min(MinLeng, leng);
		}
		return;
	}

	for (int i = 0; i < 4; i++) {
		int ny = v[idx].y;
		int nx = v[idx].x;
		int cnt = 0;
		
		while (1) {
			ny += dy[i];
			nx += dx[i];
			cnt++;
			if (MAP[ny][nx] == 1 || MAP[ny][nx] == 2) {	// �ھ �ְų� �̹� ������ �ִ� ���
				cnt = 0;
				break;
			}
			if (MAP[ny][nx] == 0 && (nx == 0 || ny == 0 || nx == N - 1 || ny == N - 1))
				break;
		}
		if (cnt != 0) {
			ny = v[idx].y;
			nx = v[idx].x;
			while (1) {
				ny += dy[i];
				nx += dx[i];
				if (nx<0 || ny<0 || nx>N - 1 || ny>N - 1)
					break;
				MAP[ny][nx] = 2;	// ������ ��ġ�Ǿ����� ��Ÿ�����ش�
			}
			dfs(idx + 1, leng + cnt, connect + 1);
			ny = v[idx].y;
			nx = v[idx].x;
			while (1) {
				ny += dy[i];
				nx += dx[i];
				if (nx < 0 || ny < 0 || nx > N - 1 || ny > N - 1)
					break;
				MAP[ny][nx] = 0;
			}

		}
		
	}
	dfs(idx + 1, leng, connect);
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;

		v.clear();
		MaxConnect = 0;
		MinLeng = 21e8;


		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> MAP[i][j];

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (MAP[i][j] == 1) {
					if (i == 0 || i == N - 1 || j == 0 || j == N - 1) continue;
					v.push_back({ i, j });
				}
			}
		}
		dfs(0, 0, 0);
		cout << "#" << tc << " " << MinLeng << '\n';
	}

}