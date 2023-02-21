#################미해결 문제########################
#################미해결 문제########################
#################미해결 문제########################
#################미해결 문제########################
#################미해결 문제########################
#################미해결 문제########################

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int MAP[8][8],w[8];
int N,res,choice[8];
int plused[8];

void isValid() {
	int A=0, B=0;
	vector<int> Av;
	vector<int> Bv;

	memset(plused, 0, sizeof(plused));

	for (int i = 0; i < N; i++) {
		if (choice[i] == 1) Av.push_back(i);
		else Bv.push_back(i);
	}
	if (Av.size() == 0 || Bv.size() == 0) return;
	// A 마을 확인
	if (Av.size() == 1) A += w[Av[0]];
	else if(Av.size()>1)
	{
		for (int i = 0; i < Av.size() - 1; i++) {
			for (int j = i + 1; j < Av.size(); j++) {
				// 같은 지역구로 선택된 두 마을이 연결될 수 있다면
				//cout << Av[i] << " " << Av[j] << '\n';
				if (MAP[Av[i]][Av[j]] && MAP[Av[j]][Av[i]]) {
					if (plused[Av[i]] == 0) {
						plused[Av[i]] = 1;
						A += w[Av[i]];
					}
					if (plused[Av[j]] == 0) {
						plused[Av[j]] = 1;
						A += w[Av[j]];
					}
				}

			}
		}
	}

	// B 마을 확인
	if (Bv.size() == 1) B += w[Bv[0]];
	else if (Bv.size()>1)
	{
		for (int i = 0; i < Bv.size() - 1; i++) {
			for (int j = i + 1; j < Bv.size(); j++) {
				// 같은 지역구로 선택된 두 마을이 연결될 수 있다면
				if (MAP[Bv[i]][Bv[j]] && MAP[Bv[j]][Bv[i]]) {
					if (plused[Bv[i]] == 0) {
						plused[Bv[i]] = 1;
						B += w[Bv[i]];
					}
					if (plused[Bv[j]] == 0) {
						plused[Bv[j]] = 1;
						B += w[Bv[j]];
					}
				}

			}
		}
	}

	
	
	cout << "A 마을 유권자 수 " << A << " B 마을 유권자 수 " << B << "\n";
	res = min(res, abs(A - B));
}

void dfs(int level) {
	if (level == N/2) {
		isValid();
		return;
	}

	for (int i = 0; i < N; i++) {
		if (choice[i] == 1) continue;
		choice[i] = 1;
		dfs(level + 1);
		choice[i] = 0;
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
		cout <<"#"<<tc<<" "<<res<<'\n';
	}
	

}


