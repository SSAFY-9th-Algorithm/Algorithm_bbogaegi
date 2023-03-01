#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
/*
간과한 부분
#1. 항상 제일 큰 수익을 얻을 수 있는 방법만 선택해서는 안된다
  -> 최선의 경우가 다를 수 
  수익을 얻을 수 있는 경우가 여러개일 때 각 종목 별 개수를 조절하면 
  한가지 종목에 몰빵하는 것보다 많은 수익을 낼 
*/

struct Stock {
	int idx;
	int price;
};

struct Profit {
	int before;
	int after;
	int diff; // 차이

	bool operator<(Profit next) const {
		return diff > next.diff;
	}
};

int principal; // 원금
int seed; // 투자 + 수익
int ma; // 매달 추가적으로 투자하는 금액
int L; // 과거 데이터 기간
int N; // 종목 수

Stock stocks[16][16]; //[종목수][데이터기간]
Profit profit[16][16]; //[데이터기간][종목수]

void reset() {
	memset(stocks, 0, sizeof(stocks));
	memset(profit, 0, sizeof(profit));
}

void input() {
	cin >> seed >> ma;
	cin >> N >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= L; j++) {
			stocks[i][j].idx = i;
			cin >> stocks[i][j].price;
			if (j > 0)
				profit[j - 1][i] = { stocks[i][j-1].price, stocks[i][j].price, stocks[i][j].price - stocks[i][j - 1].price };
		}
	}
	principal = seed + ma * L;
}

void calcMaxProfit(int month) {
	int nowProfit = month == 0 ? 0 : ma;
	seed += nowProfit;
	int nowSeed = seed;
	sort(profit[month], profit[month] + N);
	if (profit[month][0].diff <= 0)
		return;
	for (int i = 0; i < N && profit[month][i].diff > 0 && nowSeed >= profit[month][i].before; i++) {
		int buy = (nowSeed / profit[month][i].before);
		seed -= buy * profit[month][i].before;
		seed += buy * profit[month][i].after;
		nowSeed %= profit[month][i].before;
	}
}

int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		reset();
		input();
		for (int i = 0; i < L; i++) {
			calcMaxProfit(i);
		}
		seed += ma;
		cout << "#" << tc << " " << seed - principal << '\n';
	}
}
