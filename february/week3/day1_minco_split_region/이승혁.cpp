#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int MAP[8][8], w[8];
int N, res, choice[8];

void isValid() {
	int A = 0, B = 0, Aflag = 0, Bflag = 0;
	vector<int> Av;
	vector<int> Bv;

	for (int i = 0; i < N; i++) {
		if (choice[i] == 1) Av.push_back(i);
		else Bv.push_back(i);
	}

	if (Av.size() == 0 || Bv.size() == 0)return;

	// A 마을 확인
	if (Av.size() == 1) Aflag = 1;
	else if (Av.size() > 1)
	{
		// 간선의 개수는 최소 N-1 개 이상
		int Acnt = 0;
		for (int i = 0; i < Av.size(); i++) {
			// 하나도 이어지지 않았다면 그대로 0
			int Asolo = 0;
			for (int j = 0; j < Av.size(); j++) {
				if (i == j) continue;
				if (MAP[Av[i]][Av[j]] == 1) {
					Acnt++;
					Asolo = 1;
				}
			}
			if (Asolo == 0) return;
		}
		if (Acnt / 2 >= Av.size() - 1) Aflag = 1;
	}

	// B 마을 확인
	if (Bv.size() == 1) Bflag = 1;
	else if (Bv.size() > 1)
	{
		int Bcnt = 0;
		for (int i = 0; i < Bv.size(); i++) {
			int Bsolo = 0;
			for (int j = 0; j < Bv.size(); j++) {
				if (i == j) continue;
				if (MAP[Bv[i]][Bv[j]] == 1) {
					Bsolo = 1;
					Bcnt++;
				}
			}
			if (Bsolo == 0) return;
			if (Bcnt / 2 >= Bv.size() - 1) Bflag = 1;
		}
	}
	// 유권수 추가 확인 초기화


	if (Aflag == 1 && Bflag == 1) {
		for (int i = 0; i < Av.size(); i++) A += w[Av[i]];
		for (int i = 0; i < Bv.size(); i++) B += w[Bv[i]];
		res = min(res, abs(A - B));
	
		//cout << "A 지역구 뽑힌 마을 : ";
		//for (int i = 0; i < Av.size(); i++) {
		//	cout << Av[i] << " ";
		//}cout << '\n';
		//cout << "B 지역구 뽑힌 마을 : ";
		//for (int i = 0; i < Bv.size(); i++) {
		//	cout << Bv[i] << " ";
		//}cout << '\n';
	}
	

}

void dfs(int level) {
	if (level == N / 2) {
		isValid();
		return;
	}

	for (int i = 0; i < N; i++) {
		if (choice[i] == 1) continue;
		// i 마을을 선택한다.
		choice[i] = 1;
		dfs(level + 1);
		choice[i] = 0;

		// i 마을을 선택하지 않는다.
		dfs(level + 1);
	}
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		//reset
		cin >> N;
		res = 21e8;
		memset(MAP, 0, sizeof(MAP));
		memset(w, 0, sizeof(w));
		memset(choice, 0, sizeof(choice));

		//input
		for (int i = 0; i < N; i++) for (int j = 0; j < N; j++)cin >> MAP[i][j];
		for (int i = 0; i < N; i++)cin >> w[i];

		// solve
		dfs(0);
		// output
		if (res == 21e8)
			cout << "#" << tc << " " << 0 << '\n';
		else
			cout << "#" << tc << " " << res << '\n';
	}


}
