#include <iostream>
#include <cstring>
using namespace std;
// 달별 수영장 이용 횟수 1~12
// 일, 달, 3달, 년 이용권 금액
int swimcnt[13],pee[4];
int sum,MIN;

void dfs(int month) {
	
	// 1년권 쓰는 경우 마지막에 비교
	if (month > 12) {
		//cout << "최종: " << sum << '\n';
		if (sum < MIN)MIN = sum;
		return;
	}

	if (swimcnt[month] != 0) {
		// 1일권 쓰는 경우
		sum += swimcnt[month] * pee[0];
		//cout << month << "월" << " 일일요금계산 -> " << sum << '\n';
		dfs(month + 1);
		sum -= swimcnt[month] * pee[0];


		// 1달권 쓰는 경우
		sum += pee[1];
		//cout << month << "월" << " 1달권 계산 -> " << sum << '\n';
		dfs(month + 1);
		sum -= pee[1];

		// 3달권 쓰는 경우
		sum += pee[2];
		//cout << month << "월" << " 3달권 계산 -> " << sum << '\n';
		dfs(month + 3);
		sum -= pee[2];

	}
	else {dfs(month + 1);}
}

		


int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc ++ )
	{
		int sum = 0;
		for (int i = 0; i < 4; i++) { cin >> pee[i]; }
		for (int i = 1; i < 13; i++) { cin >> swimcnt[i]; }
		MIN = pee[3];
		dfs(1);
		memset(swimcnt, 0, sizeof(swimcnt));
		memset(pee, 0, sizeof(pee));
		cout << "#"<<tc<<" "<<MIN<<'\n';

	}
}
