// 가장 적게걸리는 -> 모든 경우 + 최소값
// ===> 가지치기

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

bool cmps1(person left, person right) {
		if (left.s1t < right.s1t)
			return true;
		if (left.s1t > right.s1t)
			return false;
		return false;
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
vector<int>path;

int N, p_cnt, s_cnt, MAP[10][10],MINTIME;
int idx1, idx2;
int canEnter1, canEnter2;

void reset() {
	idx1 = 0;
	idx2 = 0;
	MINTIME = 21e8;
	canEnter1 = -21e8;
	canEnter2 = -21e8;
	p_cnt = 0;
	s_cnt = 0;
	memset(MAP, 0, sizeof(MAP));
	memset(stair, 0, sizeof(stair));
	path.clear();
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
	}
}



void steps() {
	vector<int>st1ing;
	vector<int>st2ing;

	canEnter1 = -21e8;
	canEnter2 = -21e8;

	// 0번 계단에 선택된 녀석들
	int finish[10] = { 0, };
	for (int i = 0; i < path.size(); i++) {
		finish[path[i]] = 1;
		if (i < 3) {
			st1ing.push_back(path[i]);
			canEnter1 = max(canEnter1,people[path[i]].s1t);
		}
		else {
			// 들어갈 수 없는 상황
			if (people[path[i]].s1t - people[st1ing[i - 3]].s1t < stair[0].t) {
				canEnter1 = max(canEnter2,people[st1ing[i-3]].s1t + stair[0].t);
				st1ing.push_back(path[i]);
			}
			// 들어갈 수 있다
			else
			{
				canEnter1 = max(canEnter1,people[path[i]].s1t);
				st1ing.push_back(path[i]);
			}
		}
	};
	int st2_cnt = 0;

	for (int i = 0; i < p_cnt; i++) {
		if (finish[i] == 1)continue;
		if (st2_cnt < 3) {
			st2ing.push_back(i);
			canEnter2 = max(canEnter2,people[i].s2t);
		}
		else {
			// 들어갈 수 없는 상황
			int check = st2ing[st2_cnt - 3];
			if (people[i].s2t - people[check].s2t < stair[1].t) {
				canEnter2 = max(canEnter2, people[check].s2t + stair[1].t);
				st2ing.push_back(i);
			}
			// 들어갈 수 있다
			else
			{
				canEnter2 = max(canEnter2, people[i].s2t);
				st2ing.push_back(i);
			}
		}
	}
	cout << "\n 1번 계단 이용자 : ";
	for (int i = 0; i < st1ing.size(); i++) {
		cout << st1ing[i] << " ";
	}cout << "\n 2번 계단 이용자 : ";
	for (int i = 0; i < st2ing.size(); i++) {
		cout << st2ing[i] << " ";
	}cout << '\n';
	cout << canEnter1 << " " << canEnter2 << '\n';

	int MIN;
	if (canEnter1 != -21e8 && canEnter2 != -21e8)
		MIN = max(canEnter1, canEnter2);
	else if (canEnter1 == -21e8)
		MIN = canEnter2;
	else if (canEnter2==-21e8)
		MIN = canEnter1;

	MINTIME = min(MINTIME, MIN);
}

void dfs(int level) {
	if (level == p_cnt)
	{
		steps();
		return;
	}
	// 0번 계단으로 갈 애들 고르기
	path.push_back(level);
	dfs(level + 1);
	path.pop_back();
	// 안고르기
	dfs(level + 1);
	

		
}

int main() {
	//freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		reset();
		input();
		calctime();
		sort(people, people + p_cnt, cmps1);
		dfs(0);
		cout << "#" << tc << " " << MINTIME +1 << '\n';
		
	}
}

