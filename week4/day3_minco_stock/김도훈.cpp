#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

// �ż��Ѱ��� �����޿� �ݵ�� �ŵ�
// �����ް� ���ؼ� ���̳ʽ��� �Ȼ�� ���� ������ �̵�
// �õ�Ӵϴ� �ϴ� ������ �Ŵ� Ma��ŭ �����Ѵ�

struct Info {
	int num;
	int price;
	int get;
	//int cnt;
};


int Ms, Ma;
int N, L;
int MAP[15][16];
vector<Info>v;
int DAT[15];

bool cmp(Info left, Info right) {
	if (left.get > right.get)
		return true;
	if (left.get < right.get)
		return false;
	if (left.price < right.price)
		return true;
	if (left.price > right.price)
		return false;
	return false; //left.get > right.get;
}


void func() {
	for (int i = 0; i <= L; i++) {	// ���� �� ��ŭ ����
		Ms += Ma;	// �Ŵ� �õ�Ӵ� M��ŭ ������

		// ���޿� �ֽ��� ������ �Ⱦƾ���
		for (int p = 0; p < 15; p++) {
			if (DAT[p] != 0) {
				Ms += DAT[p] * MAP[p][i];
			}
		}

		cout << Ms << endl;
		
		if (i == L) break;

		for (int j = 0; j < N; j++) {
			v.push_back({ j, MAP[j][i], MAP[j][i + 1] - MAP[j][i] });
			// �����ް� ���Ͽ� ������ ����
		}
		sort(v.begin(), v.end(), cmp);
		// ������ ���� ������ ����

		cout << v[0].get << " " << v[1].get << " " << v[2].get << endl;

		for (int k = 0; k < v.size(); k++) {
			if (v[k].get <= 0) break;
			int val = MAP[v[k].num][i];
			if (val > Ms) continue;	// �õ�Ӵϰ� �����ؼ� �������
			int cnt = Ms / val;
			DAT[v[k].num] = cnt;	// �ֽ��� ��ٴ� ���� �����ϱ� ���� ������ �Բ� DAT�� ����
			// ������ �õ�ӴϿ��� �������
			Ms -= cnt * val;
		}
		v.clear();

	}
	


}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> Ms >> Ma;
		int start = Ms;
		cin >> N >> L;

		memset(MAP, 0, sizeof(MAP));

		for (int i = 0; i < N; i++) {
			for (int j = 0; j <= L; j++) {
				cin >> MAP[i][j];
			}
		}

		func();
		int ans = Ms - (start + (Ma * L));

		cout << "#" << tc << " " << Ms <<" "<<ans<< endl;

	}

}