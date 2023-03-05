#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

/*
1. 계단 입구까지 이동 시간 
	= | PR - SR | + | PC - SC |
2. 계단을 내려가는 시간
	= 계단 입구에 도착한 1분 후부터 K만큼

각 계단 당 3명씩 이용 가능
*/

struct Person {
	int idx;
	int y;
	int x;
	int arrive1;
	int arrive2;
	int total1;
	int total2;
};

struct Stair {
	int y;
	int x;
	int cost;
};

struct s1Cmp {
	bool operator()(Person p1, Person p2) {
		if (p1.total1 > p2.total1)
			return true;
		if (p1.total1 < p2.total1)
			return false;
		return p1.arrive1 > p2.arrive1;
	}
};

struct s2Cmp {
	bool operator()(Person p1, Person p2) {
		if (p1.total2 > p2.total2)
			return true;
		if (p1.total2 < p2.total2)
			return false;
		return p1.arrive2 > p2.arrive2;
	}
};

int N; 
Person people[11];
Stair stairs[2];
int minTime = 21e8;
int numOfPerson = 0;
priority_queue<Person, vector<Person>, s1Cmp> s1;
priority_queue<Person, vector<Person>, s2Cmp> s2;

int mat[11][11];
int decide[11];

void reset() {
	memset(people, 0, sizeof(people));
	memset(stairs, 0, sizeof(stairs));
	memset(mat, 0, sizeof(mat));
	memset(decide, 0, sizeof(decide));
	minTime = 21e8;
	numOfPerson = 0;
	s1 = priority_queue<Person, vector<Person>, s1Cmp>();
	s2 = priority_queue<Person, vector<Person>, s2Cmp>();
}

void setPeopleInfo() {
	for (int i = 0; i < numOfPerson; i++) {
		Person now = people[i];
		now.arrive1 = 1 + abs(now.y - stairs[0].y) + abs(now.x - stairs[0].x);
		now.arrive2 = 1 + abs(now.y - stairs[1].y) + abs(now.x - stairs[1].x);
		now.total1 = now.arrive1 + stairs[0].cost;
		now.total2 = now.arrive2 + stairs[1].cost;
		people[i] = now;
		s1.push(people[i]);
		s2.push(people[i]);
	}
}

void input() {
	int sIdx = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> mat[i][j];
			if (!mat[i][j])
				continue;
			if (mat[i][j] == 1) {
				people[numOfPerson] = {numOfPerson, i, j, 0, };
				numOfPerson++;
			}
			else
				stairs[sIdx++] = { i, j, mat[i][j] };
		}
	}
	setPeopleInfo();
}

int calcTime(priority_queue<Person, vector<Person>, s1Cmp> &tmp1, priority_queue<Person, vector<Person>, s2Cmp> &tmp2) {
	vector<Person> v1;
	vector<Person> v2;
	int t1 = 0;
	int t2 = 0;
	while (!tmp1.empty()) {
		Person now = tmp1.top();
		tmp1.pop();
		if (decide[now.idx] != 1)
			continue;
		if (v1.size() > 2) {
			if (now.arrive1 < v1[v1.size() - 3].total1)
				now.total1 += v1[v1.size() - 3].total1 - now.arrive1;
		}
		v1.push_back(now);
		t1 = now.total1;
		if (t1 >= minTime)
			return 21e8;
	}
	while (!tmp2.empty()) {
		Person now = tmp2.top();
		tmp2.pop();
		if (decide[now.idx] != 2)
			continue;
		if (v2.size() > 2) {
			if (now.arrive2 < v2[v2.size() - 3].total2)
				now.total2 += v2[v2.size() - 3].total2 - now.arrive2;
		}
		v2.push_back(now);
		t2 = now.total2;
		if (t2 >= minTime)
			return 21e8;
	}
	return max(t1, t2);
}

void dfs(int level) {
	if (level == numOfPerson) {
		priority_queue<Person, vector<Person>, s1Cmp> temp1 = s1;
		priority_queue<Person, vector<Person>, s2Cmp> temp2 = s2;
		int time = calcTime(temp1, temp2);
		if (minTime > time)
			minTime = time;
		return;
	}
	decide[level] = 1;
	dfs(level + 1);
	decide[level] = 2; 
	dfs(level + 1);
}

int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		reset();
		input();
		dfs(0);
		cout << "#" << tc << " " << minTime << "\n";
	}
}
