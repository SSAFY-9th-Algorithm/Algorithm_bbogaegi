// 잘 모르겠어서 일단 작성하고 코드 돌려봤다
// 출력된거 보면서 떠오름
// 종목별로 해당 달에 사면 이득인것 고른다 -> 수익이 큰거 순으로 정렬
// 수익이 음수거나 0이면 나간다(정렬했기때문에)
// 살 수 있다면 해당종목 번호, 수량을 큐에 담는다.
// 매 달 계산 시작 전 queue가 비어있지 않다면 팔고 시작한다.
// 팔기는 구매할 때 담은 종목번호를 이용해서 현재 가격 구한다.
// 끝

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct sales{
	int idx, price, benefit;
};
struct stocks {
	int amount, idx;
};

queue<stocks> mystocks;
vector<sales> v;

int stock[15][16];
int N, M, seed, first, p, ans;

bool cmp(sales left, sales right) {
	if (left.benefit > right.benefit)
		return true;
	if (left.benefit < right.benefit)
		return false;
	if (left.price < right.price)
		return true;
	if (left.price > right.benefit)
		return false;
	return left.benefit > right.benefit;
}

void reset() {
	memset(stock, 0, sizeof(stock));
}

void input() {
	cin >> seed >> p;
	cin >> N >> M;
	first = seed;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= M; j++) {
			cin >> stock[i][j];
		}
	}
}

void sell(int month) {
	while (!mystocks.empty()) {
		stocks now = mystocks.front();
		seed += now.amount * stock[now.idx][month];
		mystocks.pop();
	}
}

void calc() {
	for (int m = 0; m < M; m++) {
		if (m > 0)
			seed += p;
		if (mystocks.size() > 0) sell(m);
		for (int s = 0; s < N; s++)
			v.push_back({ s ,stock[s][m], stock[s][m + 1] - stock[s][m] });
		sort(v.begin(), v.end(), cmp);
		
		for (int i = 0; i < v.size(); i++) {
			if (v[0].benefit <= 0 || v[i].benefit <= 0)break;
			int price = stock[v[i].idx][m];
			if (seed < price) continue;
			mystocks.push({ seed / price, v[i].idx });
			seed -= seed / price * price;
		}
		v.clear();
	}

	// 다 끝나고 남은 주식 팔고, 최종 수익 계산
	if (mystocks.size() > 0) sell(M);
	seed += p;
	first += p * M;
	ans = seed - first;
}


int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		//reset()
		reset();
		//input()
		input();
		// solve()
		calc();
		//output
		cout << "#" << tc << " " << ans << '\n';
	}
	
}
