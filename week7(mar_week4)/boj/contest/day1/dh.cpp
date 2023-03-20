#include <iostream>
using namespace std;

// �� ó�� �����ϴ� �κ��� ������ û�� -> 1���� ī��Ʈ ����
// ��� 2����
// �켱 ���� ĭ���� �ֺ� 4ĭ �߿� û�Ұ� �Ǿ� ���� ���� ĭ�� �ִ��� Ȯ��
// �������� ȸ�� 0 3 2 1 0 3 2 1...... -> d = (d + 3) % 4

int dir[4] = { 0, 1, 2, 3 };
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int N, M;
int r, c, d;
int MAP[50][50];
int visited[50][50];
int cnt;


int main() {
	cin >> N >> M;
	cin >> r >> c >> d;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> MAP[i][j];


	while (1) {
		if (visited[r][c] == 0) {
			visited[r][c] = 1;
			cnt++;
		}
		int flag = 0;
		// ������ �����鼭 Ȯ��
		for (int i = 0; i < 4; i++) {
			d = (d + 3) % 4;
			int nx = r + dx[d];
			int ny = c + dy[d];
			if (MAP[nx][ny] == 0 && visited[nx][ny] == 0) {
				r += dx[d];
				c += dy[d];
				flag = 1;
				break;	// ������ �������� ���ͼ� ���ΰ��� û�� ���� Ȯ��
			}
		}	// 4���� Ȯ���ߴµ� ��� û���� ���� ���ٸ�? (flag = 0)

		// �����Ѵ� -> �����Ҷ� ���̶�� �۵������
		if (flag == 0) {
			/*
			0 -> 2
			1 -> 3
			2 -> 0
			3 -> 1
			*/
			// -> d = (d+2)%4
			int backdir = (d + 2) % 4;
			if (MAP[r + dx[backdir]][c + dy[backdir]] == 1) break; // ���̸� ��
			// �ƴϸ� ����
			r += dx[backdir];
			c += dy[backdir];
		}
	}
	cout << cnt << endl;
}