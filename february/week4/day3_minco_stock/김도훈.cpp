#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

// 매수한것은 다음달에 반드시 매도
// 다음달과 비교해서 마이너스면 안사는 것이 무조건 이득
// 시드머니는 일단 무조건 매달 Ma만큼 증가한다

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
	for (int i = 0; i <= L; i++) {	// 개월 수 만큼 진행

		if(i>0) // ***처음 0개월에는 더해주면 안된다
			Ms += Ma;	// 매달 시드머니 Ma만큼 더해짐

		// 전달에 주식을 샀으면 팔아야지
		for (int p = 0; p < 15; p++) {
			if (DAT[p] != 0) {
				Ms += DAT[p] * MAP[p][i];
				DAT[p] = 0;	//***확인 후 계산을 해줬으면 초기화 시켜줘야한다
			}
		}

		//cout << Ms << endl;

		if (i == L) break;

		for (int j = 0; j < N; j++) {
			v.push_back({ j, MAP[j][i], MAP[j][i + 1] - MAP[j][i] });
			// 다음달과 비교하여 이익을 저장
		}
		sort(v.begin(), v.end(), cmp);
		// 이익이 높은 순으로 정렬

		//cout << v[0].get << " " << v[1].get << " " << v[2].get << endl;

		for (int k = 0; k < v.size(); k++) {
			if (v[k].get <= 0) break;
			int val = MAP[v[k].num][i];
			if (val > Ms) continue;	// 시드머니가 부족해서 살수없음
			int cnt = Ms / val;
			DAT[v[k].num] = cnt;	// 주식을 샀다는 것을 저장하기 위해 개수와 함께 DAT에 저장
			// 샀으면 시드머니에서 빼줘야지
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

		cout << "#" << tc << " " << ans << endl;

	}

}
