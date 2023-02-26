#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

// 처음에 뭔 뻘짓을 했느냐
// 이익 정렬을 잘못했다!
// 마지막달은 사면 안되는데 샀다!

// 설계
// 순서대로 보면서 이익 있는 종목 구매 -> 판매 반복

struct Stock {
	int num;	// 종목 번호
	int price;	// 가격
	int p;	// 이익

	bool operator < (Stock next) const{
		if (p < next.p)
			return true;
		if (p > next.p)
			return false;
		if (price > next.price)
			return true;
		if (price < next.price)
			return false;
		return false;
	}
};

int Ms, Ma; // 첫 시드액, 월별 투자 금액
int N, L; // 종목 수, 과거 데이터 기간
int DATA[16][17];
int ans;

void INIT() {
	ans = 0;
}

void input() {
	cin >> Ms >> Ma >> N >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < L+1; j++)
			cin >> DATA[i][j];
	}
}

int sell(int j, queue<pair<int,int>>& q) {
	int res = 0;
	while (!q.empty())
	{
		int cnt = q.front().first, idx = q.front().second;
		q.pop();
		res += cnt * DATA[idx][j];
	}
	return res;
}

void solve() {
	int total = Ms + Ma * L;
	int totalcost = Ms;
	
	queue<pair<int, int>> buystocks;
	priority_queue<Stock>pq;
	for (int j = 0; j <= L; j++) {
		// 첫주가 아니면 Ma 만큼 저축!
		if (j != 0)
			totalcost += Ma;

		// 내가 산 주식이 있으면 팔아 치우자!
		if (buystocks.size() > 0) 
			totalcost += sell(j, buystocks);

		// 마지막 달은 구매 안할거니까 팔고 끝내자
		if (j == L)
			continue;

		// 종목들을 확인하며 이익이 있는 주식들을 담아 줄건데 
		// 이익이 큰 순서 -> 가격이 싼 순서로 담음
		for (int i = 0; i < N; i++) {
			int profit = DATA[i][j + 1] - DATA[i][j];

			if(profit > 0)
				pq.push({ i ,DATA[i][j], profit });
		}
		// 담았으면 사야죠!
		while (!pq.empty())
		{
			Stock now = pq.top();
			pq.pop();

			int cnt = totalcost / now.price;
			int idx = now.num;

			// 담은 친구들 중에 내가 가진돈으로 살 수 있는 애들만 살거에요!
			if (cnt > 0) {
				buystocks.push({ cnt, idx });
				totalcost -= cnt * now.price;
			}
		}
	}
	
	int de = 1;

	ans = totalcost - total;
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		INIT();
		// input
		input();
		// solve
		solve();
		// output
		cout << '#' << tc << ' ' << ans << '\n';
	}

	return 0;
}
