#include <iostream>
#include <vector>
using namespace std;


// 0 1 2 3 -> �� �� �� ��
// �� �� �ִ� ������ ���� ����
// 00000, 00001, 00002, 00003, 00010 ... ����츦 ����������Ѵ�
// -> dfs �̿�


int N;
int MAP[21][21];
int tmp[21][21];
int tmpMAP[20][20];
int arr[5];
int ans = -21e8;
vector<int>v;

void move(int num) { // ������ �������� �����̰� �ϴ� �Լ�
	// ���� Ž���ϸ鼭 0�� �ƴϸ� �ϴ� ���Ϳ� �ִ´�
	// ���͸� Ž���ϸ鼭 ���ӵ� �� ���� ������ 2�� ���ؼ� ���� ä���ش�

	if (num == 0) {	// ���������� �̴� ���
		// ���������� �̴ϱ� �ະ�� �����ʿ��� �������� Ž��
		for (int i = 0; i < N; i++) {
			for (int j = N - 1; j >= 0; j--) {
				if (tmp[i][j] != 0) {
					v.push_back(tmp[i][j]);
				}
				tmp[i][j] = 0;
			}
			int idx = N - 1;
			for (int j = 0; j < v.size(); j++) {
				if (j + 1 < v.size() && v[j] == v[j + 1]) {
					tmp[i][idx] = v[j] * 2;
					j++;	// ���Ƽ� ������ ������ ������ ���� �ٽ� �����ʱ� ����
				}
				else {
					tmp[i][idx] = v[j];
				}
				idx--;
			}
			v.clear();
		}
	}
	else if (num == 1) {	// �������� �̴� ���
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (tmp[i][j] != 0) v.push_back(tmp[i][j]); // ó������ ���鼭 ���Ϳ� �ϴ� �� �־��ش�.
				tmp[i][j] = 0; // �־��ָ鼭 ���� �ʱ�ȭ
			}
			int idx = 0;
			for (int j = 0; j < v.size(); j++) { // ���͸� ó������ ������ ���鼭
				if (j + 1 < v.size() && v[j] == v[j + 1]) {
					tmp[i][idx] = v[j] * 2;
					j++;
				}
				else tmp[i][idx] = v[j]; // �ٸ��ٸ� �׳� ���� ���Ͱ��� �ʿ� �־��ش�.
				idx++;
			}
			v.clear();
		}
	}
	else if (num == 2) {	// �Ʒ��� �̴� ���
		for (int i = 0; i < N; i++) {
			for (int j = N - 1; j >= 0; j--) {
				if (tmp[j][i] != 0) v.push_back(tmp[j][i]);
				tmp[j][i] = 0;
			}
			int idx = N - 1;
			for (int j = 0; j < v.size(); j++) {
				if (j + 1 < v.size() && v[j] == v[j + 1]) {
					tmp[idx][i] = v[j] * 2;
					j++;
				}
				else tmp[idx][i] = v[j];
				idx--;
			}
			v.clear();
		}
	}
	else {	// ���� �̴� ���
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (tmp[j][i] != 0) v.push_back(tmp[j][i]);
				tmp[j][i] = 0;
			}
			int idx = 0;
			for (int j = 0; j < v.size(); j++) {
				if (j + 1 < v.size() && v[j] == v[j + 1]) {
					tmp[idx][i] = v[j] * 2;
					j++;
				}
				else tmp[idx][i] = v[j];
				idx++;
			}
			v.clear();
		}
	}
}


void dfs(int level) {
	if (level == 5) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				tmp[i][j] = MAP[i][j];

		
		for (int i = 0; i < 5; i++)
			move(arr[i]);
			//cout << arr[i];
		//cout << endl;

		/*for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << tmp[i][j] << " ";
			}
			cout << endl;
		}*/


		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				if (ans < tmp[i][j])
					ans = tmp[i][j];
			}
		return;
	}

	// ���⼭ �������ָ� �ȴ�.
	/*for (int i = 0; i < 4; i++)
		move(arr[i]);*/


	for (int i = 0; i < 4; i++) {	// ������ �� �ִ� ��� ���
		arr[level] = i;
		dfs(level + 1);
		
	}
}


int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> MAP[i][j];
	dfs(0);
	cout << ans;
}