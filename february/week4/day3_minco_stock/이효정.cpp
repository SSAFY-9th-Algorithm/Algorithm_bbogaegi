#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
/*
간과한 부분
#1. 항상 제일 큰 수익을 얻을 수 있는 방법만 선택해서는 안된다
  -> 최선의 경우가 다를 수
  수익을 얻을 수 있는 경우가 여러개일 때 각 종목 별 개수를 조절하면
  한가지 종목에 몰빵하는 것보다 많은 수익을 낼 수 있다

=> 위의 문제는 아니었고, 같은 수익이 날 때 이전 값이 적은 종목을
	매수하는게 이득인데, 그런 정렬기준이 없었음
	세이씨 최공!!╰(*°▽°*)╯
*/

struct Stock {
	int idx;
	int price;
};

struct Profit {
	int before;
	int after;
	int diff; // 차이

	// ** 정렬 기준은 2가지가 되어야한다! **
	bool operator<(Profit next) const {
		if (diff > next.diff)
			return true;
		else if (diff < next.diff)
			return false;
		return before < next.before;
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
				profit[j - 1][i] = { stocks[i][j - 1].price, stocks[i][j].price, stocks[i][j].price - stocks[i][j - 1].price };
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
	// for (int i = 0; i < N && profit[month][i].diff > 0 && nowSeed >= profit[month][i]; i++) {
	// for조건이 위처럼 되면
	// 가격이 제일 높은 종목이 제일 큰 수익을 낸다고 정렬이 되면
	// 아래에 수익을 낼 수 있는 종목에 대해서는 탐색하지 않고 끝나는 문제가 발생
	// => for 안에서 if조건으로 continue해줌
	for (int i = 0; i < N && profit[month][i].diff > 0; i++) {
		if (nowSeed < profit[month][i].before)
			continue;
		int buy = (nowSeed / profit[month][i].before);
		seed -= buy * profit[month][i].before;
		seed += buy * profit[month][i].after;
		nowSeed %= profit[month][i].before;
	}
}

int main(void) {
	// freopen("input.txt", "r", stdin);
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
