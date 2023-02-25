#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct coord {
	int y, x,t;
};
struct person {
	int y, x;
	int s1t, s2t;
	int num;
};

struct cmps1 {
	bool operator () (person left, person right) {
		if (left.s1t < right.s1t)
			return false;
		if (left.s1t > right.s1t)
			return true;
		return false;
	}
};
struct cmps2 {
	bool operator () (person left, person right) {
		if (left.s2t < right.s2t)
			return false;
		if (left.s2t > right.s2t)
			return true;
		return false;
	}
};

coord stair[2];
person people[10];

int N, p_cnt, s_cnt, MAP[10][10], finish[10];
int idx1, idx2;
int canEnter1, canEnter2;
priority_queue<person,vector<person>,cmps1>pq1;
priority_queue<person,vector<person>,cmps2>pq2;
vector<int>st1time;
vector<int>st2time;

void reset() {
	idx1 = 0;
	idx2 = 0;
	canEnter1 = -21e8;
	canEnter2 = -21e8;
	p_cnt = 0;
	s_cnt = 0;
	memset(MAP, 0, sizeof(MAP));
	memset(stair, 0, sizeof(stair));
	memset(finish, 0, sizeof(finish));
	st1time.clear();
	st2time.clear();
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 1) {
				people[p_cnt++] = { i,j,0,0,p_cnt };
			}
			else if (MAP[i][j] > 1)stair[s_cnt++] = { i,j,MAP[i][j] };
	
		}
	}
}

void calctime() {
	for (int i = 0; i < p_cnt; i++) {
		// 각 사람별 계단1, 계단2 탈출 시간 갱신
		person p = people[i];
		p.s1t = abs(p.y - stair[0].y) + abs(p.x - stair[0].x) + stair[0].t ;
		p.s2t = abs(p.y - stair[1].y) + abs(p.x - stair[1].x) + stair[1].t;
		people[i] = p;
		pq1.push({ people[i] });
		pq2.push({ people[i] });
	}
}

void steps(int v) {
	if (v == 0) {
		// 0 번계단이 가까운 사람들
		int cursize = pq1.size();
		for (int i = 0; i < cursize; i++) {
			person now = pq1.top();
			if (finish[now.num] == 1) {
				pq1.pop();
				continue;
			}
			finish[now.num] = 1;
			if (idx1 < 3) {
				canEnter1 = max(canEnter1, now.s1t);
				st1time.push_back(now.num);
			}
			else if (idx1 >= 3 && now.s1t - people[st1time[idx1 - 3]].s1t >= stair[0].t) {
				canEnter1 = max(canEnter1, now.s1t);
			}
			// 3번째 앞 사람이 끝나야 이동 가능
			else {
				canEnter1 = people[st1time[idx1 - 3]].s1t + stair[0].t;
			}
			idx1++;
			pq1.pop();
			break;
		}
	}
	else {
		// 1번 계단이 가까운 사람들
		int cursize2 = pq2.size();
		for (int i = 0; i < cursize2; i++) {
			person now = pq2.top();
			if (finish[now.num] == 1) {
				pq2.pop();
				continue;
			}
			finish[now.num] = 1;
			if (idx2 < 3) {
				canEnter2 = max(canEnter2, now.s2t);
				st2time.push_back(now.num);
			}
			else if (idx2 >= 3 && now.s2t - people[st2time[idx2 - 3]].s2t >= stair[1].t) {
				canEnter2 = max(canEnter2, now.s2t);
			}
			// 3번째 앞 사람이 끝나야 이동 가능
			else {
				canEnter2 = people[st2time[idx2 - 3]].s2t + stair[2].t;
			}
			idx2++;
			pq2.pop();
			break;
		}
	}

}

void goStairs() {
	while (!pq1.empty() && !pq2.empty()) {

		// 둘 다 차있다
		// 둘의 순번이 같은애들
		if (!pq1.empty() && !pq2.empty())
		{

			if (pq1.top().num == pq2.top().num) {
				if (pq1.top().s1t < pq2.top().s2t)
					pq2.pop();
				else
					pq1.pop();
			}
		}

		if (stair[0].t > stair[1].t)
		{
			if (idx1 < 3) {
				for (int t = 0; t < 3; t++)
					steps(0);
				for (int t = 0; t < 3; t++)
					steps(1);
			}
			else
			{
				steps(0);
				steps(1);
			}
		}
		else {
			if (idx2 < 3) {
				for (int t = 0; t < 3; t++)
					steps(1);
				for (int t = 0; t < 3; t++)
					steps(0);
			}
			else
			{
				steps(1);
				steps(0);
			}
		}
	}
		
}

int main() {
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		reset();
		input();
		calctime();
		goStairs();
		cout << "#" << tc << " " << max(canEnter1, canEnter2) +1<< '\n';
		
	}
}


/*
10
0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0
0 0 1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
3 0 1 0 1 0 0 0 0 2
1 1 0 0 1 0 1 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0

*/
